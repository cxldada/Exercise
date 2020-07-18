#include <unistd.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include <syslog.h>
#include <sys/stat.h>

#define BUFLEN 128
#define QLEN 10

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

// 关闭执行时关闭标识
int set_cloexec(int fd)
{
    int val;
    if((val = fcntl(fd,F_GETFD,0)) < 0)
        return -1;
    
    val |= FD_CLOEXEC;

    return (fcntl(fd,F_SETFD,val));
}

void daemonize(const char *cmd)
{
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    // 清空文件创建屏蔽字
    umask(0);

    // 获取文件描述符的最大数量
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
    {
        printf("%s: can't get file limit", cmd);
        return;
    }

    // 成为会话首进程
    if((pid = fork()) < 0) {
        printf("%s: can't fork", cmd);
        return;
    }else if(pid != 0)
        exit(0);

    setsid();

    // 确认将来打开的会话不会分配新的tty
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if(sigaction(SIGHUP,&sa,NULL) < 0)
    {
        printf("%s: can't ignore SIGHUP", cmd);
        return;
    }
    if((pid = fork()) < 0) {
        printf("%s: can't fork", cmd);
        return;
    }else if(pid != 0)
        exit(0);

    if(chdir("/") < 0) {
        printf("%s: can't change directory to /", cmd);
        return;
    }

    // 关闭所有打开的文件描述符
    if(rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i = 0; i < rl.rlim_max; i++)
        close(i);

    fd0 = open("/dev/null",O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    // 初始化日志文件
    openlog(cmd,LOG_CONS,LOG_DAEMON);
    if(fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR,"unexpected file descriptors %d %d %d",fd0,fd1,fd2);
        exit(1);
    }
}

int initserver(int type, const struct sockaddr *addr, socklen_t alen, int qlen)
{
    int fd;
    int err = 0;

    if ((fd = socket(addr->sa_family, type, 0)) < 0)
        return -1;
    if (bind(fd, addr, alen) < 0)
        goto errout;
    if (type == SOCK_STREAM || type == SOCK_DGRAM)
    {
        if (listen(fd, qlen) < 0)
            goto errout;
    }

errout:
    err = errno;
    close(fd);
    errno = err;
    return -1;
}

void serve(int sockfd)
{
    int clfd;
    FILE *fp;
    char buf[BUFLEN];

    set_cloexec(sockfd);
    for(;;)
    {
        if((clfd = accept(sockfd,NULL,NULL)) < 0){
            syslog(LOG_ERR,"ruptimed: accept error: %s",strerror(clfd));
            exit(1);
        }
        set_cloexec(clfd);
        if((fp = popen("/usr/bin/uptime","r")) == NULL) {
            sprintf(buf,"error: %s\n",strerror(errno));
            send(clfd,buf,strlen(buf),0);
        }else{
            while(fgets(buf,BUFLEN,fp) != NULL)
                send(clfd,buf,strlen(buf),0);
            pclose(fp);
        }
        close(clfd);
    }
}

int main(int argc,char *argv[])
{
    struct addrinfo *ailist,*aip;
    struct addrinfo hint;
    int sockfd,err,n;
    char *host;

    if(argc != 1){
        puts("usage ruptimed");
        exit(0);
    }
    if((n = sysconf(_SC_HOST_NAME_MAX)) < 0)
        n = HOST_NAME_MAX;
    if((host = malloc(n)) == NULL) {
        puts("malloc error");
        exit(0);
    }
    if(gethostname(host,n) < 0){
        puts("gethostname error");
        exit(0);
    }
    daemonize("ruptimed");
    memset(&hint,0,sizeof(hint));
    hint.ai_flags = AI_CANONNAME;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_canonname = NULL;
    hint.ai_addr = NULL;
    hint.ai_next = NULL;
    if((err = getaddrinfo(host,"ruptime",&hint,&ailist)) != 0) {
        syslog(LOG_ERR,"ruptimed: getaddrinfo error: %s",gai_strerror(err));
        exit(1);
    }
    for(aip = ailist; aip != NULL; aip = aip->ai_next)
    {
        if((sockfd = initserver(SOCK_STREAM,aip->ai_addr,aip->ai_addrlen,QLEN)) >= 0){
            serve(sockfd);
            exit(0);
        }
    }
    exit(1);
}