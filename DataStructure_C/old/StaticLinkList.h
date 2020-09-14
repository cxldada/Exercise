#ifndef _STATIC_LINK_LIST_H_
#define _STATIC_LINK_LIST_H_

#include "macro.h"

#ifndef SLinkElemType
#define SLinkElemType int
#endif

#define _SLINK_MAXSIZE_ 10

typedef struct {
    SLinkElemType data;
    int cur;
} component, SLinkList[_SLINK_MAXSIZE_];

Status InitList(SLinkList sl);
Status ClearList(SLinkList sl);
int ListEmpty(SLinkList sl);
int ListLength(SLinkList sl);

Status GetElem(SLinkList sl, int i, SLinkElemType *data);
int LocateElem(SLinkList sl, SLinkElemType e);

Status ListInsert(SLinkList sl, int i, SLinkElemType elem);
Status ListDelete(SLinkList sl, int i, SLinkElemType *elem);

void printfSlist(SLinkList sl);

#endif