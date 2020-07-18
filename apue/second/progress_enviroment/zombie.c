#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    if((pid = fork()) < 0)
    {
        printf("fork error\n");
        exit(0);
    }
    else if(pid == 0)
    {
        exit(0);
    }

    printf("child pid: %d\n", pid);
    sleep(30);
    if (pid == wait(NULL))
        printf("wait pid: %d\n", pid);

    return 0;
}
