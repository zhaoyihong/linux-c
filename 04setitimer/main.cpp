/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月21日 星期六 12时39分15秒
 
    setitimer 可以方便的间歇性的产生时钟
        可以精确到微秒
    

 ************************************************************************/

#include  <iostream>
#include  <stdio.h>
#include  <signal.h>
#include  <sys/time.h>
#include  <stdlib.h>

using namespace std;

void handler(int signo)
{
    if(signo == SIGALRM)
        printf("get alarm!\n");
}

int main()
{
    signal(SIGALRM,handler);

    struct itimerval timeval;
    //it_value是指第一次开始的时间.it_interval是间隔时间
    timeval.it_value.tv_sec = 3; //3s后开始发送第一次信号
    timeval.it_value.tv_usec = 0;
    timeval.it_interval.tv_sec = 1; //每隔0s发送一次
    timeval.it_interval.tv_usec = 0; 
    //等价写法
    //timeval.it_value = {3,0};
    //timeval.it_interval = {1,0};


    if( -1 == setitimer(ITIMER_REAL,&timeval,NULL) )
    {
        perror("setimer");
        exit(-1);
    }

    while(1)
    {
        pause();
    }


    return 0;
}
