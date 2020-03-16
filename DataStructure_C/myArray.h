#ifndef _MY_ARRAY_H_
#define _MY_ARRAY_H_

#include <stdbool.h>

#define ARRAY_INIT_SIZE 64
#define ARRAY_INCREMENT 10

typedef struct {
    int *arr;
    int length;
    int space;
} MyArray;

int InitArray(MyArray *array);
int DestoryArray(MyArray *array);
int ClearArray(MyArray *array);
bool ArrayEmpty(MyArray array);
int ArrayLength(MyArray array);
int GetElem(MyArray array, int i, int *elem);
int LocateElem(MyArray array, int elem);
int ArrayInsert(MyArray *array, int i, int elem);
int ArrayDelete(MyArray *array, int i, int *elem);
int uniteArray(MyArray *p, MyArray q);

#endif