/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m11_register_access.c
*   创 建 者：jshunwang
*   创建日期：2018年01月16日
*   描    述：
*			由于处理器内部使用了MMU内存管理单元，所以如果想直接操作
*			soc上三总线上的寄存器必须要将物理地址映射到虚拟地址上
================================================================*/

//new head file
#include <linux/ioport.h>
#include <linux/io.h>

//查找物理基地址，偏移，和映射大小
#define DEV_BASE	0x11000000
#define DEV_OFFSET	0x0010
#define DEV_SIZE	SZ_4K

//定义映射后的虚拟地址存储变量
static void __iomem *vir_base;

//地址映射要在入口函数内完成
vir_base = ioremap(DEV_BASE, DEV_SIZE);
if(!vir_base){
	printk("<0>cannot ioremap\n");
	return -EIO;
}

//地址映射要在出口函数内取消
iounmap(vir_base);

//寄存其的读写要使用专用的函数

/* 8位寄存器 */
char value;
value = readb(vir_base + offset);
writeb(value, (vir_base) + offset);


/* 16位寄存器 */
short value;
value = readw(vir_base + offset);
writew(value, (vir_base) + offset);

/* 32位寄存器 */
int value;
value = readl(vir_base + offset);
writel(value, (vir_base) + offset);

/* 64位寄存器 */
u64 value;
value = readq(vir_base + offset);
writeq(value, (vir_base) + offset);



