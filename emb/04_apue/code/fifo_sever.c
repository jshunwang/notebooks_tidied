/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：fifo_sever.c
*   创 建 者：jshunwang
*   创建日期：2017年12月05日
*   描    述：
*
================================================================*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define FIFOPATH "/tmp/fifotestfile"
#define SIZE 11

int main(void)
{
	int fd;
	int err;

	err = mkfifo(FIFOPATH, 666);
	if(err < 0){
		puts(strerror(errno));	
	}
	if(err == 0){
		fd = open(FIFOPATH, O_WRONLY);
		if(fd < 0){
			perror("open()");	
			exit(1);
		}
		write(fd, "i am sever\n",SIZE );
	}
	
	remove(FIFOPATH);

	return 0;
}
