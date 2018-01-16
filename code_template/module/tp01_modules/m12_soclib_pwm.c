/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：m12_soclib_pwm.c
*   创 建 者：jshunwang
*   创建日期：2018年01月16日
*   描    述：
*			pwm 库的使用
================================================================*/

#include <linux/module.h>

//new head file
#include <linux/pwm.h>

//define the pwm id
#define PWM_ID	2

//定义一个pwm设备指针
struct pwm_device *dev;




static int __init my_init(void)
{
	//注册pwm
	dev = pwm_request(PWM_ID, "mypwm");
	if(IS_ERR(dev)){
		printk("cannot request pwm\n");	
		return PTR_ERR(dev);
	}

	//配置pwm，配置完后会默认打开
	pwm_config(dev, duty_ns, period_ns);

	//使能pwm和关闭pwm
	pwm_enable(dev);
	pwm_disable(dev);

/**如果pwm仍然无效，明确设置gpio为timer模式
#include <mach/soc.h> 	//nexell提供的底层函数
#include <cfg_type.h>	//GPIO号

#define PWM_IO	(PAD_GPIOX + X)
 
nxp_soc_gpio_set_io_func(PWM_IO, 2);
 */


	return 0;
}

static void __exit my_exit(void)
{
	//释放pwm
	pwm_free(dev);
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("JSW");
MODULE_LICENSE("GPL");


