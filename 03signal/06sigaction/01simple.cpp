/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒

    sigaction 的简单用法
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

int main(void)
{


    struct sigaction act;
    act.sa_handler = handler;   //信号行为
    sigemptyset(&act.sa_mask);  //清空屏蔽字
    act.sa_flags = 0;         

    if(-1 == sigaction(SIGINT,&act,NULL))
    {
        err_exit("sigaction");
    }

    for(;;);
    
    return 0;
}


