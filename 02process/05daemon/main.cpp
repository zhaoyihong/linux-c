/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月14日 星期六 16时56分57秒
 ************************************************************************/

#include  <iostream>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>

using namespace std;

void err_exit(const char *msg);
int mydaemon(int,int);

int main(void)
{

    mydaemon(0,0);

    //daemon的两个参数 nochdir:为1时不改变当前目录, noclose为1时不关闭标准输入输出错误

    //daemon(0,0);
   
    cout << "cannot print" << endl;

    for(;;)
    {

    }

    return 0;

}

void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}


int mydaemon(int nochdir,int noclose)
{
    pid_t pid = fork();
    if(-1 == pid)
    {
        err_exit("fork error");
    }

    //关闭主进程
    if(pid > 0)
    {
        exit(0);
    }

    //在子进程中执行:

    //创建新的会话期
    setsid();

    if(nochdir)
    {
        //设置当期目录为根目录
        chdir("/");
    }

    if(noclose)
    {
        //将标准输入输出错误长定向到/dev/null
        
        //关闭0 1 2 三个文件描述符
        for(int i=0;i<3;++i)
        {
            close(i);
        }
        
        //fd 必为0
        int fd = open("/dev/null",O_RDWR);
        
        //将0复制到1
        dup(fd);
        //将0复制到2
        dup(fd);
    }

    return 0;
}
