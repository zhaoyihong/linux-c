/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒

    sigaction 用法

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

void handler(int signo)
{
    printf("receive a signal:%d\n",signo);
}

//使用sigaction定义一个signal函数
sighandler_t mysignal(int signum, sighandler_t handler)
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    struct sigaction oldact;
    
    if(sigaction(signum,&act,&oldact) == -1)
    {
        return SIG_ERR;
    }

    return oldact.sa_handler;
}

int main(void)
{


    if(SIG_ERR == mysignal(SIGINT,handler))
    {
        err_exit("mysignal");
    }

    for(;;);
    
    return 0;
}


