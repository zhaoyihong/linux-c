/*************************************************************************
	> File Name: mysystem.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月14日 星期六 15时21分43秒
    

    自己实现一个system函数,
        实现原理是开辟一个子进程运行cmd参数 /bin/sh -c cmd
        主线程阻塞等待子进程退出

************************************************************************/

#include  <iostream>
#include  <stdlib.h>
#include  <stdio.h>
#include  <sys/wait.h>
#include  <sys/types.h>
#include  <errno.h>

using namespace std;

int my_system(char *cmd)
{
    //判断cmd是否为空
    if(cmd == NULL)
    {
        return 1;
    }

    //判断/bin/sh是否存在
    if(access("/bin/sh",0) == -1)
    {
        return 127;
    }

    //执行命令
    pid_t pid = fork();
    if(-1 == pid)
    {
        perror("fork");
        exit(-1);
    }
    else if(0 == pid)
    {
        char *const argv[] = {"sh","-c",cmd,NULL};
        int ret = execv("/bin/sh",argv);
        if(ret < 0)
        {
            exit(127);
        }
        exit(ret);
    }
    
    int retcode;
    while( waitpid(pid,&retcode,0) < 0)
    {
        if(errno == EINTR)
        {
            continue;
        }

        return -1;
    }
    
    if(!WIFEXITED(retcode))
    {
        return -1;
    }

    return WEXITSTATUS(retcode);

}


int main(void)
{
    my_system("ls -l | wc -l");

    return 0;
}



