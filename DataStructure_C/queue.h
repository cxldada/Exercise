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

Status InitQueue(LinkQueue *queue);
Status DestoryQueue(LinkQueue *queue);
Status ClearQueue(LinkQueue *queue);

int QueueEmpty(LinkQueue queue);
int QueueLength(LinkQueue queue);
Status GetHead(LinkQueue queue, QueueElemType *e);
Status EnQueue(LinkQueue *queue, QueueElemType e);
Status DeQueue(LinkQueue *queue, QueueElemType *e);

#endif