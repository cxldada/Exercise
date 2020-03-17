#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

extern int errno;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("usage: ./a.out <dir or file>\n");
        exit(0);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        printf("open %s error: %s", argv[1], strerror(errno));
        exit(0);
    }

    int new_fd = fcntl(fd, F_DUPFD, 5);
    if(new_fd <= 0) {
        printf("dup2 error: %s", strerror(errno));
        exit(0);
    }
    printf("old descriptor: %d\nnew descriptor: %d\n", fd, new_fd);

    exit(0);
}