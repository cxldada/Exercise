#include "../include/apue.h"

#define BUFFSIZE 1024

int main(int argc, char const *argv[])
{
    long li_iopos;
    char buf[BUFFSIZE];

    fgets(buf, BUFFSIZE, stdin);
    li_iopos = ftell(stdin);
    fputs(buf, stdout);
    printf("iopos = %ld.\n", li_iopos);
    li_iopos = ftell(stdout);
    printf("iopos = %ld.\n", li_iopos);

    return 0;
}
