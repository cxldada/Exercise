#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    int fd;
    struct stat buf;

    /***
     * stat
     */
    for (int i = 1; i < argc; i++)
    {
        printf("%s: ", argv[i]);
        if(stat(argv[i],&buf) == -1)
            continue;
        
        if(S_ISREG(buf.st_mode))
            printf("regular file");
        else if(S_ISDIR(buf.st_mode))
            printf("directory");
        else if(S_ISBLK(buf.st_mode))
            printf("block special");
        else if(S_ISCHR(buf.st_mode))
            printf("character special");
        else if(S_ISFIFO(buf.st_mode))
            printf("fifo");
        else if(S_ISSOCK(buf.st_mode))
            printf("socket");
        else
            printf("** unknow mode **");

        puts("");
    }

    /***
     * lstat
     */
    for (int i = 1; i < argc; i++)
    {
        if(lstat(argv[i],&buf) == -1)
            continue;

        if (S_ISLNK(buf.st_mode))    // stat 会查询链接文件指向的文件 而不是链接文件本身 lstat会返回链接文件的信息
            printf("%s: symbolic link",argv[i]);
        
        puts("");
    }

    return 0;
}
