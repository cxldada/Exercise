#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        printf("usage: a.out [filename]\n");
        return 0;
    }

    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("STDOUT_FILENO: %d\n", STDOUT_FILENO);
    printf("STDERR_FILENO: %d\n", STDERR_FILENO);

    int newIfd = dup(STDIN_FILENO);
    int newOfd = dup2(STDOUT_FILENO,5);
    int newfd = open(argv[1], O_RDWR | O_CREAT | O_EXCL);
    if(newfd == -1)
    {
        perror("open file error:");
        return 0;
    }

    printf("new In: %d\n", newIfd);
    printf("new Out: %d\n", newOfd);
    printf("new fd: %d\n", newfd);

    char buf[128];
    int n = read(newIfd, buf, 128);
    write(newOfd, buf, n);

    return 0;
}
