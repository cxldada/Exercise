#include "queue.h"
#include <stdlib.h>

Status InitQueue_LQ(LinkQueue *queue) {
    queue->front = queue->rear = malloc(sizeof(QNode));
    if (!queue->front)
        exit(OVERFLOW);

    queue->front->next = NULL;
    return OK;
}

Status DestoryQueue_LQ(LinkQueue *queue) {
    while (queue->front) {
        queue->rear = queue->front;
        free(queue->front);
        queue->front = queue->rear;
    }

    return OK;
}

Status ClearQueue_LQ(LinkQueue *queue) {
    return DestoryQueue_LQ(queue);
}

int QueueEmpty_LQ(LinkQueue queue) {
    return (queue.front == queue.rear);
}

int QueueLength_LQ(LinkQueue queue) {
    return (queue.rear - queue.front);
}

Status GetHead_LQ(LinkQueue queue, QueueElemType *e) {
    if (queue.front == queue.rear)
        return ERROR;

    *e = queue.front->next->data;
    return OK;
}

Status EnQueue_LQ(LinkQueue *queue, QueueElemType e) {
    QNode *node = malloc(sizeof(QNode));
    if (!node)
        return OVERFLOW;

    node->data = e;
    node->next = NULL;

    queue->rear->next = node;
    queue->rear = node;
    return OK;
}

Status DeQueue_LQ(LinkQueue *queue, QueueElemType *e) {
    if (queue->front == queue->rear)
        return ERROR;

    QNode *pNode = queue->front;
    queue->front = queue->front->next;
    *e = pNode->data;
    if (queue->rear == pNode)
        queue->rear = queue->front;

    free(pNode);

    return OK;
}
