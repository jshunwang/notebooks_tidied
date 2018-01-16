/*******************************
 * 测试platform_device的准备和注册
 * 本例针对ADC硬件
 * 如果设备包括物理寄存器以及中断,应该封装到resource结构体中;
 * 设备的其他信息,包括初始化值等,可以自定义结构体来封装;
 * Author: zht
 * Date: 2017-10-27
 *******************************/
#include <linux/module.h>
//设备模型需要的头文件
#include <linux/platform_device.h>
#include <mach/irqs.h> //中断号
#include "regs_adc.h" //定义自定义的结构体adc_pdata

//定义物理信息
#define ADC_BASE	0xC0053000
#define ADC_SIZE	SZ_4K
#define ADC_IRQ		IRQ_PHY_ADC

//准备自定义的ADC初始化结构体
static struct adc_pdata adc_pdata = {
	.ch_def		= 0,	//默认通道号
	.ch_max		= 7,	//最大通道号
	.ch_min		= 0,	//最小通道号
	.presc		= 199,	//分频值,将输入的PCLK(200MHZ)分频为1MHZ
	.soc_time	= 0xF,	//Start Of Conversion Time
};

//准备资源数组,封装物理地址以及中断号
static struct resource adc_res[] = {
	[0] = {
		.start	= ADC_BASE,
		.end	= ADC_BASE + ADC_SIZE -1,
		.flags	= IORESOURCE_MEM,
	},
	[1] = {
		.start	= ADC_IRQ, 
		.end	= ADC_IRQ,
		.flags	= IORESOURCE_IRQ,
	},
};

//如果pdev支持注销, 应提供对应的release()方法
//比如platform_device是用kmalloc动态分配的,则应该在release方法中kfree
static void
adc_release(struct device *dev)
{
	printk("x6818_adc(-1): release()\n");
}

//准备platform_device
static struct platform_device adc_pdev = {
	.name			= "x6818_adc", 
	.id				= -1,
	.resource 		= adc_res,
	.num_resources	= ARRAY_SIZE(adc_res),
	.dev	= {
		.release = adc_release,
		.platform_data = &adc_pdata,
	},
};

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

