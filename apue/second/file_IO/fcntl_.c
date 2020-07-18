#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

void getfl(int fd);
void setfl(int fd);

int main(int argc, char const *argv[])
{
    /* 
     * cmd 按照功能分类
     * 复制一个已有描述符  F_DUPFD  F_DUPFD_CLOEXEC
     * 获取或设置文件描述符标志 F_GETFD  F_SETFD
     * 获取或设置文件状态标志 F_GETFL  F_SETFL
     * 获取或设置异步I/O所有权 F_GETOWN  F_SETOWN
     * 获取或设置记录锁 F_GETLK F_SETLK F_SETLKW
     * 
     * 不同的命令返回值的含义是不同的，但是只要出错都会返回-1
     */
    if(argc < 2)
    {
        printf("usage: a.out argc\n");
        return 0;
    }
    int fd = atoi(argv[1]);

    setfl(fd);
    getfl(fd);

    return 0;
}

void getfl(int fd)
{
    int val;
    if((val = fcntl(fd,F_GETFL)) == -1)
    {
        printf("fcntl getfl error\n");
        return;
    }

    switch (val & O_ACCMODE)
    {
    case O_RDONLY:
        printf("read only\n");
        break;
    case O_WRONLY:
        printf("write only\n");
        break;
    case O_RDWR:
        printf("read write\n");
        break;
    default:
        printf("unknow access mode\n");
        break;
    }

    if(val & O_APPEND)
        printf("append\n");

    if(val & O_SYNC)
        printf("sync\n");

    if(val & O_TRUNC)
        printf("trunc\n");

#if defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if(val & O_FSYNC)
        printf("fsync\n");
#endif

    if(val & O_ASYNC)
        printf("async\n");


}

void setfl(int fd)
{
    int val;

    if((val = fcntl(fd,F_GETFL)) == -1)
    {
        printf("fcntl getfl error\n");
        return;
    }

    val |= O_SYNC;

    if((val = fcntl(fd,F_SETFL,val)) == -1)
    {
        printf("fcntl setfl error\n");
        return;
    }
}
