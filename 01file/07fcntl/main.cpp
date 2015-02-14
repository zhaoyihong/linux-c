/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月12日 星期四 09时14分30秒

    fcntl函数用法
        1 复制文件描述符和 2 设置文件状态标识

************************************************************************/

#include  <iostream>
#include  <errno.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <stdio.h>
#include  <stdlib.h>

using namespace std;

void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

//使用fcntl来实现dup2 (复制文件描述符)
int my_dup2(int oldfd,int newfd)
{
    //第二个参数是赋值文件命令,第三个是开始搜索可用描述符的起始点
    int ret = fcntl(oldfd,F_DUPFD,newfd);
    if(-1 == ret)
    {
        err_exit("fcntl");
    }

    if(newfd != ret)
    {
        fprintf(stderr,"newfd is not valid",18);
        return -1;
    }

    return ret ;
}

void set_flag(int fd,long flag)
{
    long flags = fcntl(fd,F_GETFL,0);
    if(flags == -1)
    {
        err_exit("fcntl");
    }
    int ret = fcntl(fd,F_SETFL,flags | flag);
    if(ret == -1)
    {
        err_exit("fcntl");
    }
}

void clr_flag(int fd,long flag)
{
    long flags = fcntl(fd,F_GETFL,0);
    if(flags == -1)
    {
        err_exit("fcntl");
    }

    int ret = fcntl(fd,F_SETFL,flags & ~flag);
    if(ret == -1)
    {
        err_exit("fcntl");
    }
}

int main(void)
{
    //复制文件描述符
    int fd = open("text.txt",O_WRONLY|O_CREAT,0644);
    if(-1 == fd)
    {
       err_exit("open"); 
    }

    int fd5 = my_dup2(fd,102);
    if(-1 == fd5)
    {
        exit(-1);
    }
    write(fd5,"fd5",3);

    // 改变文件状态标识
    set_flag(0,O_NONBLOCK);//设置非阻塞位
    char buf[1024] = {0};
    int ret = read(0,buf,1024);//立即返回-1 表示资源暂且不可用, 
    cout << ret << endl;
    puts(buf);
    
    clr_flag(0,O_NONBLOCK); //设置为阻塞
    ret = read(0,buf,1024);//阻塞中 
    cout << ret << endl;
    puts(buf);


    return 0;
}
