#include "stack.h"

Status InitStack(SqStack *stack) {
    stack->base = malloc(_MAXSIZE_ * sizeof(StackElemType));
    if (!stack->base)
        return ERROR;

    stack->top = stack->base;
    stack->stacksize = _MAXSIZE_;
    return OK;
}

Status DestoryStack(SqStack *stack) {
    ClearStack(stack);
    free(stack->base);
    stack->base = stack->top = NULL;
    stack->stacksize = 0;
    return 0;
}

Status ClearStack(SqStack *stack) {
    StackElemType e;
    while (Pop(stack, &e)) {
    }
    return OK;
}

int StackEmpty(SqStack stack) {
    return (stack.base == stack.top);
}

int StackLength(SqStack stack) {
    return (stack.top - stack.base);
}

StackElemType GetTop(SqStack stack) {
    if (stack.top != stack.base)
        *(stack.top - 1);

    return ERROR;
}

Status Push(SqStack *stack, StackElemType e) {
    if(stack->top - stack->base == stack->stacksize)
        return ERROR;

    *stack->top = e;
    ++stack->top;
    return OK;
}

Status Pop(SqStack *stack, StackElemType *e) {
    if (stack->top == stack->base)
        return ERROR;

    e = *(stack->top - 1);
    --stack->top;
    return OK;
}
