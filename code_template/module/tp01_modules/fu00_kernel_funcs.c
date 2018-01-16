/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m00_kernel_funcs.c
*   创 建 者：jshunwang
*   创建日期：2018年01月15日
*   描    述：
*			汇总kernel code 用到的函数
================================================================*/

//01>memory control

#include <linux/uaccess.h>
int copy_to_user(void __user *to, const void *from, int n)
int copy_from_user(void *to, const void __user *from, int n)

#include <linux/slab.h>
void *kmalloc(size_t s, gfp_t gfp)
void *kzalloc(size_t size, gfp_t flags)
void  kfree(void *p)

