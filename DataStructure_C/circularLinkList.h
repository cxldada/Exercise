#ifndef _CIRCULAR_LINK_LIST_
#define _CIRCULAR_LINK_LIST_

#include "macro.h"

#ifndef CirLinkElemType
#define CirLinkElemType int
#endif

typedef struct CLNode{
    CirLinkElemType data;
    struct CLNode *next;
} CLNode, *Clinklist;

// initialize
Status InitList(Clinklist list);
void CreateList(Clinklist list, int n);
Status DestoryList(Clinklist list);
Status ClearList(Clinklist list);

int ListEmpty(Clinklist list);
int ListLength(Clinklist list);

Status GetElem(Clinklist list, int i, LinkElemType *data);
LNode *LocateElem(Clinklist list, LinkElemType elem);

Status ListInsert(Clinklist list, int i, LinkElemType elem);
Status ListDelete(Clinklist list, int i, LinkElemType *elem);

void UnionList(Clinklist la, Clinklist lb);

#endif