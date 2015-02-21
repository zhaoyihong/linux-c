/************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年02月16日 星期一 11时41分30秒
        

    sigqueue发送信号 

************************************************************************/

#include  <iostream>
#include  <signal.h>
#include  <stdio.h>
#include  <stdlib.h>
using namespace std;

void err_exit(const char *msg )
{
        perror(msg);
        exit(-1);
}


int main(int argc,char *argv[])
{
    if(argc !=3 )
    {
        fprintf(stderr,"Usage:%s pid num",argv[0]);
        exit(-1);
    }


    int pid = atoi(argv[1]);
    union sigval value;
    value.sival_int = atoi(argv[2]);
    
    if(sigqueue(pid,SIGUSR1,value) < 0)
    {
        err_exit("sigqueue");
    }

    printf("done!\n");
   


    return 0;
}


