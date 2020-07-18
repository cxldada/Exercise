#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 128
#define TIMEOUT 20

void sigalrm(int signo)
{
}

void print_uptime(int sockfd,struct addrinfo *aip)
{
    int n;
    char buf[BUFLEN];

    buf[0] = 0;
    if(sendto(sockfd,buf,1,0,aip->ai_addr,aip->ai_addrlen) < 0) {
        printf("sendto error");
        return;
    }
    alarm(TIMEOUT);
    if((n = recvfrom(sockfd,buf,BUFLEN,0,NULL,NULL)) < 0){
        if(errno != EINTR)
            alarm(0);
        printf("recv error");
    }
    alarm(0);
    write(STDOUT_FILENO,buf,n);
}