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
    char str[10];
    SqStack stack;
    InitStack(&stack);
    printf("please input check string: ");
    scanf("%s", str);
    for (int i = 0; str[i] != '\0'; ++i) {
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

void LineEdit() {
    SqStack stack;
    InitStack(&stack);
    char ch = getchar(), c;
    while (ch != EOF) {
        while (ch != EOF && ch != '\n') {
            switch (ch) {
                case '#':
                    Pop(&stack, c);
                    break;
                case '@':
                    ClearStack(&stack);
                    break;
                default:
                    Push(&stack, ch);
                    break;
            }
        }
        // 字符串收集处理
        ClearStack(&stack);
        if(ch != EOF)
            ch = getchar();
    }
    DestoryStack(&stack);
}

void move(char x, int n, char y) {
    printf("move %d: from %s to %s", x, y);
}

// hanoi
void hanoi(int n, char x, char y, char z) {
    if(n == 1) {
        move(x, 1, z);
    }
    else {
        // 将第二大的挪到 中间的柱子去
        hanoi(n - 1, x, z, y);
        move(x, n, y);
        hanoi(n - 1, y, x, z);
    }
}

int main() {
    // conversion();
    // matchBracket();
    exit(0);
}
