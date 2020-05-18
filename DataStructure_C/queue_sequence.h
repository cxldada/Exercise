#ifndef _QUEUE_SEQUENCE_H_
#define _QUEUE_SEQUENCE_H_

#include "macro.h"

#ifndef QueueElemType
#define QueueElemType int
#endif

#define _MAXQSIZE_ 100
typedef struct {
    QueueElemType *base;
    int front;
    int rear;
} SqQueue;

// 循环队列
Status InitQueue(SqQueue *queue);
Status DestoryQueue(SqQueue *queue);
Status ClearQueue(SqQueue *queue);

int QueueEmpty(SqQueue queue);
int QueueLength(SqQueue queue);
Status GetHead(SqQueue queue, QueueElemType *e);
Status EnQueue(SqQueue *queue, QueueElemType e);
Status DeQueue(SqQueue *queue, QueueElemType *e);

#endif