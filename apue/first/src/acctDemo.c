#include "../include/apue.h"
#include <sys/acct.h>

#define acct acct_v3

int main(int argc, char const *argv[])
{
    struct acct acdata;
    FILE *fp;

    if(argc != 2)
        err_quit("usage: pracct filename");
    if((fp = fopen(argv[1],"r")) == NULL)
        err_sys("can't open %s",argv[1]);
    while (fread(&acdata, sizeof(acdata), 1, fp) == 1)
    {
        printf("%d\n%d\n%.0f", (int)sizeof(acdata.ac_comm),
               (int)sizeof(acdata.ac_comm),
               acdata.ac_comm);
    }
    if(ferror(fp))
        err_sys("read error");

    return 0;
}
