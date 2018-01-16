/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m00_init_exit.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			以内核tick为基准的，有内核维护的软件定时器timer_list
*			的使用
================================================================*/

/*****************************************************************
关键词：
	#include <linux/timer.h>	//timer_list
	#include <linux/sched.h>	//jiffies
			
static struct timer_list mytimer;
static void mytimer_func(unsigned long data){}
setup_timer(&mytimer, mytimer_func, (unsigned long)(&mytimer));
mod_timer(&mytimer, jiffies + 100);
del_timer(&mytimer);

*****************************************************************/

#include <linux/module.h>

//new head file
#include <linux/sched.h>
#include <linux/timer.h>

//定义一个定时器实例
static struct timer_list mytimer;

//定义软件定时器实例到时，时的执行函数
static void mytimer_func(unsigned long data)
{
	/******other codes********/

	//可以再次启动定时器，形成循环
	mod_timer((struct timer_list *)data, jiffies + 100);
}



static int __init my_init(void)
{
	/*********my codes***********/
	//设置定时器
	setup_timer(&mytimer, mytimer_func, (unsigned long)(&mytimer));
	//启动定时器
	mod_timer(&mytimer, jiffies + 100);
	return 0;
}

static void __exit my_exit(void)
{
	/*********my codes***********/
	//删除定时器
	del_timer(&mytimer);
	return ;	
}

module_init(my_init);//指定入口函数
module_exit(my_exit);//指定出口函数

MODULE_AUTHOR("JSW");//指定作者
MODULE_LICENSE("GPL");//模块许可声明
















