#include "../../include/apue.h"
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    const char *addr4 = "127.0.0.1";
    char buf[INET_ADDRSTRLEN];
    char addr4new[32];
    int code;

    if ((code = inet_pton(AF_INET, addr4, (void *)buf)) < 1)
        printf("inet_pton error code: %d\n", code);
    else
        printf("%s\n", buf);

    inet_ntop(AF_INET, buf, addr4new, INET_ADDRSTRLEN);

    printf("%s\n", addr4new);

    return 0;
}
