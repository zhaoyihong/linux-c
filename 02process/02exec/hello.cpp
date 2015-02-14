/*************************************************************************
	> File Name: hello.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 21时08分48秒

    用来被exec.cpp中的execle调用,AABB来自环境变量
************************************************************************/

#include<iostream>
#include  <stdlib.h>
using namespace std;

int main(void)
{
    cout << "AA=" << getenv("AA") << endl;
    cout << "BB=" << getenv("BB") << endl;
}
