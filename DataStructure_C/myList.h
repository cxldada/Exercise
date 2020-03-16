#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include <stdbool.h>

// 单向链表
typedef struct {
    int data;
    ListNode *next;
} ListNode, *LinkList;

int InitList(LinkList list);
int ClearList(LinkList list);
bool ArrayEmpty(LinkList list);
int ListLength(LinkList list);
int GetElem(LinkList list, int i, int *elem);
int LocateElem(LinkList list, int elem);
int ListInsert(LinkList list, int i, int elem);
int ListDelete(LinkList list, int i, int *elem);
int UniteList(LinkList p, LinkList q);

#endif