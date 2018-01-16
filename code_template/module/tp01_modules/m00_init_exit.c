/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m00_init_exit.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			编写一个module的最基本结构	
*				--module入口函数
*				--module出口函数
================================================================*/

/*****************************************************************
关键词：
		#include <linux/module.h>
			
		module_init(my_init);//指定入口函数
		module_exit(my_exit);//指定出口函数

		MODULE_AUTHOR("JSW");//指定作者
		MODULE_LICENSE("GPL");//模块许可声明
*****************************************************************/

#include <linux/module.h>

static int __init my_init(void)
{
	/*********my codes***********/
	return 0;
}

static void __exit my_exit(void)
{
	/*********my codes***********/
	return ;	
}

module_init(my_init);//指定入口函数
module_exit(my_exit);//指定出口函数

MODULE_AUTHOR("JSW");//指定作者
MODULE_LICENSE("GPL");//模块许可声明
















