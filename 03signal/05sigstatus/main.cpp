/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒
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
    if(SIGINT == signo)         //SIGINT ctrl+c发出
        printf("receive a signal:%d\n",signo);
    else if(SIGQUIT == signo)  //SIGQUIT ctlr+\发出
    {
        sigset_t set;
        sigemptyset(&set);
        sigaddset(&set,SIGINT);
        sigprocmask(SIG_UNBLOCK,&set,NULL); //解除阻塞
        //解除阻塞后,SIGINT信号才会被递达
        //由于SIGINT是非实时信号,不支持队列,因此只有一个SIGINT被处理
    }
}

void printsigset(sigset_t *set)
{
    for(int i=1;i<NSIG;++i)
    {
        if(sigismember(set,i))
        {
            putchar('1');
        }
        else
        {
            putchar('0');
        }
    }
    printf("\n");
}

int main(void)
{
    
    //阻塞SIGINT,当信号达到后,但被阻塞了,此时信号处于未决状态.
    sigset_t bset;
    sigemptyset(&bset);
    sigaddset(&bset,SIGINT);
    sigprocmask(SIG_BLOCK,&bset,NULL);



    if(signal(SIGINT,handler) == SIG_ERR)
    {
        err_exit("signal");
    }

    if(signal(SIGQUIT,handler) == SIG_ERR)
    {
        err_exit("signal");
    }

    sigset_t pset; //获取阻塞信号

    for(;;)
    {
        sigpending(&pset); //获取未决信号,保存到pset中
        printsigset(&pset); //自定义函数,打印pset的每一位
        sleep(1);
    }
    
    return 0;
}


