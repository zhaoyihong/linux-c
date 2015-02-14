/*************************************************************************
	> File Name: vfork.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月13日 星期五 15时25分29秒
    
    vfork子进程共享地址空间,不进行任何拷贝,所以效率比fork高.
    vfork中子进程先执行
    vfork中子进程必须立刻进行_exit或者exec
    fork实现了write on  copy后,效率提高不少,但还是比vfork低
        但是vfork的实现或多或少都有问题,所以还是推荐使用fork

    vfork进程中不可以使用return 0来退出
 ************************************************************************/

#include  <iostream>
#include  <unistd.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>


using namespace std;
void err_exit(const char *msg)
{
    perror(msg);
    exit(-1);
}

int main()
{
    cout << "before fork" << endl;


    pid_t pid = vfork();

    if(pid == -1)
    {
       err_exit("fork"); 
    }

    //子进程中
    if(pid == 0)
    {
      //sleep(5);
      _exit(0);
    }

    //父进程中
    if(pid > 0)
    {
        printf("this is parent,pid=%d,child pid=%d\n",getpid(),pid);
    }
  
    //由于父进程sleep了一秒,父进程在子进程之后执行,文件中是helloworld,没有发生覆盖现象,课件父子进程中的描述符是共享文件表的

    //num由于写时拷贝,在进程改变它时子进程拷贝了一份num变量,因此改变num时不会影响父进程

    return 0;
}
