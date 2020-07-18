#include "../include/apue.h"
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
    {
        if(execl("/home/cxl/Documents/unix_test/demo/testinterp","testintrp","myarg1","MY ARG2",(char *)0) < 0)
            err_sys("execl error");
    }

    if (waitpid(pid, NULL, 0) < 0)
        err_sys("waitpid error");

    exit(0);
}
