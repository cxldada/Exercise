/**
 * 单链表的实现
 * */
#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include "common.h"

// 单向链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

// initialize
Status InitList_Link(LinkList list);
void CreateList_Link_Head(LinkList list, int n);
void CreateList_Link_Tail(LinkList list, int n);
Status DestoryList_Link(LinkList list);
Status ClearList_Link(LinkList list);

int ListEmpty_Link(LinkList list);
int ListLength_Link(LinkList list);

Status GetElem_Link(LinkList list, int i, ElemType *data);
LNode *LocateElem_Link(LinkList list, ElemType elem);

// 单链表的插入和删除操作(在第i个位置上插入删除)
Status ListInsert_Link(LinkList list, int i, ElemType elem);
Status ListDelete_Link(LinkList list, int i, ElemType *elem);

void ListTraverse_Link(LinkList list);

void MergeList_Link(LinkList la, LinkList lb, LinkList lc);

#endif
