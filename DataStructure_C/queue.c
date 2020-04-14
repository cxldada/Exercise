#include "queue.h"

Status InitQueue_LQ(LinkQueue *queue) {
    /*
    QNode *head = malloc(sizeof(QNode));
    if (!head)
        return OVERFLOW;

    head->data = 0;
    head->next = NULL;
    */

    queue->front = queue->rear = NULL;
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
    if (DestoryQueue_LQ(queue) == OK)
        return InitQueue_LQ(queue);

    return ERROR;
}

int QueueEmpty_LQ(LinkQueue queue) {
    return (queue.rear == NULL || queue.front == NULL);
}

int QueueLength_LQ(LinkQueue queue) {
    return (queue.rear - queue.front);
}

Status GetHead_LQ(LinkQueue queue, QueueElemType *e) {
    if (!QueueEmpty_LQ(queue)) {
        *e = queue.front->data;
        return OK;
    }

    return ERROR;
}

Status EnQueue_LQ(LinkQueue *queue, QueueElemType e) {
    QNode *node = malloc(sizeof(QNode));
    if (!node)
        return OVERFLOW;
    node->data = e;
    node->next = NULL;

    if (queue->front == NULL || queue->rear == NULL) {
        queue->front = queue->rear = node;
        return OK;
    }

    queue->rear->next = node;
    queue->rear = node;
    return OK;
}

Status DeQueue_LQ(LinkQueue *queue, QueueElemType *e) {
    if (queue->front == NULL || queue->rear == NULL)
        return ERROR;

    QNode *pNode = queue->front;
    queue->front = queue->front->next;
    *e = pNode->data;
    if (queue->rear == pNode)
        queue->rear = queue->front;
    free(pNode);

    return OK;
}

Status InitQueue(SqQueue *queue) {
    queue->base = malloc(_MAXSIZE_ * sizeof(QueueElemType));
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
    return (queue.rear - queue.front + _MAXSIZE_) % _MAXSIZE_;
}

Status GetHead(SqQueue queue, QueueElemType *e) {
    if (!QueueEmpty(queue)) {
        *e = queue.base[queue.front];
        return OK;
    }
    return ERROR;
}

Status EnQueue(SqQueue *queue, QueueElemType e) {
    if ((queue->rear + 1) % _MAXSIZE_ == queue->front)
        return ERROR;

    queue->base[queue->rear] = e;
    queue->rear = (queue->rear + 1) % _MAXSIZE_;
    return OK;
}

Status DeQueue(SqQueue *queue, QueueElemType *e) {
    if (queue->front == queue->rear)
        return ERROR;

    *e = queue->base[queue->front];
    queue->front = (queue->front + 1) % _MAXSIZE_;
    return OK;
}

/*
int main(int argc, char const *argv[]) {
    LinkQueue lq;

    InitQueue_LQ(&lq);

    for (int i = 0; i < 10; ++i)
        EnQueue_LQ(&lq, 10 + i);

    for (int i = 0; i < 10; ++i) {
        QueueElemType e;
        DeQueue_LQ(&lq, &e);
        printf("%d\n", e);
    }

    return 0;
}
*/