/*************************************************************************
	> File Name: system.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月14日 星期六 15时17分39秒
 ************************************************************************/

#include  <iostream>
#include  <stdlib.h>
using namespace std;

int main(void)
{
    int ret = system("ls");
    cout << "ret:" << ret << endl;
    return 0;
}

