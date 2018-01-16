/****************************
 * ADC设备的头文件
 * 可以在头文件中定义一个结构体, 把初始化信息放到结构体中;
 * 还可以把寄存器的偏移值也放入头文件中;
 * Author: zht
 * Date: 2017-10-27
 ****************************/
#ifndef	__REGS_ADC_H
#define __REGS_ADC_H

//定义结构体,存储初始化信息(按设备特征定义,谁写驱动谁定义)
//在准备platform_device时,准备初始化结构体;
//在platform_driver中,取出该结构体使用;
struct adc_pdata {
	int ch_def;	//默认通道号
	int ch_max;	//最大通道号
	int ch_min;	//最小通道号
	int presc;	//分频值,使用时加1
	int soc_time; //Start of Conversion Time
};

//定义ADC寄存器的偏移值(基地址放到resource结构体中)
#define ADCCON 			0x00 
#define ADCDAT 			0x04 
#define ADCINTENB 		0x08 
#define ADCINTCLR 		0x0C 
#define PRESCALERCON 	0x10

#endif // __REGS_ADC_H

