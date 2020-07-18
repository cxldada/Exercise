#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <float.h>

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("usage: a.out path");
        exit(0);
    }

    int fd;

    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        printf("open %s error: %s", argv[1], strerror(errno));
        return 0;
    }

    close(fd);

    exit(0);
}