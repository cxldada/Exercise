#ifndef __RDN
#define __RDN

#include "./apue.h"

ssize_t readn(int fd,void *ptr,size_t n)
{
    size_t nleft;
    ssize_t nread;

    nleft = n;
    while(nleft > 0)
    {
        if((nread = read(fd,ptr,nleft)) < 0)
        {
            if(nleft == n)
                return -1;
            else
                break;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    return (n - nread);
}

ssize_t writen(int fd,const void *ptr,size_t n)
{
    size_t nleft;
    ssize_t nwriteen;
    
    nleft = n;
    while(nleft > 0)
    {
        if((nwriteen = write(fd,ptr,nleft)) < 0)
        {
            if(nleft == n)
                return -1;
            else
                break;
        }
        else if(nwriteen == 0)
            break;
        nleft -= nwriteen;
        ptr += nwriteen;
    }
    return (n - nleft);
}

#endif
