#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include "macro.h"

// sequence type stack
typedef struct SqStack {
    ElemType *base;
    ElemType *top;
    int stacksize;
} SqStack;

// link type stack
typedef struct StackNode {
    ElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

Status InitStack(SqStack *stack);
Status DestoryStack(SqStack *stack);
Status ClearStack(SqStack *stack);

int StackEmpty(SqStack stack);
int StackLength(SqStack stack);
ElemType GetTop(SqStack stack);

Status Push(SqStack *stack, ElemType e);
Status Pop(SqStack *stack, ElemType *e);

#endif
