/*************************************************************************
	> File Name: pause.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月15日 星期日 15时34分48秒
    

    在实时系统的设计中，经常会出现多个任务调用同一个函数的情况。如果这个函数不幸被设计成为不可重入的函数的话，那么不同任务调用这个函数时可能修改其他任务调用这个函数的数据，从而导致不可预料的后果。那么什么是可重入函数呢？所谓可重入函数是指一个可以被多个任务调用的过程，任务在调用时不必担心数据是否会出错。不可重入函数在实时系统设计中被视为不安全函数。满足下列条件的函数多数是不可重入的：
        1) 函数体内使用了静态的数据结构；
        2) 函数体内调用了malloc()或者free()函数；
        3) 函数体内调用了标准I/O函数。

可重入函数可以查询 man 7 signal 
   Async-signal-safe functions 中


不要在信号处理函数中调用不可重入函数!


************************************************************************/

#include  <iostream>
#include  <signal.h>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>

using namespace std;

struct Data
{
    int a;
    int b;
};

Data data;


//不可重入函数,可能带来安全问题
//可能会打印0,1 或者 1,0 这样的未预料的结果
void unsafe()
{
    printf("%d,%d\n",data.a,data.b);
}

void handler(int signo)
{
    unsafe();
    alarm(1);
}

int main(void)
{

    struct Data one = {
        1,1
    };
    struct Data zero ={
        0,0
    };

    if(signal(SIGALRM,handler) == SIG_ERR)
    {
        perror("signal");
        exit(-1);
    }

    //1秒后发送SIGALRM信号,只发送一次
    //如果想循环掉用,在handler中调用alarm
    alarm(1);

    for(;;)
    {
        data = one;
        data = zero;
    }
    

    cout << "done" << endl;

    return 0;

}
