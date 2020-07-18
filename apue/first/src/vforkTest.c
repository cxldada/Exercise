#include "../include/apue.h"

int globvar = 6;

int main(int argc, char *argv[])
{
    int var;
    pid_t pid;

    var = 88;
    printf("before fork\n");
    if((pid = vfork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        globvar++;
        var++;
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    exit(0);
}
