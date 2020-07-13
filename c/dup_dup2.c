#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/***
 * 系统默认是关闭 FD_CLOEXEC 标志的
 * dup函数会将新文件描述符的标志清除掉，这里测试一下
 * */

int main(int argc, char const *argv[])
{
    int fd, dfd, d2fd;
    int declare;
    // create file
    fd = open("./newfile", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, S_IRWXO);
    if(fd == -1) {
        printf("create new file error\n");
        exit(0);
    }

    // write data
    if(write(fd,"1234567890",10) == -1) {
        printf("write data error\n");
        exit(0);
    }

    // get file declare
    declare = fcntl(fd, F_GETFD);
    printf("before change fd: %d\n", declare);

    // open fd_cloexec
    fcntl(fd, F_SETFD, declare | FD_CLOEXEC);
    declare = fcntl(fd, F_GETFD);
    printf("after change fd: %d\n", declare);

    // dup
    dfd = dup(fd);

    // check file declare
    declare = fcntl(dfd, F_GETFD, declare);
    printf("dup fd: %d\n", declare);

    // dup2
    d2fd = dup2(fd, 10);

    // check file declare
    declare = fcntl(d2fd, F_GETFD, declare);
    printf("dup2 fd: %d\n", declare);


    exit(0);
}

