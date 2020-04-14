#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include "macro.h"

#ifndef StackElemType
#define StackElemType int
#endif

// sequence type stack
typedef struct SqStack {
    StackElemType *base;
    StackElemType *top;
    int stacksize;
} SqStack;

// link type stack
typedef struct StackNode {
    StackElemType data;
    struct StackNode *next;
} StackNode, *LinkStack;

Status InitStack(SqStack *stack);
Status DestoryStack(SqStack *stack);
Status ClearStack(SqStack *stack);

int StackEmpty(SqStack stack);
int StackLength(SqStack stack);
StackElemType GetTop(SqStack stack);

Status Push(SqStack *stack, StackElemType e);
Status Pop(SqStack *stack, StackElemType *e);

#endif
