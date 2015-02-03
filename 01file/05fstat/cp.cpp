/*************************************************************************
	> File Name: cp.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月22日 星期四 20时35分15秒
    写一个程序拷贝文件
************************************************************************/


#include<iostream>
#include  <stdlib.h>
#include  <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include  <string.h>
#include  <errno.h>

using namespace std;

void usage(const char *filename)
{
    printf("usage:%s src dest\n",filename);
}

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    int srcfd = open(argv[1],O_RDONLY);
    if(-1 == srcfd)
    {
        err_exit("open");
    }

    //添加获取源文件权限
    
    struct stat sstat;
    if(-1 == fstat(srcfd,&sstat))
    {
        err_exit("fstat");
    }

   // int destfd = open(argv[2],O_WRONLY|O_TRUNC|O_CREAT|O_SYNC,0644); //添加同步选项O_SYNC
    int destfd = open(argv[2],O_WRONLY|O_EXCL|O_CREAT|O_SYNC,sstat.st_mode); //使用源文件的权限来创建,为了防止原来有文件,使用O_EXCL来报错
    if(-1 == destfd)
    {
        err_exit("open");
    }

    char buf[128];
    int nread;
    while(1)
    {
        bzero(buf,sizeof(buf));
        nread=read(srcfd,buf,sizeof(buf));
        if(nread == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }
            err_exit("read");
        }
        else if(nread == 0)
        {
            break;
        }

        //int ret = write(destfd,buf,strlen(buf)); //错误,因为读取到的不是以\0结尾的字符串
        int ret = write(destfd,buf,nread); //注意write只是写到了输出缓冲区,没有写到磁盘.如果想直接写到磁盘需要使用同步选项 
        if(-1 == ret)
        {
            err_exit("write");
        }
    }
 
    close(srcfd);
    close(destfd);

    return 0;
}


