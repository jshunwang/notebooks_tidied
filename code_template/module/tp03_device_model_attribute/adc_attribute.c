/**************************
 * ADC设备的测试例子
 * 增加platform_driver外壳;
 * 用/sys/class下面的属性文件来控制/获得设备信息;
 * 不再支持传统的char驱动以及/proc下的文件;
 * Author: zht
 * Date: 2017-10-30
 **************************/
#include <linux/module.h>
#include <linux/sched.h> //进程状态
#include <linux/err.h> //IS_ERR
#include <linux/wait.h> //wait_queue_head_t
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h> //pdev & pdrv
#include "regs_adc.h" //获取硬件信息

//定义驱动用到的变量
static void __iomem *vir_base; 
static int cur_ch; //当前的通道
static int max_ch; //最大通道号
static int min_ch; //最小通道号
static int adc_irq; //记录中断号
static wait_queue_head_t adc_wait;

//定义一个新的class，用于代表一种新的设备分类
static struct class *adc_class;	//struct class 的定义在linux/device.h
//在class下面创建device设备,加入属性文件
static struct device *adc_dev;

//中断处理函数
static irqreturn_t
adc_service(int irq, void *dev_id)
{
	if (readl(vir_base+ADCINTCLR)==0) {
		printk("<0>Not adc irq\n");
		return IRQ_NONE;
	}
	//printk("adc irq service\n");
	writel(1, vir_base+ADCINTCLR);
	wake_up(&adc_wait);
	return IRQ_HANDLED;
}


/************************
 * 文件名: channel
 * adc_show_channel: 返回当前的通道号
 * adc_store_channel: 设置通道号(0~7)
 ************************/
static ssize_t 
adc_show_channel(struct device *dev,
		struct device_attribute *attr, char *buf)
{	
	return sprintf(buf, "%d\n", cur_ch);
}

//参数buf中是用户态echo的数字
static ssize_t
adc_store_channel(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc, value;
	unsigned long channel;
	//将用户态的字符串转换为整数
	//kstrtoul功能类似于用户态的strtoul, 0代表自动识别进制(8/10/16)
	//如果返回非0,则转换失败,返回错误值
	rc = kstrtoul(buf, 0, &channel);
	if (rc)
		return rc;
	if ((channel > max_ch) || (channel < min_ch)) {
		printk("<0>channel should be %d~%d\n", min_ch, max_ch);
		return -EINVAL;
	}
	//设置新的通道号
	value = readl(vir_base+ADCCON);
	value &= ~(0x7<<3);
	value |= (channel<<3);
	writel(value, (vir_base+ADCCON));
	cur_ch = channel;
	return count;
}


/***************************
 * 文件名: adc_value
 * adc_show_value: 启动新的采样并返回采样值(数字)
 ***************************/
static ssize_t 
adc_show_value(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	int value;
	DEFINE_WAIT(wait);
	//启动新的采样
	value = readl(vir_base+ADCCON);
	value |= (1<<0);
	writel(value, (vir_base+ADCCON));
	//等待(睡眠等)直到采样结束
	while (1) {
		prepare_to_wait(&adc_wait, &wait, TASK_INTERRUPTIBLE);
		value = readl(vir_base+ADCCON);
		if (!(value & (1<<0)))
			break;
		if (signal_pending(current)) {
			finish_wait(&adc_wait, &wait);
			return -ERESTARTSYS;
		}
		schedule();
	}
	finish_wait(&adc_wait, &wait);
	//获得AD值并返回
	value = readl(vir_base+ADCDAT) & 0xFFF;

	return sprintf(buf, "%d\n", value);
}


/***************************
 * 文件名: resolution
 * adc_show_resolution: 返回数字值的范围
 ***************************/
static ssize_t 
adc_show_resolution(struct device *dev,
		struct device_attribute *attr, char *buf)
{	
	return sprintf(buf, "[0~4095]\n");
}


/**************************
 * 文件名: range
 * adc_show_range: 返回模拟电压的范围
 **************************/
static ssize_t 
adc_show_range(struct device *dev,
		struct device_attribute *attr, char *buf)
{	
	return sprintf(buf, "[0~1.8V]\n");
}


