/*************************************************************************
	> File Name: exit.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 19时07分09秒
 
    exit 与 _exit的区别:
        1 exit 会刷新缓冲区,而_exit不会
        2 exit会调用终止处理程序,而_exit不会
 
    atexit 是终止处理程序函数,使用atexit注册的函数会在程序结束时执行,还行顺序和注册顺序相反
 
 ************************************************************************/

#include<iostream>
#include  <stdio.h>
#include  <stdlib.h>
using namespace std;

void myexit1(void)
{
    cout << "myexit1" << endl;
}

void myexit2(void)
{
    cout << "myexit2" << endl;
}

int main(void)
{

    //注册终止处理函数
    atexit(myexit1);
    atexit(myexit2);

    printf("hello world");

    exit(0); //有输出
    //_exit(0);  //没输出
}
