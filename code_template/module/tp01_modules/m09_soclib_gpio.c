/******************************
 * led的char驱动例子3
 * 采用gpio库控制gpio引脚输出的电平;
 * 支持char驱动，通过ioctl命令来控制LED;
 * 通过/proc/ledinfo文件获得灯的当前信息
 * Author: zht
 * Date: 2018-01-08
 ******************************/
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
//gpio库需要的头文件
#include <linux/gpio.h>　//gpip_request ...
#include <cfg_type.h> //gpio号

//定义常量和ioctl号
#define LED_NUM		4

#define LED_TYPE	'L'
#define LED_ON		_IOW(LED_TYPE, 1, int)
#define LED_OFF		_IOW(LED_TYPE, 2, int)
#define LED_ALLON	_IO(LED_TYPE, 3)
#define LED_ALLOFF	_IO(LED_TYPE, 4)

//定义变量，用数组保存gpio号
static int led_gpios[LED_NUM] = {
	PAD_GPIO_B+26,
	PAD_GPIO_C+11,
	PAD_GPIO_C+7,
	PAD_GPIO_C+12,
};

//准备/proc/ledinfo文件的file_ops
static int 
led_proc_show(struct seq_file *sf, void *data)
{
	//用for循环查看４个灯的当前状态
	//用gpio_get_value获得gpio的当前电平
}

．．．

//准备char驱动需要的file_ops
static long 
led_ioctl(struct file *filp, unsigned int req, unsigned long arg)
{
	//实现４个ioctl命令
	//用gpio_set_value(gpio号, 0|1)来设置IO电平高低
}

static int __init my_init(void)
{
	int ret, i, j;
	//1.申请gpio号，led默认灭
	for (i=0; i<LED_NUM; i++) {
		ret = gpio_request(led_gpios[i], "myled");
		if (ret) {
			printk("LED: request gpio %d failed\n", led_gpios[i]);
			goto err_io;
		}
		gpio_set_value(led_gpios[i], 1);
	}
	//2.创建proc文件
	//3.注册miscdevice
	printk("LED: register misc OK\n");
	return 0;
err_io:
	for (j=0; j<i; i++)
		gpio_free(led_gpios[j]);
	return ret;
}

static void __exit my_exit(void)
{
	int i;
	misc_deregister(&led_misc);
	remove_proc_entry("ledinfo", NULL);
	for (i=0; i<LED_NUM; i++)
		gpio_free(led_gpios[i]);
}





