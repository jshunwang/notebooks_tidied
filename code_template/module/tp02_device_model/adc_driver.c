/***********************************************************************************
 * linux device model——drive file
 * 自2.6的kernel版本以后，引入了设备模型的驱动code形式，将原来的统一写在
 * module中的device信息和drive信息分别提取出来建立在两个文件中dev和drv.
 * 本实例是drv文件的模板
 *		--创建并注册一个驱动视力，实例中制定了：
 *			--与哪些设备匹配
 *			--有哪那些操作方法
 **********************************************************************************/
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/ioport.h>
#include <linux/io.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
//platform总线需要的头文件
#include <linux/platform_device.h>
#include "adcinfo.h"

//定义变量
static void __iomem *vir_base;
static int cur_ch, min_ch, max_ch; //当前&最小&最大通道
static int adc_irq;	//中断号
static struct mutex adc_lock;
static wait_queue_head_t adc_wq;

//char驱动


//proc文件

//中断处理函数

//准备platform_driver
//在pdrv->probe中完成以前模块入口中的工作
static int
adc_probe(struct platform_device *pdev)
{
	struct resource *res_phy, *res_irq;
	struct adc_pdata *pdata;

	printk("%s(%d) : probe()\n", pdev->name, pdev->id);
	//1.从pdev中获得设备的硬件信息和初始化信息
	res_phy = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	res_irq = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res_phy || !res_irq) {
		printk("%s(%d) : cannot get enough resource\n", pdev->name, pdev->id);
		return -EINVAL;
	}
	pdata = pdev->dev.platform_data;
	//打印硬件和初始化信息
	printk("phy_base = %#x\n", res_phy->start);
	printk("phy_size = %#x\n", res_phy->end-res_phy->start+1);
	printk("irq = %d\n", res_irq->start);
	printk("def_ch = %d\n", pdata->def_ch);
	printk("min_ch = %d\n", pdata->min_ch);
	printk("max_ch = %d\n", pdata->max_ch);
	printk("presc  = %d\n", pdata->presc);
	printk("soc_time = %d\n", pdata->soc_time);

	//2.ioremap
	//3.初始化硬件及全局变量
	//4.注册中断
	//5.创建proc文件
	//6.注册miscdevice
	
	return 0;
}

//在pdrv->remove中完成以前模块出口中的工作
static int
adc_remove(struct platform_device *pdev)
{
	printk("%s(%d) : remove()\n", pdev->name, pdev->id);
	//free_irq()
	//misc_dereister()
	//remove_proc_entry()
	//将设备设置为power off
	//iounmap()
	return 0;
}

//准备platform_device_id结构体的数组，记录驱动支持哪些设备
static struct platform_device_id adc_ids[] = {
	{ "s5p6818-adc", 0 },
	{ "s5p4418-adc", 0 },
	{},
};

static struct platform_driver adc_pdrv = {
	.probe 	= adc_probe,	//驱动注册时调用的函数
	.remove	= adc_remove,	//驱动注销时调用的函数
	.id_table = adc_ids,	//本驱动能匹配的设备文件的的列表
	.driver = {				 	//struct device_driver 一个描述驱动本身属性的结构体
		.name = "uplook-adc",	//驱动自己的名字
	},
};

static int __init my_init(void)
{
	//注册pdrv
	return platform_driver_register(&adc_pdrv);
}
static void __exit my_exit(void)
{
	//注销pdrv
	platform_driver_unregister(&adc_pdrv);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

