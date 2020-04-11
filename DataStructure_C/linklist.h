#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include "macro.h"

// 单向链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;
//typedef struct LNode LNode;
//typedef struct LNode *LinkList;

// 双向链表
typedef struct DuLNode {
    ElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;
//typedef struct DuLNode DuLNode;
//typedef struct DuLNode *DuLinkList;

// initialize
Status InitList(LinkList list);
Status DestoryList(LinkList list);
Status ClearList(LinkList list);

int ListEmpty(LinkList list);
int ListLength(LinkList list);

int GetElem(LinkList list, int i, ElemType *data);
LNode *LocateElem(LinkList list, ElemType elem, compare_func func);

// 单链表的插入和删除操作
int ListInsert(LinkList list, int i, ElemType elem);
int ListDelete(LinkList list, int i, ElemType *elem);

// 双向链表的插入和删除操作
Status ListInsert_Dul(DuLinkList list, int i, ElemType elem);
Status ListDelete_Dul(DuLinkList list, int i, ElemType *elem);

void ListTraverse(LinkList list, visit_func func);

#endif
