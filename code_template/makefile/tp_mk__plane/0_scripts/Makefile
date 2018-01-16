#================================================================
#   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
#   
#   文件名称：Makefile
#   创 建 者：jshunwang
#   创建日期：2018年01月08日
#   描    述：
#			scripts目录下
#			定义变量,类似于c语言中的头文件
#================================================================

CC := gcc
CFLAGS := -Wall -O3
#gcc 选项-Wall,显示所有warning;选项-O，指定优化等级，后加数字
Libs = -lpthread
Target := 1_target/cal
Source := $(wildcard src/*.c)
Include:= $(wildcard src/*.h)
PATH_TOP:=$(PWD)

# makefile 中的变量中不能使用通配符赋值，wildcard函数的作用就是展开
# 通配符，然后再赋值给变量。此处代表的是当前路径下的src路径下的所有
# .c文件
Modules += add sub 2_main
# 一个文件夹代表一个功能模块，以第一级路径名作为模块名字
AllObjs := $(addsuffix /src/*.o, $(Modules))
# addsuffix:这个函数的作用是将变量$(Modules)中所有的直都加一个后缀，
# 后缀内容是"/src/*.o"
AllInc	:= $(addprefix -I$(PATH_TOP)/, $(addsuffix /src/, $(Modules)))

Objs := $(patsubst %.c,%.o,$(Source))
# patsubst:这个函数的作用是读取$(Source)中的各个变量名字，并且将各个
# 名字中的.c用.o替换。替换后的所有变量的名字做为返回直


