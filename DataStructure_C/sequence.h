#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_

#include "macro.h"

typedef struct {
    _SQ_ELEM_TYPE *data;
    int length;
} SqList;

typedef int (*compare_func)(_SQ_ELEM_TYPE l, _SQ_ELEM_TYPE r);
typedef void (*visit_func)(_SQ_ELEM_TYPE e);

// initialize sequence list
Status InitList(SqList *l);
Status DestoryList(SqList *l);
Status ClearList(SqList *l);
int ListEmpty(SqList l);
int ListLength(SqList l);

// get element data from position i
Status GetElem(SqList l, int i, _SQ_ELEM_TYPE *e);

// using func to find position of e in l
// return 0: is not find;
int LocateElem(SqList l, _SQ_ELEM_TYPE e, compare_func func);

// find prior element of cur_e
Status PriorElem(SqList l, _SQ_ELEM_TYPE cur_e, _SQ_ELEM_TYPE *pre_e);
Status NextElem(SqList l, _SQ_ELEM_TYPE cur_e, _SQ_ELEM_TYPE *next_e);

// insert and delete
Status ListInsert(SqList *l, int i, _SQ_ELEM_TYPE e);
Status ListDelete(SqList *l, int i, _SQ_ELEM_TYPE *e);

void ListTraverse(SqList l, visit_func func);

#endif