#include "queue_sequence.h"

Status InitQueue(SqQueue *queue) {
    queue->base = malloc(_MAXQSIZE_ * sizeof(QueueElemType));
    if (!queue->base)
        return OVERFLOW;
    queue->front = queue->rear = 0;
    return OK;
}

Status DestoryQueue(SqQueue *queue) {
    free(queue->base);
    queue->front = queue->rear = 0;
    return OK;
}

Status ClearQueue(SqQueue *queue) {
    if (DestoryQueue(queue) == OK)
        return InitQueue(queue);
    return ERROR;
}

int QueueEmpty(SqQueue queue) {
    return (queue.front == queue.rear);
}

int QueueLength(SqQueue queue) {
    return (queue.rear - queue.front + _MAXQSIZE_) % _MAXQSIZE_;
}

Status GetHead(SqQueue queue, QueueElemType *e) {
    if (queue.front == queue.rear)
        return ERROR;

    *e = queue.base[queue.front];
    return OK;
}

Status EnQueue(SqQueue *queue, QueueElemType e) {
    if ((queue->rear + 1) % _MAXQSIZE_ == queue->front)
        return ERROR;

    queue->base[queue->rear] = e;
    queue->rear = (queue->rear + 1) % _MAXQSIZE_;
    return OK;
}

Status DeQueue(SqQueue *queue, QueueElemType *e) {
    if (queue->front == queue->rear)
        return ERROR;

    *e = queue->base[queue->front];
    queue->front = (queue->front + 1) % _MAXQSIZE_; // 注意
    return OK;
}
