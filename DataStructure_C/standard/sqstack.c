#include <stdio.h>
#include <stdlib.h>
#include "common.h"
/***************************************/
// 顺序栈的实现
/***************************************/
#define MAX_SIZE 50

typedef struct {
    ElemType data[MAX_SIZE];
    int top;
} SqStack;

void InitStack(SqStack *S) {
    S->top = -1;
}

Status Stack_Empty(SqStack s) {
    return (s.top == -1);
}

Status Push(SqStack *S, ElemType x) {
    if (S->top == MAX_SIZE - 1) {
        return FALSE;
    }
    S->data[++(S->top)] = x;

    return TRUE;
}

Status Pop(SqStack *S, ElemType *x) {
    if (S->top == -1) {
        return FALSE;
    }

    x = S->data[(S->top)--];
    return TRUE;
}

Status GetTop(SqStack S, ElemType *x) {
    if (S.top != -1) {
        x = S.data[S.top];
        return TRUE;
    }
    return FALSE;
}

/*********************************************/
// 链式栈的实现
/*********************************************/

typedef struct LinkNode {
    ElemType data;
    struct LinkNode *next;
} LinkNode, *LinkStack;

Status Push(LinkStack s, ElemType x) {
    LinkNode *p;
    p = (LinkNode *)malloc(sizeof(LinkNode));
    if(p == NULL) {
        exit(OVERFLOW);
    }
    p->data = x;
    p->next = s;
    s = p;
    return TRUE;
}

Status Pop(LinkStack s,ElemType *x) {
    LinkNode *p;
    if(s == NULL) {
        return FALSE;
    }

    p = s;
    s = s->next;
    x = p->data;
    free(p);
    return TRUE;
}

Status GetTop(LinkStack s,ElemType *x) {
    if(s == NULL) {
        return FALSE;
    }
    x = s->data;
    return TRUE;
}
