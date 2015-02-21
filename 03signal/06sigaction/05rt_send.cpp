/************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒
        

    实时信号与非实时信号 
        kill - signal 
        sigqueue - sigaction 
    都可以
    以前误以为只有sigqueue才有队列,其实不是这样,实时信号以kill和sigqueue发送都有队列

    kill和sigqueue的区别在于信号的附加数据
    signal 和 sigacton的区别在于 附加数据的结构和信号处理时候可以频闭其他信号

************************************************************************/

#include  <iostream>
#include  <signal.h>
#include  <stdio.h>
#include  <stdlib.h>
using namespace std;

void err_exit(const char *msg )
{
        perror(msg);
        exit(-1);
}


int main(int argc,char *argv[])
{
    if(argc !=2 )
    {
        fprintf(stderr,"Usage:%s pid",argv[0]);
        exit(-1);
    }


    int pid = atoi(argv[1]);
    
    for(int i=0;i<3;++i)
    {
        if(kill(pid,SIGUSR1) < 0)
        {
            err_exit("kill");
        }

        if(kill(pid,SIGRTMIN) < 0)
        {
            err_exit("sigkill");
        }
    }

    sleep(3);

    if(kill(pid,SIGINT) < 0)
    {
        err_exit("kill");
    }


    printf("done!\n");
   


    return 0;
}


