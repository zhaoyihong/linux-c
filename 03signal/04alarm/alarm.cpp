/*************************************************************************
	> File Name: pause.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月15日 星期日 15时34分48秒
    
    pause函数会使进程暂停,直到收到信号
        进程暂停状态不会消耗cpu时间,而死循环等待会占用cpu时间

************************************************************************/

#include  <iostream>
#include  <signal.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>

using namespace std;

void handler(int signo)
{
    cout << "recev a signal:" << signo << endl;
    alarm(1);
}

int main(void)
{
    if(signal(SIGALRM,handler) == SIG_ERR)
    {
        perror("signal");
        exit(-1);
    }

    //1秒后发送SIGALRM信号,只发送一次
    //如果想循环掉用,在handler中调用alarm
    alarm(1);

    for(;;)
        pause();

    cout << "done" << endl;

    return 0;

}
