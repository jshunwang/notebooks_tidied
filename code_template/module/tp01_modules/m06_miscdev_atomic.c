/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m06_miscdev_atomic.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			当设计到对设备文件进行写操作时应该添加mutex lock,本例中
*			中使用ioctl，复位module中的一个全局变量，因为本例没有
*			设计到真正的设备，如果有设备，这个写操作还可以是重新设置
*			该设备的寄存器。如果临界区只是一个变量，这个变量只是进行
*			了类似 ++ --等这样的简单操作，那么mutex_lock就不太合适
*			了可以将该变量声明为atomic_t变量，这个变量类型由内核维护
*			能够确保是原子操作。
================================================================*/

/*****************************************************************
关键词：
	#include <linux/atomic.h>

	//定义锁实体
	static atomic_t atomicvalue;

	//临界区
	int write_func(){
		atomic_inc(&atomicvalue);	
		atomic_dec(&atomicvalue);	
		atomic_set(&atomicvalue, 1);	
		atomic_read(&atomicvalue);
	}


*****************************************************************/

#include <linux/module.h>
#include <linux/fs.h>		//file_operations
#include <linux/uaccess.h>	//copy_to/from_user
#include <linux/miscdevice.h>	//miscdevice

//new head file
#include <linux/atomic.h>

//定义ioctl命令号
#define COMMAND_TYPE	'C'
	//不带参数命令, 命令号为1
#define COMMAND_CLEAR		_IO(COMMAND_TYPE, 1)

//定义变量，
static atomic_t ioctl_value;


//准备struct miscdevice 类型实体miscdev的操作函数

	//定义函数的具体内容
static long miscdev_ioctl(struct file *filp, unsigned int req, unsigned long arg)
{
	}
	//访问临界区
	switch(req){
		case COMMAND_CLEAR:
			atomic_set(&iotclvalue, 0);	
			break;
	}
	return 0;
}
	
	//miscdev的操作函数挂到一个struc file_operations的结构体实体上
static struct file_operations dev_fops = {
	.owner	= THIS_MODULE,	//指定所属为当前module
	.unlocked_ioctl = miscdev_ioctl,
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
















