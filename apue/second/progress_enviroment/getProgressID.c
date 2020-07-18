#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    printf("pid: %d, ppid: %d, uid: %d, euid: %d, gid: %d, egid: %d",
           getpid(), getppid(), getuid(), geteuid(), getgid(), getegid());
    return 0;
}
