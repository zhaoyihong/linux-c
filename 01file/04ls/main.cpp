/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月22日 星期四 21时15分26秒
 
    遍历目录,实现一个简单的ls程序,只能查看目录下的内容,05中将有更加复杂的程序
 ************************************************************************/

#include<iostream>
#include  <sys/types.h>
#include  <sys/stat.h>
#include  <fcntl.h>
#include  <stdlib.h>
#include  <errno.h>
#include  <stdio.h>
#include  <unistd.h>
#include <dirent.h>

using namespace std;

void err_exit(const char*msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void usage(const char *bin)
{
    cout << "uage:" << bin << " dirname" << endl;
}

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    DIR* dir = opendir(argv[1]);
    if(NULL == dir)
    {
        err_exit("opendir");
    }

    struct dirent * file_dirent;
    while((file_dirent=readdir(dir)) != NULL)
    {
        cout << (file_dirent->d_name) << " ";
    }
    cout << endl;
    
    return 0;
}
