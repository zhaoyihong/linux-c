/************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒
        

    接收sigqueue发送的信号 

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
    struct sigaction act;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);  
    act.sa_flags = SA_SIGINFO;

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
    printf("receve a signal:%d,data=%d,data=%d\n",signo,(info->si_value).sival_int,info->si_int);
    //info->si_int 和 (info->si_value).sival_int 作用相同
}
