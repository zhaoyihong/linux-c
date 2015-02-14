/*************************************************************************
	> File Name: exec.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 15时25分29秒



       int execl(const char *path, const char *arg, ...);
       int execlp(const char *file, const char *arg, ...);
       int execle(const char *path, const char *arg,
                  ..., char * const envp[]);

       int execv(const char *path, char *const argv[]);
       int execvp(const char *file, char *const argv[]);
       int execvpe(const char *file, char *const argv[],
                  char *const envp[]);

     带l的直接把执行参数写在形参中,带v的是把执行参数写在数组中,然后把数组写在形参中

    参数列表 argv 第一个是文件名,接着是各个参数,最后是NULL
    envp 每个都是一个环境变量名,最后是NULL


    最终都会调用execve系统函数

************************************************************************/

#include  <iostream>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <signal.h>

using namespace std;
void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

int main()
{
    signal(SIGCHLD,SIG_IGN);

    cout << "before fork" << endl;

    pid_t pid = fork();

    if(pid == -1)
    {
       err_exit("fork"); 
    }

    //子进程中
    if(pid == 0)
    {
        cout << "child process" << endl; 
        //char *const argv[] = {"ls","-al","/etc/passwd",NULL};
        //int ret = execve("/bin/ls",argv,NULL);
        
        //int ret = execl("/bin/ls","ls","-al","/etc/passwd",NULL);
        //int ret = execlp("ls","ls","-al","/etc/passwd",NULL);
        char *const envp[] = {
            "AA=100",
            "BB=200"
        };

        int ret = execle("./hello","hello",NULL,envp);
        if(-1 == ret)
        {
            err_exit("exec");
        }
    }

    //父进程中
    if(pid > 0)
    {
        cout << "parent process" << endl;
        sleep(1);
    }

    return 0;
}
