/*************************************************************************
	> File Name: 01openfie.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月22日 星期四 20时20分16秒
 ************************************************************************/

#include<stdio.h>
#include  <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include  <stdlib.h>

void err_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(void)
{
    int fd = open("test.txt",O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if(-1 == fd)
    {
        err_exit("open");
    }
    printf("open success\n");

    close(fd);
    return 0;
}

