#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        puts("usage: a.out pathname");
        return 0;
    }

    if (access(argv[1], R_OK) < 0)
        puts("can't read");
    else
        puts("can read");

    return 0;
}
