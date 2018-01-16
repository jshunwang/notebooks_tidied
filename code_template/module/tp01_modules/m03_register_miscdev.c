/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m02_register_cdev.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			自动建立删除设备文件
*			自动设置设备id:major_id和minor_id
================================================================*/

/*****************************************************************
关键词：
		#include <linux/fs.h>		//file_operations
		#include <linux/uaccess.h>	//copy_to/from_user
		#include <linux/miscdevice.h>	//miscdevice

*****************************************************************/

#include <linux/module.h>

//new head file
#include <linux/fs.h>		//file_operations
#include <linux/uaccess.h>	//copy_to/from_user
#include <linux/miscdevice.h>	//miscdevice



//准备struct miscdevice 类型实体miscdev的操作函数

	//定义函数的具体内容

static ssize_t dev_write(struct file *filp, const char __user *buf, size_t count)
{
	ssize_t cnt;
	/**********my code**************/
	
	return cnt;
}

static ssize_t dev_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t cnt;
	/**********my code**************/
	
	return cnt;
}
	//miscdev的操作函数挂到一个struc file_operations的结构体实体上
static struct file_operations dev_fops = {
	.owner	= THIS_MODULE,	//指定所属为当前module
	.open	= dev_open,
	.release= dev_release,
	.read	= dev_read,
	.write	= dev_write,
};

//创建 struct miscdevice类型的实体代表这个字符设备miscdev
static struct miscdevice miscdev = {
	.minor	= MISC_DYNAMIC_MINOR,	//动态分配
	.name	= "mymiscdev",			//指定/dev/下对应的设备文件名字
	.mode	= 0666,					//perm设置
	.fops	= &buf_fops,			//指定该设备的文件操作函数集
}

static int __init my_init(void)
{
	int ret;
	/*********my other codes***********/
	//注册dev
	ret = misc_register(&miscdev);
	if(ret){
		printk("<0>dev: register miscdev failed\n");	
		return ret;
	}
	printk("<0>dev: register miscdev ok\n");	

	return 0;
}

static void __exit my_exit(void)
{
	/*********my other codes***********/
	//去除设备
	misc_deregister(&miscdev);
	printk("<0>dev: deregister miscdev ok\n");	
	return ;	
}

module_init(my_init);//指定入口函数
module_exit(my_exit);//指定出口函数

MODULE_AUTHOR("JSW");//指定作者
MODULE_LICENSE("GPL");//模块许可声明
















