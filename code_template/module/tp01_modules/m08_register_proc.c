/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m08_register_proc.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			用户可以通过/proc/的某个文件读取设备文件的属性信息，
*			本例的功能就是，使module中添加创建/pro/xxxinfo的功能
================================================================*/

/*****************************************************************
关键词：
	#include <linux/proc_fs.h>	//proc文件的结构体、注册函数等
	#include <linux/seq_file.h>	//seq_printf()


*****************************************************************/

#include <linux/module.h>

//new head file
#include <linux/proc_fs.h>	//proc文件的结构体、注册函数等
#include <linux/seq_file.h>	//seq_printf()

//定义变量，作为设备文件属性打印到/proc/proctestinfo
static int ioctl_value;

//定义proc文件中现实的内容
static int my_proc_show(struct seq_file *sf, void *data)
{
	seq_printf(sf, "ioctl_value: %d\n", ioctl);
	return 0;
}

//为自己创建的proc文件定义open函数（带show功能）
static int my_proc_open(struct inode *inode, struct file *filp)
{
	single_open(filp, my_proc_show, NULL);
	return 0;
}

//定义proc操作函数实体
static struct file_operations proc_fops = {
	.owner	= THIS_MODULE,
	.open	= my_proc_open,		//自己定义的open proc文件的函数
	.release	= single_release,
	.read		= seq_read,
};

static int __init my_init(void)
{
	int ret;
	/*********my other codes***********/
	struct proc_dir_entry *pfile;	//指向一个proc文件的指针

	//创建proc文件
	pfile	=proc_create_data(const char *name, 	//"proctestinfo"
					umode_t mode,					// 0444
					struct proc_dir_entry *parent,	// NULL
					const struct file_operations *proc_fops,	//proc_fops
					void *data);					// NULL
	if(!pfile){
		printk("<0>create /proc/xx failed\n");	
		return -EINVAL;
	}
	printk("<0>dev: register miscdev ok\n");	

	return 0;
}

static void __exit my_exit(void)
{
	/*********my other codes***********/
	remove_proc_entry(const char *name, 	//"proctestinfo"
					struct proc_dir_entry *parent);	// NULL

	printk("<0>dev: deregister miscdev ok\n");	
	return ;	
}

module_init(my_init);//指定入口函数
module_exit(my_exit);//指定出口函数

MODULE_AUTHOR("JSW");//指定作者
MODULE_LICENSE("GPL");//模块许可声明
















