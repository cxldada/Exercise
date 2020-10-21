#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"

#define MAX_SIZE 50

/********************************************/
// 循环队列的顺序实现
/********************************************/

typedef struct {
    ElemType data[MAX_SIZE];
    int front, rear;
} SqQueue;

void InitQueue(SqQueue q) {
    q.front = q.rear = 0;
}

bool EnQueue(SqQueue *q, ElemType x) {
    if ((q->rear + 1) % MAX_SIZE == q->front) {
        return false;
    }

    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAX_SIZE;
    return true;
}

bool DeQueue(SqQueue *q, ElemType *x) {
    if(q->front == q->rear)
        return false;

    *x = q->data[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    return true;
}

int QueueLength(SqQueue q) {
    return (q.rear - q.front + MAX_SIZE) % MAX_SIZE;
}

/*************************************************/
// 队列的链式存储实现
/*************************************************/

typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode;

typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

void InitQueue(LinkQueue *q) {
    q->front = q->rear = (LinkNode *)malloc(sizeof(LinkNode));
    q->front->next = NULL;
}

bool IsEmpty(LinkQueue q) {
    if (q.front == q.rear)
        return true;
    else
        return false;
}

bool EnQueue(LinkQueue *q, ElemType x) {
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    if(s == NULL) {
        exit(OVERFLOW);
    }
    s->data = x;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
    return true;
}

bool DeQueue(LinkQueue *q, ElemType *x) {
    if(q->front == q->rear)
        return false;

    LinkNode *p = q->front->next;
    *x = p->data;
    q->front = q->front->next;

    if(q->rear == p)
        q->rear = q->front;

    free(p);
    return true;
}

/**************************************************/
// 栈和队列的应用
/**************************************************/

/**
 * 括号匹配
 * */

bool MatchBrackts() {
    const int MAXSIZE = 1024;
    char s[MAXSIZE];
    int top;
    char ch = getchar();
    while (ch != EOF) {
        switch (ch)
        {
        case '{':
        case '(':
        case '[': {
            s[top++] = ch;
        } break;
        case ')': {
            if (top == 0 || s[--top] != '(')
                return false;
        } break;
        case ']': {
            if(top == 0 || s[--top] != '[')
                return false;
        } break;
        case '}': {
            if (top == 0 || s[--top] != '{')
                return false;
        } break;
        default:
            break;
        }
        ch = getchar();
    }
    if(top == 0)
        return true;
    else
        return false;
}
