/*************************************************************************
	> File Name: mydup2.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月12日 星期四 11时11分58秒

    不使用fcntl来实现dup2
************************************************************************/

#include<iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <string.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>

using namespace std;

void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

int mydup2(int oldfd,int newfd)
{
    //1判断oldfd使用可以使用
    int ret = dup(oldfd);
    if(-1 == ret)
    {
        const char *errormsg = "oldfd is invalid!";
        fprintf(stderr,errormsg,strlen(errormsg));
        exit(-1);
    }
    close(ret);

    //2判断oldfd和newfd是否一致
    if(oldfd == newfd)
    {
        return newfd;
    }
    
    //3使用dup进行逐个复制
    int *fdbuf = new int[newfd];
    int i;
    for(i=0;i<newfd;++i)
    {
        ret = dup(oldfd);
        if(ret == -1)
        {
            err_exit("dup");
        }

        if(ret == newfd)
        {
            break;
        }
    }

    if(ret == newfd)
    {
        //4关闭除newfd外的其他文件描述符
        for(int j=0;j<i;++j)
        {
            close(fdbuf[j]);
        }
        delete[] fdbuf;

        return newfd;
    }

    delete[] fdbuf;
    //没匹配到返回-1
    return -1;
}


int main()
{

    int fd = open("text2.txt",O_WRONLY|O_CREAT,0644);
    if(-1 == fd)
    {
        err_exit("open");
    }

    int fd2 = mydup2(fd,100);
    if(-1 == fd2)
    {
        const char *errmsg = "newfd is not valid";
        fprintf(stderr,errmsg,strlen(errmsg));
        exit(-1);
    }

    write(fd,"hello",5);
    write(fd2,"world",5);

    close(fd);
    close(fd2);
}


