/*************************************************************************
	> File Name: fork2.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 19时20分19秒
 ************************************************************************/

#include<iostream>
#include  <unistd.h>
using namespace std;

int main(void)
{
    fork();
    fork();
    fork();
    
    //一共有8个进程,最终打印8个ok
    cout << "ok"  << endl;

    return 0;
}
