#include "../../include/apue.h"
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    uint32_t netl,hostl;
    uint16_t nets,hosts;
    
    netl = htonl(10);
    printf("%d\n",netl);

    nets = htons(10);
    printf("%d\n",nets);

    hostl = ntohl(netl);
    printf("%d\n",hostl);

    hosts = ntohs(nets);
    printf("%d\n",hosts);

    return 0;
}
