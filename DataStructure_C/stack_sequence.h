#ifndef _MY_STACK_H_
#define _MY_STACK_H_

#include "macro.h"

#ifndef StackElemType
#define StackElemType int
#endif

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

// sequence type stack
typedef struct SqStack {
    StackElemType *base;
    StackElemType *top;
    int size;
} SqStack;

Status InitStack(SqStack *stack);
Status DestoryStack(SqStack *stack);
Status ClearStack(SqStack *stack);

int StackEmpty(SqStack stack);
int StackLength(SqStack stack);

Status GetTop(SqStack stack, StackElemType *elem);
Status Push(SqStack *stack, StackElemType e);
Status Pop(SqStack *stack, StackElemType *e);

#endif
