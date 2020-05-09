#include "stack_sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 10 to 8
void conversion() {
    int num;
    SqStack stack;
    InitStack(&stack);
    printf("please input a number: ");
    scanf("%d", &num);
    while(num) {
        Push(&stack, num % 8);
        num /= 8;
    }
    printf("\n");
    while(!StackEmpty(stack)) {
        Pop(&stack, &num);
        printf("%d", num);
    }
    printf("\n");
}

void matchBracket() {
    char *str;
    SqStack stack;
    InitStack(&stack);
    printf("please input check string: ");
    scanf("%s", str);
    for (int i = 0; str[i] != '\n'; ++i) {
        int e;
        GetTop(stack, &e);
        switch (str[i]) {
            case '}': {
                if (e == '{') {
                    Pop(&stack, &e);
                    continue;
                }
            } break;
            case ']': {
                if (e == '[') {
                    Pop(&stack, &e);
                    continue;
                }
            } break;
            case ')': {
                if (e == '(') {
                    Pop(&stack, &e);
                    continue;
                }
            } break;
            default: {
                Push(&stack, str[i]);
            } break;
        }
    }
    if (StackEmpty(stack)) {
        printf("is matching!\n");
    } else {
        printf("no matching!\n");
    }
}

int main() {
    //conversion();
    matchBracket();
    exit(0);
}
