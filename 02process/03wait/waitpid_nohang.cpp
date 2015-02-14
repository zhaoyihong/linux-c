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


//如果有多个进程同时结束,一次wait只能wait一个,循环wait会导致子进程执行时主进程阻塞,因此要使用非阻塞的waitpid
//
void handle(int signo)
{
    int retcode;
    pid_t pid;
    static int cnt = 0;

    //WNOHANG时,使用的是非阻塞的waitpid,当没有子进程时,返回0
    while( (pid=waitpid(-1,&retcode,WNOHANG)) >0 )
    {
        cout << "child " << pid << " exit ,return code:" << WEXITSTATUS(retcode) << endl;
        ++cnt;
    }

    cout << "count : "<< cnt << endl;
}

int main()
{
    signal(SIGCHLD,handle);
   
    for(int i=0;i<100;++i)
    {
        pid_t pid = fork();
        if(0 == pid)
        {
            sleep(1);
            cout << "process " << getpid() << " exit" << endl;
            exit(100);
        }
    }

    while(1)
    {

    }
    return 0;
}
