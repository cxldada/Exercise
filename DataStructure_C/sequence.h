#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_

#include "macro.h"

typedef struct {
    ElemType *data;
    int length;
} SqList;

// initialize sequence list
Status InitList(SqList *l);
Status DestoryList(SqList *l);
Status ClearList(SqList *l);
int ListEmpty(SqList l);
int ListLength(SqList l);

// get element data from position i
Status GetElem(SqList l, int i, ElemType *e);

// using func to find position of e in l
// return 0: is not find;
int LocateElem(SqList l, ElemType e, compare_func func);

// find prior element of cur_e
Status PriorElem(SqList l, ElemType cur_e, ElemType *pre_e);
Status NextElem(SqList l, ElemType cur_e, ElemType *next_e);

// insert and delete
Status ListInsert(SqList *l, int i, ElemType e);
Status ListDelete(SqList *l, int i, ElemType *e);

void ListTraverse(SqList l, visit_func func);

#endif