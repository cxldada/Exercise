#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "macro.h"

#ifndef QueueElemType
#define QueueElemType int
#endif


typedef struct QNode {
    QueueElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

typedef struct {
    QueueElemType *base;
    int front;
    int rear;
} SqQueue;

Status InitQueue_LQ(LinkQueue *queue);
Status DestoryQueue_LQ(LinkQueue *queue);
Status ClearQueue_LQ(LinkQueue *queue);

int QueueEmpty_LQ(LinkQueue queue);
int QueueLength_LQ(LinkQueue queue);
Status GetHead_LQ(LinkQueue queue, QueueElemType *e);
Status EnQueue_LQ(LinkQueue *queue, QueueElemType e);
Status DeQueue_LQ(LinkQueue *queue, QueueElemType *e);

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