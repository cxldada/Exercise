#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_

#include "macro.h"

#ifndef SqElemType
#define SqElemType int
#endif

typedef struct {
    SqElemType *data;
    int length;
    int size;
} SqList;

// initialize sequence list
Status InitList(SqList *l);
Status DestroyList(SqList *l);
Status ClearList(SqList *l);
int ListEmpty(SqList l);
int ListLength(SqList l);

// get element data from position i
Status GetElem(SqList l, int i, SqElemType *e);

// using func to find position of e in l
// return 0: is not find;
int LocateElem(SqList l, SqElemType e);

// insert and delete
Status ListInsert(SqList *l, int i, SqElemType e);
Status ListDelete(SqList *l, int i, SqElemType *e);

void ListTraverse(SqList l, Status(*visit)(SqElemType e));

void MergeList_Sq(SqList la, SqList lb, SqList *lc);

void UnionList_Sq(SqList *la, SqList lb);

#endif