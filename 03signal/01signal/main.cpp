/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月15日 星期日 11时08分14秒

    在输入一行结束前不可被SIGINT信号结束程序

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
    //signal函数的返回值是原有的handler,类型是__sighandler_t,建议保存原先的处理函数,使用完后恢复
    __sighandler_t old_handler = signal(SIGINT,handler);
    //如果signal运行出错,返回 SIG_ERR 
    if(old_handler == SIG_ERR)
    {
        err_exit(0);
    }

    char ch;
    while( (ch=getchar())!='\n');

    old_handler = signal(SIGINT,old_handler);
    if(old_handler == SIG_ERR)
    {
        err_exit(0);
    }

    for(;;);

    return 0;
}


void handler(int signo)
{
    cout << "recve a signal:" << signo << ",please input again!"<< endl;
}



