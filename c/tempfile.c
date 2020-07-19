#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 256

int main(int argc, char const *argv[]) {
    char name[L_tmpnam], line[MAXLINE];
    FILE *fp;

    printf("%s\n", tmpnam(NULL));

    tmpnam(name);
    printf("%s\n", name);

    if((fp = tmpfile()) == NULL) {
        printf("tmpfile error\n");
        exit(0);
    }

    fputs("one line of output\n", fp);
    rewind(fp);
    if(fgets(line,sizeof(line),fp) == NULL) {
        printf("fgets error");
        exit(0);
    }

    fputs(line, stdout);

    exit(0);
}
