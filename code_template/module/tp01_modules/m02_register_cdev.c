/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m02_register_cdev.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			手动建立删除设备文件
*			$ sudo mknod /dev/mydev dev_type major_id minor_id
*			手动设置设备id:major_id和minor_id
================================================================*/

/*****************************************************************
关键词：
		#include <linux/fs.h>		//file_operations
		#include <linux/uaccess.h>	//copy_to/from_user
		#include <linux/cdev.h>		//MKDEV

*****************************************************************/

#include <linux/module.h>

//new head file
#include <linux/fs.h>		//file_operations
#include <linux/uaccess.h>	//copy_to/from_user
#include <linux/cdev.h>		//MKDEV(ma,mi)|cdev_add()|cdev_del()

//准备设备号，在/proc/devices中找一个没有用过的,假设是10\10
#define DEV_MAJOR	10
#define DEV_MINOR	10

//定义变量
static dev_t dev_id;	//一个整数用于存放主次设备号合成后的设备号
static struct cdev dev;	//创建一个字符设备的实体

//准备struct cdev类型实体dev的操作函数

	//定义函数的具体内容
		//open 省略的话默认总是打开成功
static int dev_open(struct inode *inode, struct file *filp)
{
	/**********my code**************/
	return 0;
}

		//release 省略的话默认总是打开成功
static int dev_release(struct inode *inode, struct file *filp)
{
	/**********my code**************/
	return 0;
}

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
	//dev的操作函数挂到一个struc file_operations的结构体实体上
static struct file_operations dev_fops = {
	.owner	= THIS_MODULE,	//指定所属为当前module
	.open	= dev_open,
	.release= dev_release,
	.read	= dev_read,
	.write	= dev_write,
};

static int __init my_init(void)
{
	int ret;
	/*********my other codes***********/
	//通过主次设备号合成设备号
	dev_id	= MKDEV(DEV_MAJOR, DEV_MINOR);
	//用dev_fops的文件操作函数初始化，dev设备实体
	cdev_init(&dev, &dev_fops);
	//注册dev
	ret = cdev_add(&dev, dev_id, 1);
	if(ret){
		printk("<0>dev: register dev failed\n");	
		return ret;
	}
	printk("<0>dev: register dev ok\n");	

	return 0;
}

static void __exit my_exit(void)
{
	/*********my other codes***********/
	//去除设备
	cdev_del(&dev);
	printk("<0>dev: deregister dev ok\n");	
	return ;	
}

module_init(my_init);//指定入口函数
module_exit(my_exit);//指定出口函数

MODULE_AUTHOR("JSW");//指定作者
MODULE_LICENSE("GPL");//模块许可声明
















