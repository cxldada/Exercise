#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 1024

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("usage: a.out <oldfile> <newfile>");
        return 0;
    }

    int ofd, nfd;

    if ((ofd = open(argv[1], O_RDONLY)) < 0)
    {
        printf("open error for %s\n", argv[1]);
        return 0;
    }

    if ((nfd = open(argv[2], O_WRONLY | O_CREAT | O_EXCL)) < 0)
    {
        printf("open error for %s\n", argv[1]);
        return 0;
    }

    int n;
    char buf[SIZE];
    while ((n = read(ofd, buf, SIZE)) > 0)
    {
        if((n = write(nfd,buf,n)) != n)
        {
            printf("write error\n");
            return 0;
        }
    }

    return 0;
}
