#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_

#include "macro.h"

#ifndef SequenceElemType
#define SequenceElemType int
#endif

typedef struct {
    SequenceElemType *data;
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
Status GetElem(SqList l, int i, SequenceElemType *e);

// using func to find position of e in l
// return 0: is not find;
int LocateElem(SqList l, SequenceElemType e);

// insert and delete
Status ListInsert(SqList *l, int i, SequenceElemType e);
Status ListDelete(SqList *l, int i, SequenceElemType *e);

void ListTraverse(SqList l, Status(*visit)(SequenceElemType e));

#endif