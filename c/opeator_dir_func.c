// 操作目录的实例程序

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int ret;
    DIR *dp;
    struct dirent *dir;

    if(argc != 2) {
        printf("usage: a.out <starting-pathname>");
        exit(0);
    }

    dp = opendir(argv[1]);
    if(!dp){
        printf("open dir error!\n");
        exit(0);
    }

    while (dir = readdir(dp))
    {
        printf("%s\n", dir->d_name);
    }

    closedir(dp);
    exit(0);
}
