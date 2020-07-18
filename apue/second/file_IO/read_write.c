#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int n;
    char buff[128];

    if ((n = read(STDIN_FILENO, buff, 128)) == -1)
    {
        printf("read error\n");
        exit(0);
    }

#if 1
    close(STDOUT_FILENO);
#endif

    write(STDOUT_FILENO, buff, n);

    return 0;
}
