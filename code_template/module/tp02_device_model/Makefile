# 编译ko模块的Makefile
# 首先要找到模块运行的内核，利用内核中的根Makefile进行编译
# 如果要编译开发板上的模块，需要把X6818_B/kernel/Makefile的第196行的CROSS_COMPILE修改为:
# CROSS_COMPILE := arm-linux-
# Author: zht
# Date: 2017-12-29

#KERNEL := /usr/src/linux-headers-`uname -r`/
KERNEL 	:= /home/jsw/note/uplookng_tcb/zht/class-e6818/X6818_B/x6818_linux_160719/kernel
obj-m 	:= adc_dev.o adc_driver.o
myko	:= adc_dev.ko adc_driver.ko
#mycfile := adc01.c
#myelf	:= adc01


all:
	make -C $(KERNEL) M=`pwd` modules
#	arm-linux-gcc -o $(myelf) $(mycfile)
#	cp $(myelf) /home/jsw/note/uplookng_tcb/zht/class-e6818/test/
	cp $(myko)  /home/jsw/note/uplookng_tcb/zht/class-e6818/test/
clean:
	make -C $(KERNEL) M=`pwd` clean
	rm -f $(myelf)
