/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m13_kernel_time.c
*   创 建 者：jshunwang
*   创建日期：2018年01月16日
*   描    述：
*
================================================================*/

//内核中记录着两个时间

//相对时间--相对开机那一时刻，用两个全局变量记录
#include <linux/sched.h>
unsigned long jiffies;	//32bit--4G 
unsigned long long jiffies_64; //64bit--4G*4G

//绝对时间--相对1970年01月01日00:00:00,用两个结构体存储
struct timeva tval;
do_gettimeofday(&tval);

struct timespec tspec;
getnstimeofday(&tspec);


