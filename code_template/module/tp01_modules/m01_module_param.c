/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m01_module_param.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			insmod module 时可以传入参数的直，这些参数是模块中的全
*			局变量，代表module的属性信息。
*			$ sudo insmod m01_module_param.ko param=10
================================================================*/

/*****************************************************************
关键词：
		#include <linux/module.h>

		module_param(name, type, perm);
*****************************************************************/

#include <linux/module.h>

static int param = 0;

module_param(param, int, 06444);

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
















