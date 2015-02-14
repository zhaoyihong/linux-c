/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月12日 星期四 09时14分30秒

    fcntl函数用法
        3 对文件加锁
        注意 对文件加读锁 ,文件必须有读权限 ;写锁同理

        我们运行两个这个lock程序,其中第一个阻塞在unlock之前,第二个程序加锁时会返回
                lock fail: Resource temporarily unavailable  这样的错误
                说明写锁确实是排他的

        这个wlock程序中使用FD_SETLKW 表示是阻塞锁
************************************************************************/

#include  <iostream>
#include  <errno.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
using namespace std;

void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

int main(void)
{
    int fd = open("text.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(-1 == fd)
    {
       err_exit("open"); 
    }

    struct flock lock;
    bzero(&lock,sizeof(lock));
    lock.l_type = F_WRLCK; //写锁 (排他锁)
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0; //如果等于0表示整个文件都锁定
 
    puts("add wait lock,maybe block");
    if( fcntl(fd,F_SETLKW,&lock) != 0)
    {
        fcntl(fd,F_GETLK,&lock);
        //l_pid中写明了被哪个进程锁住了
        printf("file is locked by %d process!\n",lock.l_pid);
        err_exit("lock fail");
    }

    puts("lock success,press any key to unlock");
    getchar();

    //解锁
    lock.l_type = F_UNLCK;
    if(fcntl(fd,F_SETLKW,&lock) != 0)
    {
        err_exit("unlock fail");
    }

    puts("unlock success");


    return 0;
}
