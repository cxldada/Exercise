#ifndef _UNIVERSAL_LINK_LIST_
#define _UNIVERSAL_LINK_LIST_

#include "macro.h"

#ifndef ElemType
#define ElemType int
#endif

// Node structure;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} * Link, *Position;

// link structure;
typedef struct {
    Link head, tail;
    int len;
} LinkList;

Status MakeNode(Link p, ElemType e);
void FreeNode(Link p);
Status InitList(LinkList *list);
Status ClearList(LinkList *list);

// h is list head, insert s node to first of h;
Status InsFirst(Link h, Link s);
Status DelFirst(Link h, Link q);

Status Append(LinkList *list, Link s);
Status Remove(LinkList *list, Link q);

// p in list, insert before s to p;
Status InsBefore(LinkList *list, Link p, Link s);
Status InsAfter(LinkList *list, Link p, Link s);

Status SetCurElem(Link p, ElemType e);
ElemType GetCurElem(Link p);

Status ListEmpty(LinkList list);
int ListLength(LinkList list);

Position GetHead(LinkList list);
Position GetLast(LinkList list);
Position PriorPos(LinkList list, Link p);
Position NextPos(LinkList list, Link p);

Status LocatePos(LinkList list, int i, Link p);
Position LocateElem(LinkList list, ElemType e, Status (*compare)(ElemType, ElemType));
Status ListTraverse(LinkList list, Status (*visit)());

#endif