#ifndef _MY_STATIC_LIST_H_
#define _MY_STATIC_LIST_H_

#include <stdbool.h>

typedef int ElemType;

// 单向链表
typedef struct {
    ElemType data;
    int cur;
} SNode;

typedef struct SNode *StaticList;

int InitList(StaticList list);
int ClearList(StaticList list);
bool ArrayEmpty(StaticList list);
int ListLength(StaticList list);
int GetElem(StaticList list, int i, SNode *elem);
int LocateElem(StaticList list, int elem);
int ListInsert(StaticList list, int i, int elem);
int ListDelete(StaticList list, int i, int *elem);
int UniteList(StaticList p, StaticList q);

#endif
