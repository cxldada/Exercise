#include "../include/apue.h"
#include <errno.h>
#include <netdb.h>
#include <sys/socket.h>

#define MAXSLEEP 128
#define BUFLEN 128

int connect_retry(int domain,int type,int protocol,const struct sockaddr *addr,socklen_t alen)
{
	int numsec,fd;
	for(numsec = 1;numsec <= MAXSLEEP;numsec <<= 1)
	{
		if((fd = socket(domain,type,protocol)) < 0)
			return -1;

		if(connect(fd,addr,alen) == 0) {
			return fd;
		}
		close(fd);

		if(numsec <= MAXSLEEP / 2)
			sleep(numsec);
	}
	return -1;
}

int initserver(int type,const struct sockaddr *addr,socklen_t alen,int qlen) {
	int fd;
	int err = 0;

	if((fd = socket(addr->sa_family,type,0)) < 0)
		return -1;
	if(bind(fd,addr,alen) < 0)
		goto errout;
	if(type == SOCK_STREAM || type == SOCK_SEQPACKET) {
		if(listen(fd,qlen) < 0)
			goto errout;
	}
	return fd;

errout:
	err = errno;
	close(fd);
	errno = err;
	return -1;
}

void print_uptime(int sockfd) {
	int n;
	char buf[BUFLEN];

	while((n = recv(sockfd,buf,BUFLEN,0)) > 0)
		write(STDOUT_FILENO,buf,n);
	if(n < 0)
		printf("recv error\n");
}

int main(int argc,char *argv[]) {
	struct addrinfo *ailist,*aip;
	struct addrinfo hint;
	int sockfd,err;

	if(argc != 2) {
		printf("usage: ruptime hostname");
		exit(-1);
	}
	memset(&hint,0,sizeof(hint));
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_canonname = NULL;
	hint.ai_addr = NULL;
	hint.ai_next = NULL;
	if((err = getaddrinfo(argv[1],"ruptime",&hint,&ailist)) != 0) {
		printf("getaddrinfo error: %s",gai_strerror(err));
		exit(-1);
	}
	for(aip = ailist; aip != NULL; aip = aip->ai_next)
	{
		if((sockfd = connect_retry(aip->ai_family,SOCK_STREAM,0,aip->ai_addr,aip->ai_addrlen)) < 0)
			err = errno;
		else {
			print_uptime(sockfd);
			exit(0);
		}
	}
	printf("can't connect to %s",argv[1]);

	exit(0);
}
