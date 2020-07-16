#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[]) {
    int i, fd;
    struct stat statbuf;
    struct timespec times[2];

    for (i = 1; i < argc; i++) {
        if(stat(argv[1], &statbuf) < 0) {
            printf("stat error\n");
            continue;
        }

        if ((fd = open(argv[1], O_RDWR | O_TRUNC)) < 0) {
            printf("open error\n");
            continue;
        }

        times[0] = statbuf.st_atimespec;
        times[1] = statbuf.st_mtimespec;
        if (futimens(fd, times) < 0) {
            printf("futimens error\n");
            continue;
        }
        close(fd);
    }

    exit(0);
}
