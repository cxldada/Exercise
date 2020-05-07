#ifndef __MY_DU_LIST_H__
#define __MY_DU_LIST_H__

#include "macro.h"

#ifndef DLinkElemType
#define DLinkElemType int
#endif

// 双向链表
typedef struct DuLNode {
    LinkElemType data;
    struct DuLNode *prior;
    struct DuLNode *next;
} DuLNode, *DuLinkList;

// 双向链表的插入和删除操作
Status ListInsert(DuLinkList list, int i, LinkElemType elem);
Status ListDelete(DuLinkList list, int i, LinkElemType *elem);

#endif