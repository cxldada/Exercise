#include "stack_sequence.h"
#include <stdlib.h>

Status InitStack(SqStack *stack) {
    stack->base = malloc(STACK_INIT_SIZE * sizeof(StackElemType));
    if (!stack->base)
        return ERROR;

    stack->top = stack->base;
    stack->size = STACK_INIT_SIZE;
    return OK;
}

Status DestoryStack(SqStack *stack) {
    ClearStack(stack);
    free(stack->base);
    stack->base = stack->top = NULL;
    stack->size = 0;
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

Status GetTop(SqStack stack, StackElemType *elem) {
    if (stack.top != stack.base) {
        *elem = *(stack.top - 1);
        return OK;
    }

    return ERROR;
}

Status Push(SqStack *stack, StackElemType e) {
    if(stack->top - stack->base >= stack->size) {
        stack->base = realloc(stack->base,
                              (stack->size + STACKINCREMENT) * (sizeof(StackElemType)));
        if (!stack->base)
            exit(OVERFLOW);
        
        stack->top = stack->base + stack->size;
        stack->size += STACKINCREMENT;
    }

    *stack->top++ = e;
    return OK;
}

Status Pop(SqStack *stack, StackElemType *e) {
    if (stack->top == stack->base)
        return ERROR;

    *e = *--stack->top;
    return OK;
}
