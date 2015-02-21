/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒

    sigaction 中sa_mask的作用:
        在处理信号时(handler函数中),如果遇到sa_mask中置为1的信号,则屏蔽,等处理完信号后,再接收未决状态的信号
        在实验中,按下ctrl+c后 再按ctrl+\ 不会马上退出,而等到handler结束后才退出
        另外发现,按下ctrl+c后 再按ctrl+c 也是一样的现象.
        
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
    sleep(5);
    printf("handler end\n");
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = handler;   //信号行为

    //
    sigemptyset(&act.sa_mask);  //清空屏蔽字
    sigaddset(&act.sa_mask,SIGQUIT); 
    
    act.sa_flags = 0;         

    if(-1 == sigaction(SIGINT,&act,NULL))
    {
        err_exit("sigaction");
    }

    for(;;);
    
    return 0;
}


