/************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒
        

    实时信号和非实时信号
    发送端发送了三个SIGINT和三个SIGRTMIN
    接收端阻塞时,只会保留一个SIGINT,而SIGRTMIN存放在队列中了

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

void handler(int, siginfo_t *, void *);

int main(void)
{
    
    //阻塞SIGUSR1 SIGRTMIN
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s,SIGUSR1);
    sigaddset(&s,SIGRTMIN);
    sigprocmask(SIG_BLOCK,&s,NULL);

    struct sigaction act;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);  
    act.sa_flags = SA_SIGINFO;

    //当收到SIGINT时解除信号屏蔽
    if(-1 == sigaction(SIGINT,&act,NULL))
    {
        err_exit("sigaction");
    }

    //安装一个实时信号
    if(-1 == sigaction(SIGRTMIN,&act,NULL))
    {
        err_exit("sigaction");
    }

    //安装一个非实时信号
    if(-1 == sigaction(SIGUSR1,&act,NULL))
    {
        err_exit("sigaction");
    }

    
    printf("pid=%d\n",getpid());
    
    for(;;)
    {
        pause();
    }
    
    return 0;
}


void handler(int signo,siginfo_t *info, void *reverse)
{
    printf("receve a signal:%d\n",signo);
    if(signo == SIGINT)
    {
        puts("unmask signals");
        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset,SIGUSR1);
        sigaddset(&sigset,SIGRTMIN);
        sigprocmask(SIG_UNBLOCK,&sigset,NULL);
    }
}
