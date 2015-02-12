/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月12日 星期四 09时14分30秒

一个或者多个进程多次打开同一个文件会产生多个文件描述符,这些文件描述符各自有自己的文件表,文件表指向同一个i结点

使用dup复制文件描述符时,多个文件描述符将指向同一个文件表,因此可以共享文件偏移量和文件状态标识(RD WR APPEND 等)

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

//使用fcntl来实现dup2
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

int main(void)
{
    int fd = open("text.txt",O_WRONLY|O_CREAT,0644);
    if(-1 == fd)
    {
       err_exit("open"); 
    }

    //dup1 复制文件描述符,新的文件描述符使用可用描述符中的最小的
    int fd2 = dup(fd);
    if(-1 == fd2)
    {
        err_exit("dup");
    }

    //值得注意的是,两个文件描述符指向同一个文件表,因此共享文件偏移量
    write(fd2,"hello",5);
    write(fd,"world",5);
    //之后文件中有helloworld信息

    
    //dup2,将文件描述符,复制给指定的文件描述符
    int fd3 = dup2(fd,100);
    if(-1 == fd3)
    {
        err_exit("dup2");
    }

    write(fd3,"!!!\n",4);
    //文件中现在是helloworld!!!

    //但是文件的flag不能被复制,比如O_CLOEXEC 因此又有个dup3来指定flag
    
    int fd4 = dup3(fd,101,O_CLOEXEC);
    if(-1 == fd4)
    {
        err_exit("dup3");
    }

    int fd5 = my_dup2(fd,102);
    if(-1 == fd5)
    {
        exit(-1);
    }
    write(fd5,"fd5",3);


    return 0;
}
