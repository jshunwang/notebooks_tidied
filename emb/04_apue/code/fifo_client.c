/*================================================================
*   Copyright (C) 2017 Sangfor Ltd. All rights reserved.
*   
*   文件名称：fifo_client.c
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

#define FIFOPATH "/tmp/fifotestfile"
#define SIZE 11

int main(void)
{
	int fd;
	char buf[SIZE] = {};
	
	fd = open(FIFOPATH, O_RDONLY);
	if(fd < 0){
		perror("open()");	
		exit(1);
	}
	read(fd, buf, SIZE );
	puts("hahah");
	puts(buf);

	return 0;
}
