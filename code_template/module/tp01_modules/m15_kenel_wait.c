/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m15_kenel_wait.c
*   创 建 者：jshunwang
*   创建日期：2018年01月16日
*   描    述：
*			内核创建了等待队列机制，用于较长时间的延时（睡眠），
*		ps：个人认为是一种通知机制而已。
================================================================*/

//new head file
#include <linux/sched.h>
#include <linux/wait.h>

//创建一个等待队列实例,根据唤醒条件不同可以创建多个
wait_quue_head_t mywait;

//模块入口中初始化这个等待队列
init_waitqueue_head(&mywait);

//阻塞的写
ssize_t my_write(...)
{
	//如果写满，则等待	
	if( wp == buf_size){
		//wait_event(mywait, wp != buf_size);
		wait_event_interruptible(mywait, wp != buf_size);
		if(ret != 0){
			return -ERESTARTSYS;	
		}
	}

	...
}

int my_ioctl(...)
{
	wp = 0;
	wake_up(&mywait);

	...
}
