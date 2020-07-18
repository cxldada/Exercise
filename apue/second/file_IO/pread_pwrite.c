#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
    int fd;
    ssize_t n;
    char c_str[128];

    if ((fd = open("./test", O_RDWR)) == -1)
    {
        printf("open error\n");
        return 0;
    }

    if((n = pread(fd, c_str, 128, 0)) == -1)
    {
        printf("pread error");
        return 0;
    }

    pwrite(fd, c_str, n, 0);

    close(fd);

    return 0;
}
