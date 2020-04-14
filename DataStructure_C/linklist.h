#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include "macro.h"

#ifndef LinkListElemType
#define LinkListElemType int
#endif

// 单向链表
typedef struct LNode {
    LinkListElemType data;
    struct LNode *next;
} LNode, *LinkList;

// 双向链表
typedef struct DuLNode {
    LinkListElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;

// initialize
Status InitList(LinkList list);
Status DestoryList(LinkList list);
Status ClearList(LinkList list);

int ListEmpty(LinkList list);
int ListLength(LinkList list);

int GetElem(LinkList list, int i, LinkListElemType *data);
LNode *LocateElem(LinkList list, LinkListElemType elem, compare_func func);

// 单链表的插入和删除操作
int ListInsert(LinkList list, int i, LinkListElemType elem);
int ListDelete(LinkList list, int i, LinkListElemType *elem);

// 双向链表的插入和删除操作
Status ListInsert_Dul(DuLinkList list, int i, LinkListElemType elem);
Status ListDelete_Dul(DuLinkList list, int i, LinkListElemType *elem);

void ListTraverse(LinkList list, visit_func func);

#endif
