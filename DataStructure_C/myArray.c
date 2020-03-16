#include "myArray.h"
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"

int InitArray(MyArray *array) {
    array->arr = (int *)malloc(sizeof(int) * ARRAY_INIT_SIZE);
    if (!array->arr)
        return OVERFLOW;

    array->length = 0;
    array->space = ARRAY_INIT_SIZE;
    return OK;
}

int DestoryArray(MyArray *array) {
    free(array->arr);
    array->space = 0;
    array->length = 0;

    return OK;
}

int ClearArray(MyArray *array) {
    for (int i = 0; i < array->length; i++) {
        array->arr[i] = 0;
    }
    array->length = 0;
    return OK;
}

bool ArrayEmpty(MyArray array) {
    return (array.length == 0);
}

int ArrayLength(MyArray array) {
    return array.length;
}

int GetElem(MyArray array, int i, int *elem) {
    *elem = array.arr[i];
    return OK;
}

// 查找elem在array中代下标
int LocateElem(MyArray array, int elem) {
    for (int i = 0; i < array.length; ++i) {
        if (array.arr[i] == elem)
            return i;
    }
    return ERROR;
}

// 在位置i之前插入元素elem
int ArrayInsert(MyArray *array, int i, int elem) {
    if (i < 1 || i > (array->length + 1))
        return ERROR;

    if (array->length == array->space) {
        array->arr = (int *)realloc(array->arr, array->space + ARRAY_INCREMENT);
        if (!array->arr)
            return OVERFLOW;

        array->space += ARRAY_INCREMENT;
    }

    for (int j = array->length; j > (i - 1); --j) {
        array->arr[j] = array->arr[j - 1];
    }
    array->arr[i - 1] = elem;
    array->length++;

    return OK;
}

int ArrayDelete(MyArray *array, int i, int *elem) {
    if (i < 0 || i > array->length)
        return ERROR;

    *elem = array->arr[i];
    for (int j = i; j < array->length; ++j) {
        array->arr[j] = array->arr[j + 1];
    }
    array->length--;

    return OK;
}

int uniteArray(MyArray *p, MyArray q) {
    for (int i = 0; i < q.length; ++i) {
        if(LocateElem(*p, q.arr[i]) == ERROR) {
            ArrayInsert(p, p->length, q.arr[i]);
        }
    }
    return OK;
}

int main(int argc, char *argv[]) {
    MyArray myarr;
    if (InitArray(&myarr) == ERROR)
        printf("initArray error\n");

    printf("array empty: %d\n", ArrayEmpty(myarr));
    printf("array length: %d\n", ArrayLength(myarr));

    for (int i = 0; i < 64; ++i)
        ArrayInsert(&myarr, 1, i + 12);

    printf("before change: %d\n", myarr.arr[63]);
    ArrayInsert(&myarr, myarr.length, 1000);
    printf("after change: %d\n", myarr.arr[64]);

    int del = 0;
    ArrayDelete(&myarr, 10, &del);

    int index = LocateElem(myarr, 24);
    int value;
    GetElem(myarr, index, &value);
    printf("24 in array local: %d\n", index);
    printf("local %d array is: %d\n", index, value);

    ClearArray(&myarr);
    DestoryArray(&myarr);

    return 0;
}
