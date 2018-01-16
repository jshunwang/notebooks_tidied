/*=======================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：readme.txt
*   创 建 者：jshunwang
*   创建日期：2018年01月10日
*   描    述：
*
=======================================================================*/

1.简介
makefile模板——用于平级多文件编译。

2.组成
共计三个Makefile文件：1> tp_mk_plane/Makefile
						 //顶层makefile ，该路径下执行make，模板内所有源
						 //文件
					  2> tp_mk_plane/0_scripts/Makefile
					  	 //用于指定源文件和目标文件，不用再该目录下执行m-
					  	 //ake命令

					  3> tp_mk_plane/2_main 
									  /add
									  /sub
						//ps: 3>路径中的Makefile内容是一样的,在相应的路径
						//下执行make命令可以独立的编译各个功能模块。

3.模板内容展示

顶层编译前（即执行最顶层的make前）

tp_mk_plane				/*****************使用说明*******************/			
├── 0_scripts			
│   └── Makefile		//指定编编译源文件和目标文件，变量名为路径短名
├── 1_target			//存放最终的目标文件
├── 2_main				//main函数路径	
│   ├── Makefile		//模块级别的makefile，和其他功能模块中的一样
│   └── src				//src下存放源文件和头文件，以及模块的头文件
│       ├── add.h
│       ├── cal.c
│       ├── cal.h
│       └── sub.h
├── add					//某个功能函数的路径
│   ├── Makefile		//该功能函数的Makefile文件，在该模块路径下，可以
│   └── src				//单独执行make，达到只编译该功能模块下的源文件,
│       ├── add.c		//只能是一组.c .h文件
│       └── add.h
├── Makefile			//顶层Makefile
├── readme.txt			//本说明文档
└── sub					//某个功能函数的路径
    ├── Makefile		//......
	└── src
		├── sub.c
	    └── sub.h

顶层编译后（即执行最顶层的make后）

.
├── 0_scripts
│   └── Makefile
├── 1_target
│   └── cal
├── 2_main
│   ├── Makefile
│   └── src
│       ├── add.h
│       ├── cal.c
│       ├── cal.h
│       ├── cal.o
│       └── sub.h
├── add
│   ├── Makefile
│   └── src
│       ├── add.c
│       ├── add.h
│       └── add.o
├── Makefile
├── readme.txt
└── sub
    ├── Makefile
	└── src
		├── sub.c
		├── sub.h
		└── sub.o













































