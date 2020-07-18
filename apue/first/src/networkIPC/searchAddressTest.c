#include "../../include/apue.h"
#include <netdb.h>
#include <sys/socket.h>

void gethostentTest()
{
    int i;
    struct hostent *he;
    sethostent(1);
    while ((he = gethostent()) != NULL)
    {
        printf("gethostent: h_name: %s, h_addrtype: %d, h_length: %d, ", he->h_name, he->h_addrtype, he->h_length);
        printf("h_aliases: ");
        i = 0;
        while (he->h_aliases[i] != NULL)
        {
            printf("%s", he->h_aliases[i]);
            i++;
        }
        printf("h_addr_list: ");
        i = 0;
        while (he->h_addr_list[i] != NULL)
        {
            printf("%s", he->h_addr_list[i]);
            i++;
        }
        puts("");
    }
    endhostent();
}

void getnetentTest()
{
    struct netent *ne;
    setnetent(1);
    while((ne = getnetent()) != NULL)
    {
        printf("getnetent: n_name: %s, n_addrtype: %d, n_net: %d, n_aliases: ", ne->n_name, ne->n_addrtype, ne->n_net);
        for (int i = 0; ne->n_aliases[i] != NULL; i++)
        {
            printf("%s", ne->n_aliases[i]);
        }
        puts("");
    }
    endnetent();
}

int main(int argc, char *argv[])
{
    gethostentTest();
    getnetentTest();
    exit(0);
}