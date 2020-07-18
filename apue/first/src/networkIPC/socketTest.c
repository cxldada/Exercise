#include "../../include/apue.h"
#include <sys/socket.h>

int main(int argc, char const *argv[])
{
    int sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    printf("%d\n",sock);

    shutdown(sock, SHUT_RDWR);

    return 0;
}
