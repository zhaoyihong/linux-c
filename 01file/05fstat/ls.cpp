/*************************************************************************
	> File Name: main.cpp
	> Author:zhaoyihong 
	> Mail:zhaoyihong_at_126_dot_com 
	> Created Time: 2015年01月22日 星期四 21时15分26秒
 
    遍历目录,像ls -l一样显示文件的具体信息
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
#include  <string.h>
#include  <time.h>
#include <pwd.h>
#include  <grp.h>

using namespace std;

void err_exit(const char*msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void usage(const char *bin)
{
    cout << "uage:" << bin << " filename" << endl;
}

void print_file_info(const char *filename);

int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    //检查arvg[1]是否是目录文件
    
    struct stat sstat;
    stat(argv[1],&sstat);
    if(!S_ISDIR(sstat.st_mode)) //如果不是目录
    {
        print_file_info(argv[1]);    
    }
    else //如果是目录
    {
        
        DIR* dir = opendir(argv[1]);
        if(NULL == dir)
        {
            err_exit("opendir");
        }
        
        struct dirent * file_dirent;
        while((file_dirent=readdir(dir)) != NULL)
        {
            print_file_info(file_dirent->d_name);    
        }
        
    }
    return 0;
}

void print_file_info(const char *filename)
{
    
    //名字
     cout <<"filename:" << filename << " ";

    /* stat 和 fstat 的功能是一样的,只是参数稍微有区别,stat用文件路径,fstat要文件描述符
     * lstat 需要文件路径,但它把link文件也视作文件,显示link文件的信息.而上面两个会直接读取link文件指向的文件的信息
    */
    struct stat sstat;
    lstat(filename,&sstat);
    
    //uid gid
    struct passwd * pd = getpwuid(sstat.st_uid);
    cout << "uid:" << pd->pw_name << "\t";
    
    struct group * gp =getgrgid(sstat.st_gid);
    cout << "gid:" << gp->gr_name << "\t";
    
    //设备号
     int major_dev = major(sstat.st_dev);
     int minor_dev = minor(sstat.st_dev);
     cout << "major_dev:" <<  major_dev  << "\tminor_dev:" << minor_dev << "\t" ; 

    //inode
    cout << "inode:" << sstat.st_ino << "\t";

    //文件类型
    char type;
    switch(sstat.st_mode & S_IFMT)
    {
        case S_IFSOCK:
            type = 's';
            break;
        case S_IFLNK:
            type = 'l';
            break;
        case S_IFREG:
            type = '-';
            break;
        case S_IFBLK:
            type = 'b';
            break;
        case S_IFDIR:
            type = 'd';
            break;
        case S_IFCHR:
            type = 'c';
            break;
        case S_IFIFO:
            type = 'f';
            break;
        defaule:
            type = '?';
            break;
    }

    int mode_bit[3][3] = {
                          S_IRUSR,S_IWUSR,S_IXUSR,
                          S_IRGRP,S_IWGRP,S_IXGRP,
                          S_IROTH,S_IWOTH,S_IXOTH
    };

    cout << "type:" << type << "\t";

    const char *mode_char = "rwx";
    char mode[10];
    memset(mode,'-',10);
    mode[9]='\0';
    for(int i=0;i<3;++i)
    {
        for(int j=0;j<3;++j)
        {
            if(sstat.st_mode & mode_bit[i][j])
            {
                mode[i*3+j] = mode_char[j];
            }
        }
    }
    
    cout << "mode:" << mode << "\t";
    
    cout << "size:" << sstat.st_size << "\t";    
    
    cout << "last_modify:" << ctime(&sstat.st_mtime) << "\t";
    
    //获取符号链接文件指向的文件
    if(type == 'l')
    {
        char link_to_name[256] = {0};
        readlink(filename,link_to_name,sizeof(link_to_name));
        cout << "link to " << link_to_name << endl; 
    }


    cout << endl; 
}
