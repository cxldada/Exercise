#include "../include/apue.h"
#include <stdlib.h>
#include <pthread.h>

struct msg
{
    struct msg *m_next;
    // more stuff here
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void *process_msg(void *arg)
{
    printf("process_msg start\n");
    struct msg *mp;
    for (;;)
    {
        pthread_mutex_lock(&qlock);
        while (workq == NULL)
        {
            printf("process_msg start wait\n");
            pthread_cond_wait(&qready, &qlock);
        }
        printf("process_msg end wait\n");
        mp = workq;
        workq = mp->m_next;
        pthread_mutex_unlock(&qlock);
    }

    printf("process_msg ending\n");
    pthread_exit((void *)0);
}

void enqueue_msg(struct msg *mp)
{
    printf("main start\n");
    pthread_mutex_lock(&qlock);
    mp->m_next = workq;
    workq = mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
    printf("main end\n");
    sleep(5);
}

int main(void)
{
    int err;
    pthread_t tid;
    struct msg m;

    if ((err = pthread_create(&tid, NULL, process_msg, NULL)) != 0)
        err_sys("create thread error");

    sleep(5);
    
    m.m_next = NULL;
    enqueue_msg(&m);

    exit(0);
}