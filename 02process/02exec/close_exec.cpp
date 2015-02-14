/*************************************************************************
	> File Name: exec.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 15时25分29秒

    如果文件描述符表示是CLOSE_EXEC状态,在执行exec函数执行后,这个文件描述符会自动关闭

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
    cout << "main begin" << endl; 
   
    //将标准输出设置为F_CLOEXEC,在exce函数执行后自动关闭,因此hello程序不会有输出产生
    int ret = fcntl(1,F_SETFD,FD_CLOEXEC);
    if(-1 == ret)
    {
        err_exit("fcntl setfd error");
    }
    
    char *const envp[] = {
        "AA=100",
        "BB=200"
    };

    ret = execle("./hello","hello",NULL,envp);
    if(-1 == ret)
    {
        err_exit("exec");
    }

}
