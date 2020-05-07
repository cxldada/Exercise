#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include "macro.h"

#ifndef LinkElemType
#define LinkElemType int
#endif

// 单向链表
typedef struct LNode {
    LinkElemType data;
    struct LNode *next;
} LNode, *LinkList;

// initialize
Status InitList(LinkList list);
void CreateList(LinkList list, int n);
Status DestoryList(LinkList list);
Status ClearList(LinkList list);

int ListEmpty(LinkList list);
int ListLength(LinkList list);

Status GetElem(LinkList list, int i, LinkElemType *data);
LNode *LocateElem(LinkList list, LinkElemType elem);

// 单链表的插入和删除操作
Status ListInsert(LinkList list, int i, LinkElemType elem);
Status ListDelete(LinkList list, int i, LinkElemType *elem);

void ListTraverse(LinkList list, visit_func func);

void MergeList(LinkList la, LinkList lb, LinkList lc);

#endif
