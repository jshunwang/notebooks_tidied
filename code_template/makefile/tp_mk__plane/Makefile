#================================================================
#   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
#   
#   文件名称：Makefile
#   创 建 者：jshunwang
#   创建日期：2018年01月08日
#   描    述：
#			总控Makefile，位于第一级目录
#			将所有".o"文件链接生成可执行文件
#================================================================

include ./0_scripts/Makefile
#展开./scripts/Makefile文件作为本Makfile的一部分，类似c语言的头文件

modules_make = $(MAKE) -C $(1);
# $(MAKE):make定义了很多默认的变量,使用make -p可以查看所有预定义的变
# 量的当前的直，MAKE也是其中一个，代表make这个命令本身
# -C	:make -C，-C选项的作用是不执行任何操作，立即跳转到后面的选项
#		参数所表示的路径下，执行该路径下的Makefile		
# $(1)  :首先要说一下makefile中的变量是用来存储字符串的，可能不是一个
#		字符串，不同的字符串之间用冒号隔开，也就是说一个变量的直可以
#		是多个，那么可以用$(数字)，从左到右表示$(数字)位置所在的变量
#		的直的变量。
# 所以最后这句话的意思就是：有一个变量叫做modules_make,要将等号后面的
# “$(MAKE) -c $(1) ;”这个字符串付给他，但是这个字符串中有两个位置需要
# 变量MAKE确定，和modules_make这个变量中的一个标号为$(1)的变量确定。
#

modules_clean = $(MAKE) clean -C $(1);

.PHONY: all mm mc clean
# 我们使用make时，使用的是make+ 目标文件，当使用该命令后会首先检查当前
# 路径下是否有最新的目标文件，如果有就不执行了。.PHONY的第一个作用就是
# 屏蔽makefile中的这些目标名字，可以使再次执行,因为伪目标不会,生成文件
# 。这里的作用就是声明后面的目标是伪目标,即不会生成目标文件,注意.phony
# 是makef-ile，的关键字，他本身不是目标。

all: $(Target)

mm:
	$(foreach n, $(Modules), $(call modules_make , $(n)))
# @ 代表隐士执行
# foreach:将第二个变量中的直取出一个，放到第一个变量中，然后执行第三个
# 变量中的内容
# call	 :将第二个、第三个...给变量modules_make中的$(1), $(2)...赋值

mc:
	$(foreach n, $(Modules), $(call modules_clean , $(n)))

$(Target) : mm
	$(CC) $(CFLAGS) -o $(Target) $(AllObjs) $(Libs)
	echo $(Target) make done!

clean:mc
	rm -rf $(Target)
# -r 代表目录文件， -f 代表忽视不存在文件
	echo clean done!
















