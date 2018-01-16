/*******************************
 * 定义ADC设备的头文件
 * 可以定义寄存器偏移
 * 可以定义初始化结构体，在platform_device和platform_driver中使用
 * Author: zht
 * Date: 2018-01-15
 *******************************/
#ifndef	__ADCINFO_H
#define __ADCINFO_H

//定义寄存器的偏移
#define ADCCON 			0x00 
#define ADCDAT 			0x04 
#define ADCINTENB 		0x08 
#define ADCINTCLR 		0x0C 
#define PRESCALERCON 	0x10

//自己定义几个结构体，用于封装初始化信息
//结构体在platform_device中初始化，platform_driver中可以拿来用
struct adc_pdata {
	int def_ch;
	int min_ch;
	int max_ch;
	int presc;
	int soc_time;
};

#endif //__ADCINFO_H

