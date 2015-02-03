/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月22日 星期四 21时15分26秒
 ************************************************************************/

#include<iostream>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <stdio.h>
#include  <unistd.h>

using namespace std;

void err_exit(const char*msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{

    int fd = open("hole.txt",O_WRONLY|O_TRUNC|O_CREAT,0644);
    if(-1 == fd)
    {
        err_exit("open");
    }


    write(fd,"ABCD",4);

    //lseek超过文件大小时,产生一个空洞,使用du查看文件大小,其实这些空洞并没有存放在磁盘中
    int ret = lseek(fd,1024*1024,SEEK_CUR);
    if(-1 == ret)
    {
        perror("lseek");
    }

    //继续写入
    write(fd,"FGHI",4);

    
    close(fd);

    return 0;
}
