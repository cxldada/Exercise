#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd;

    if(argc < 2)
    {
        printf("usage: a.out <path>\n");
        return 0;
    }

    if((fd = open(argv[1],O_RDWR | O_APPEND)) == -1)
    {
        perror("open file error");
        return 0;
    }

    lseek(fd, 5, SEEK_SET);
    char buff[128];
    ssize_t n = read(fd,buff,128);
    if(n == -1)
    {
        perror("read error");
        return 0;
    }

    printf("read date: %s\n\n\n", buff);

    lseek(fd, 0, SEEK_SET);
    write(fd, buff, n);

    return 0;
}
