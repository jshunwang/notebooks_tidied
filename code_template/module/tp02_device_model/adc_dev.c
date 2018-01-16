/*************************************************************************
 * linux device model——device file
 * 自2.6的kernel版本以后，引入了设备模型的驱动code形式，将原来的统一写在
 * module中的device信息和drive信息分别提取出来建立在两个文件中dev和drv.
 * 本实例是dev文件的模板,
 *		--建立并注册一个设备实体，包含：
 *			--设备的属性(供用户使用的,驱动编写人员定义的)
 *			--设备使用所占用的处理器有限资源
 ************************************************************************/
#include <linux/module.h>			//建立module
#include <linux/platform_device.h>	//建立三总线下的设备文件
#include <mach/irqs.h>				//中断号
#include "adcinfo.h"				//自定义的头文件，包含了设备硬件信息

//定义常量
#define ADC_BASE	0xC0053000
#define ADC_SIZE	SZ_4K
#define ADC_IRQ		IRQ_PHY_ADC

//准备资源数组
static struct resource adc_res[] = {
	[0] = {	//物理地址					//struct resourec 用来描述处理器的有限的资源，包含物理内存地址，中断号等
		.start 	= ADC_BASE,				//资源的起始标号
		.end	= ADC_BASE+ADC_SIZE-1,	//资源的结束标号
		.flags	= IORESOURCE_MEM,		//描述该资源的标志位，比如可以用来描述资源类型
	},
	[1] = {	//中断号
		.start	= ADC_IRQ,
		.end	= ADC_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

//准备初始化结构体,根据设备的使用情况，驱动编写人员自行定义的一个结构体
static struct adc_pdata pdata = {
	.def_ch		= 1,
	.min_ch		= 0,
	.max_ch		= 7,
	.presc		= 199,
	.soc_time	= 0xF,
};

//device->release方法，在pdev注销时调用
//如果pdev是用kmalloc来分配的空间，应该在release中用kfree释放空间
static void adc_release(struct device *dev)
{
	printk("s5p6818-adc(-1) : release()\n");
}


//step02 构造platform_device对象
static struct platform_device adc_pdev = {
	.name	= "s5p6818-adc",		//设备名--可能出现同名
	.id		= -1,					//设备id--用于区分同设备名的情况
	.num_resources = ARRAY_SIZE(adc_res),	//与该设备相关的处理器资源（寄存器物理地址、中断号等）
	.resource = adc_res,					//需要几组处理器资源
	.dev	= {								//struct device描述设备属性的结构体
		.platform_data 	= &pdata,			//指向的是一个用于描述设备属性的自己定义的一个结构体
		.release 		= adc_release,		//回调函数指针，rmmod设备时使用该函数收尾
	},
};

//step01 register platform device
static int __init my_init(void)
{
	//注册platform_device
	return platform_device_register(&adc_pdev);
}

static void __exit my_exit(void)
{
	//注销platform_device
	platform_device_unregister(&adc_pdev);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("ZHT");
MODULE_LICENSE("GPL");

