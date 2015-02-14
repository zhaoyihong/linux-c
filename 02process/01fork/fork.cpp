/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 15时25分29秒
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
    //忽略子进程退出信号,防止僵尸进程出现
    signal(SIGCHLD,SIG_IGN);

    cout << "before fork" << endl;

    int fd = open("test.txt",O_CREAT|O_TRUNC|O_WRONLY,0644);
    if(-1 == fd)
    {
        err_exit("open");
    }

    int num = 100;

    pid_t pid = fork();

    if(pid == -1)
    {
       err_exit("fork"); 
    }

    //子进程中
    if(pid == 0)
    {
        num ++;
        printf("this is child,pid=%d,parent pid=%d,num=%d\n",getpid(),getppid(),num);
        write(fd,"hello",5);
    }

    //父进程中
    if(pid > 0)
    {
        sleep(1);
        printf("this is parent,pid=%d,child pid=%d,num=%d\n",getpid(),pid,num);
        write(fd,"world\n",6);
    }
  
    //由于父进程sleep了一秒,父进程在子进程之后执行,文件中是helloworld,没有发生覆盖现象,课件父子进程中的描述符是共享文件表的

    //num由于写时拷贝,在进程改变它时子进程拷贝了一份num变量,因此改变num时不会影响父进程

    close(fd);

    return 0;
}
