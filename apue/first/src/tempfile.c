#include "../include/apue.h"
#include <errno.h>

void make_temp(char *template)
{
    int fd;
    struct stat buf;

    if ((fd = mkstemp(template)) < 0)
        err_sys("mkstemp error");
    printf("temp name = %s\n", template);
    close(fd);
    if (stat(template, &buf) < 0)
    {
        if (errno == ENOENT)
            printf("file doesn't exist\n");
        else
            err_sys("stat error");
    }
    else
    {
        printf("file exist\n");
        unlink(template);
    }
}

void otherTest()
{
    char good_template[] = "/tmp/dirXXXXXX";
    char *bad_template = "/tmp/dirXXXXXX";

    printf("trying to create first temp file...\n");
    make_temp(good_template);
    printf("trying to create second temp file...\n");
    make_temp(bad_template);
}

void tempfile()
{
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));

    tmpnam(name);
    printf("%s\n", name);

    if ((fp = tmpfile()) == NULL)
        err_sys("tmpfile error");
    fputs("one line of output\n", fp);
    rewind(fp);
    if ((fgets(line, sizeof(line), fp)) == NULL)
        err_sys("fgets error");
    fputs(line, stdout);
}

int main(int argc, char *argv[])
{
    // tempfile();
    otherTest();
    return 0;
}
