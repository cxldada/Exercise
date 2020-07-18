#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buff[28];
    int fd = open(argv[1],O_RDWR);
    printf("%d\n",fd);

    int fd1 = dup2(fd,0);
    printf("%d\n",fd1);
    int fd2 = dup2(fd,1);
    printf("%d\n",fd2);
    int fd3 = dup2(fd,2);
    printf("%d\n",fd3);

    if(fd > 2)
        close(fd);

    buff[0] = 'a';
    ssize_t n = write(fd1, buff, 28);
    if(n == -1)
    {
        perror("write error");
        return 0;
    }

    printf("write success");
    return 0;
}
