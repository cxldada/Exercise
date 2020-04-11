#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include "macro.h"

// 单向链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// initialize
Status InitList(LinkList list);
Status DestoryList(LinkList list);
Status ClearList(LinkList list);

int ListEmpty(LinkList list);
int ListLength(LinkList list);

int GetElem(LinkList list, int i, ElemType *data);
LNode *LocateElem(LinkList list, ElemType elem, compare_func func);

int ListInsert(LinkList list, int i, ElemType elem);
int ListDelete(LinkList list, int i, ElemType *elem);

void ListTraverse(LinkList list, visit_func func);

#endif
