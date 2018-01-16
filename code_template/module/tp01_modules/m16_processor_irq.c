/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m16_processor_irq.c
*   创 建 者：jshunwang
*   创建日期：2018年01月16日
*   描    述：
*
================================================================*/

#include <mach/irqs.h>	//记录了全部的偏上设备和gpio中断号

//可以通过GPIO号获得该gpio的中断号
//例子：
#include <linux/gpio.h>	//gpio库
#include <cfg_type.h>	//GPIO号

#define KEY1 	(PAD_GPIO_A+28)
int irq_num = gpio_to_irq(KEY);

//中断号和中断处理函数指针由内核管理，所以剩下的工作就是给指定中断
//号的中断注册中断处理函数，中断处理函数中，不能有睡眠动作
//例子：

#include <linux/interrupt.h>
#include <mach/irqs.h>
//gpio
#include <cfg_type.h>

//确定中断号
#define KEY_IRQ 	(IRQ_GPIO_ASTART +28)

//中断处理函数
static irqreturn_t key_service(int irq, void *data)
{

	return IRQ_HANDLED;	//IRQ_NONE 代表这不是一个中断
}

//注册中断处理函数
u32 flags = IRQF_TRIGGER_FALLING;
int ret;
ret = request_irq(KEY_IRQ,	//中断号
		key_service,		//中断处理函数指针
		flags,				//中断标志
		"mykey",			//中断名字
		data,				//传递给处理函数的参数
		);
if(ret){
	printk("cannot register interrupt handler\n");
	return ret;
}

//注销处理函数
free_irq(irq, 	//中断号
		data);	//中断处理函数的参数