//新增属性文件，用于控制/获取设备信息
static struct device_attribute adc_device_attrs[] = {
	__ATTR(channel, 0666, adc_show_channel, adc_store_channel),
	__ATTR(adc_value, 0444, adc_show_value, NULL),
	__ATTR(resolution, 0444, adc_show_resolution, NULL),
	__ATTR(range, 0444, adc_show_range, NULL),
	__ATTR_NULL,
};


//platform_driver->probe
//完成以前模块入口的工作，硬件信息来自于pdev
static int
adc_probe(struct platform_device *pdev)
{
	int value, ret = 0;
	struct resource *res_mem, *res_irq; //硬件信息
	struct adc_pdata *pdata; //初始化信息
	
	//首先获得硬件资源信息,如果获取失败，则退出
	res_mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res_mem || !res_irq) {
		printk("%s : cannot get enough resources\n", pdev->name);
		return -1;
	}

	//获得初始化信息
	pdata = pdev->dev.platform_data;
	if (!pdata) {
		printk("%s : cannot get init infomation\n", pdev->name);
		return -1;
	}

	//1.地址映射ioremap
	vir_base = ioremap(res_mem->start, (res_mem->end-res_mem->start+1));
	if (!vir_base) {
		printk("Map ADC addr %#x failed\n", res_mem->start);
		ret = -EIO;
		goto err_map;
	}

	//2.初始化ADC硬件以及全局变量
	init_waitqueue_head(&adc_wait);
	cur_ch = pdata->ch_def;
	max_ch = pdata->ch_max;
	min_ch = pdata->ch_min;

	//设置ADCCON寄存器, bit[2]=0: power on
	value = (pdata->soc_time<<6) | (cur_ch<<3);
	writel(value, (vir_base+ADCCON));

	//设置ADCINTENB寄存器, 使能中断
	writel(1, (vir_base+ADCINTENB));

	//设置分频寄存器
	value = (1<<15) | (pdata->presc<<0);
	writel(value, (vir_base+PRESCALERCON));

	//3.注册中断处理函数
	adc_irq = res_irq->start;
	ret = request_irq(adc_irq, adc_service, 0, 
			"myadc", NULL);
	if (ret) {
		printk("irq %d register failed\n", adc_irq);
		goto err_irq;
	}

	//4.创建device结构体，放到/sys/class/adc目录下
	//函数的最后一个参数是device的名字
	adc_dev = device_create(adc_class, &pdev->dev, 
			0, NULL, pdev->name);
	if (IS_ERR(adc_dev)) {
		printk("Cannot create /sys attribute files\n");
		ret = PTR_ERR(adc_dev);
		goto err_dev;
	}
	printk("Register ADC OK\n");
	return 0;
err_dev:
	free_irq(adc_irq, NULL);
err_irq:
	iounmap(vir_base);
err_map:
	return ret;
}

//platform_driver->remove
//当设备或驱动注销时调用
static int
adc_remove(struct platform_device *pdev)
{
	free_irq(adc_irq, NULL);
	device_destroy(adc_class, 0);
	writel((1<<2), (vir_base+ADCCON)); //ADC power off
	iounmap(vir_base);
	return 0;
}

//准备platform_device_id的数组，表明驱动支持哪些设备
static struct platform_device_id adc_ids[] = {
	{ "x6818_adc", 0 },
	{ "e4418_adc", 0 },
	{},
};

//准备platform_driver
static struct platform_driver adc_pdrv = {
	.probe 		= adc_probe,
	.remove 	= adc_remove,
	.id_table 	= adc_ids,
	.driver 	= {
		.name = "uplook-adc-attr",
	},
};

static int __init my_init(void)
{
	//创建新的class,每个class对应一种新类型的设备
	adc_class = class_create(THIS_MODULE, "adc");
	if (IS_ERR(adc_class)) {
		printk("Cannot create /sys/class/adc\n");
		return PTR_ERR(adc_class);
	}
	//class下面的每个设备都具有相同的属性文件
	adc_class->dev_attrs = adc_device_attrs;

	return platform_driver_register(&adc_pdrv);
}

static void __exit my_exit(void)
{
	platform_driver_unregister(&adc_pdrv);
	class_destroy(adc_class);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

