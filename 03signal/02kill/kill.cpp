/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月15日 星期日 11时08分14秒

    向父进程或者进程组发送信号

************************************************************************/

#include  <iostream>
#include  <signal.h>
#include  <stdio.h>
#include  <stdlib.h>
using namespace std;

void handler(int);

void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

int main(void)
{
    if(signal(SIGUSR1,handler) == SIG_ERR)
    {
        err_exit("signal");
    }

    pid_t pid = fork();
    if(pid == -1)
    {
        err_exit("fork");
    }
    else if(pid == 0)
    {
        
        //子进程给父进程发送信号 ,SIGUSR1是10号信号
        //kill(getppid(),SIGUSR1);
       
        //向整组发送信号.子进程继承了父进程的signal函数,结果就是会打印两次
        pid_t group = getpgrp();
        kill(-group,SIGUSR1); // 等价于 killpg(group,SIGUSR1); 

        exit(0);
    }

    //sleep(5); //sleep函数被信号打断后返回
    
    //这样写,直接
    int left=5;
    while((left = sleep(left)) != 0); //sleep的返回值是剩余的时间
   

    cout << "done" << endl;
    return 0;
}


void handler(int signo)
{
    cout << getpid()  <<" recve a signal:" << signo <<  endl;
}



