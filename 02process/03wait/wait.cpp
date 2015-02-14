/*************************************************************************
	> File Name: fork.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月14日 星期六 12时02分28秒
 ************************************************************************/

#include<iostream>
#include  <sys/wait.h>
#include  <stdio.h>
#include  <stdlib.h>
using namespace std;


int main()
{
    pid_t pid;
    pid = fork();
    
    if(-1 == pid)
    {
        perror("fork");
        exit(-1);
    }
    else if(0 == pid)
    {
        cout << "this is child ,pid = " << getpid()  << endl;
        sleep(1);
        cout << "child exit" << endl;
        exit(200);
    }
    
    cout << "this is parent" << endl;
    int status = 0;
    int ret = wait(&status);
    if(-1 == ret)
    {
        perror("wait");
        exit(-1);
    }
    cout << endl;
    
    //wait返回值是子进程进程号 ,WIFEXITED宏判断是否是正常终止,WEXITSTATUS获取退出状态
    cout << "child process " << ret << endl;
    cout << "is child proces return normaly: " << boolalpha << WIFEXITED(status) << endl;
    cout << "child process return value: " << WEXITSTATUS(status) << endl;
    

    return 0;
}
