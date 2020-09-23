#include "sequence.h"
#include <stdlib.h>
#include <stdio.h>

// initialize sequence list
Status InitList(SqList *l) {
    l->data = malloc(LIST_INIT_SIZE * sizeof(SqElemType));
    if (!l->data)
        exit(OVERFLOW);

    l->length = 0;
    l->size = LIST_INIT_SIZE;
    return OK;
}

Status DestroyList(SqList *l) {
    free(l->data);
    l->length = 0;
    l->size = 0;
    return OK;
}

Status ClearList(SqList *l) {
    l->length = 0;
    return OK;
}

int ListEmpty(SqList l) {
    return (l.length == 0);
}

int ListLength(SqList l) {
    return l.length;
}

// get element data from position i
Status GetElem(SqList l, int i, SqElemType *e) {
    if (i < 1 || i > l.length)
        return ERROR;

    *e = l.data[i - 1];
    return OK;
}

int LocateElem(SqList l, SqElemType e) {
    for (int i = 0; i < l.length; ++i) {
        if (e == l.data[i])
            return i + 1;
    }

    return 0;
}

Status ListInsert(SqList *l, int i, SqElemType e) {
    if (i < 1 || i > (l->length + 1))
        return ERROR;

    if (l->length >= l->size) {
        SqElemType *newbase = realloc(l->data,
                                      (l->size + LISTINCREMENT) * sizeof(SqElemType));
        if (!newbase)
            exit(OVERFLOW);
        l->data = newbase;
        l->size += LISTINCREMENT;
    }

    // 最坏的情况为O(n)
    for (int pos = l->length; pos > (i - 1); --pos) {
        l->data[pos] = l->data[pos - 1];
    }

    l->data[i - 1] = e;
    ++l->length;
    return OK;
}

Status ListDelete(SqList *l, int i, SqElemType *e) {
    if (i < 1 || i > l->length)
        return ERROR;

    *e = l->data[i - 1];
    for (int pos = (i - 1); pos < (l->length - 1); ++pos) {
        l->data[pos] = l->data[pos + 1];
    }

    --l->length;
    return OK;
}

void ListTraverse(SqList l, Status (*visit)(SqElemType e)) {
    for (int i = 0; i < l.length; ++i)
        if (visit(l.data[i]) == ERROR)
            return;
}

// O(la.length + lb.length)
void MergeList_Sq(SqList la, SqList lb, SqList *lc) {
    // la,lb is ASC order，so lc mast be ASC order;
    lc->size = lc->length = la.length + lb.length;
    lc->data = malloc(lc->size * sizeof(SqElemType));
    if(!lc->data)
        exit(OVERFLOW);

    int i = 0, j = 0, n = 0;
    while (i < la.length && j < lb.length) {
        if(la.data[i] < lb.data[j]){
            lc->data[n++] = la.data[i++];
        }else {
            lc->data[n++] = lb.data[j++];
        }
    }
    while(i < la.length)
        lc->data[n++] = la.data[i++];

    while(j < lb.length)
        lc->data[n++] = lb.data[j++];
}

void UnionList_Sq(SqList *la, SqList lb) {
    for (int i = 0; i < lb.length; ++i) {
        int pos = LocateElem(*la, lb.data[i]);
        if (!pos) {
            ListInsert(la, la->length + 1, lb.data[i]);
        }
    }
}

int main(int argc, char const *argv[]) {
    SqList l;
    InitList(&l);
    printf("is empty: %d\n", ListEmpty(l));
    //ListInsert(&l, 1, "aaa");
    printf("is empty: %d\n", ListEmpty(l));
    for (int i = 2; i < 11; ++i)
        ListInsert(&l, i, i + 10);

    SqElemType elem;
    ListDelete(&l, 10, &elem);

    //ListTraverse(l, &visit);
    DestroyList(&l);

    return 0;
}
