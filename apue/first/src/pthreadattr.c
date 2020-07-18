#include "../include/apue.h"
#include <pthread.h>

int makethread(void *(*fn)(void *), void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;

    err = pthread_attr_init(&attr);
    if(err != 0)
        return err;
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(err == 0)
        err = pthread_create(&tid, &attr, fn, arg);
    pthread_attr_destroy(&attr);
    return err;
}

void *th_fn(void *arg)
{
    printf("thread 1");
    pthread_exit((void *)1);
}

int main(void)
{
    makethread(th_fn,NULL);
    sleep(1);
    exit(0);
}