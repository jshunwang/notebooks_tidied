# 用于编译.ko模块的Makefile
# 必须找到要运行内核对应的根Makefile，利用该Makefile进行编译
# 如果编译在pc上运行的模块，找4.4.x内核对应的根Makefile
# 如果编译在6818上运行的模块，找3.4.49内核对应的根Makefile

#KERNEL := /usr/src/linux-headers-`uname -r`/
KERNEL 	:= /home/jsw/note/uplookng_tcb/zht/class-e6818/X6818_B/x6818_linux_160719/kernel
obj-m := adc_pdev.o adc_attribute.o
myko  := adc_pdev.ko adc_attribute.ko
#myelf := adc01
#mysrc := adc01.c

all:
	make -C $(KERNEL) M=`pwd` modules
	cp $(myko)  /home/jsw/note/uplookng_tcb/zht/class-e6818/test/
#	arm-linux-gcc -o $(myelf) $(mysrc)
#	cp $(myelf) /home/jsw/note/uplookng_tcb/zht/class-e6818/test/
clean:
	make -C $(KERNEL) M=`pwd` clean
#	rm -f $(myelf)

