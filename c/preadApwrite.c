#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *filepath = "./pread_pwrite";
const char *content = "abcdefg1234567890\n";

int main(int argc, char const *argv[]) {
    int fd;
    off_t start, pstart, pend;

    // open new file
    if ((fd = open(filepath, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG)) == -1) {
        printf("open %s error\n", filepath);
        exit(fd);
    }

    // look offset
    start = lseek(fd, 0, SEEK_CUR);
    printf("write start offset: %lld\n", start);

    // write
    if (write(fd, content, 18) == -1) {
        printf("write error\n");
        exit(-1);
    }

    // look offset
    pstart = lseek(fd, 0, SEEK_CUR);
    printf("write end offset %lld\n", pstart);
    printf("pwrite start offset %lld\n", pstart);

    // pwrite offset
    if (pwrite(fd, content, 18, pstart) == -1) {
        printf("pwrite error\n");
        exit(-1);
    }

    // look offset
    pend = lseek(fd, 0, SEEK_CUR);
    printf("pwrite end offset %lld\n", pend);

    // close file
    close(fd);

    // open file
    if ((fd = open(filepath, O_RDONLY)) == -1) {
        printf("open %s error\n", filepath);
        exit(fd);
    }

    // look offset
    start = lseek(fd, 0, SEEK_CUR);
    printf("read start offset: %lld\n", start);

    // read file
    char buf[18];
    if (read(fd, buf, 18) == -1) {
        printf("read error");
        exit(-1);
    }

    // look offset
    pstart = lseek(fd, 0, SEEK_CUR);
    printf("read end offset %lld\n", pstart);
    printf("pread start offset %lld\n", pstart);

    // pread file
    char pbuf[18];
    if (pread(fd, pbuf, 18, pstart) == -1) {
        printf("read error");
        exit(-1);
    }

    // look offset
    pend = lseek(fd, 0, SEEK_CUR);
    printf("pread end offset %lld\n", pend);

    exit(0);
}
