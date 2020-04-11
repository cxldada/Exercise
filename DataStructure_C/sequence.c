#include "sequence.h"

// initialize sequence list
Status InitList(SqList *l) {
    l->data = malloc(_SQ_MAXSIZE_ * sizeof(_SQ_ELEM_TYPE));
    if(!l->data)
        exit(OVERFLOW);

    l->length = 0;
    return OK;
}

Status DestoryList(SqList *l) {
    free(l->data);
    l->length = 0;
    return OK;
}

Status ClearList(SqList *l){
    free(l->data); // free data

    l->data = malloc(_SQ_MAXSIZE_ * sizeof(_SQ_ELEM_TYPE));
    if(!l->data)
        exit(OVERFLOW);

    l->length = 0;
    return OK;
}

int ListEmpty(SqList l){
    return (l.length == 0);
}

int ListLength(SqList l) {
    return l.length;
}

// get element data from position i
Status GetElem(SqList l, int i, _SQ_ELEM_TYPE *e) {
    if(i < 1 || i > l.length)
        return ERROR;

    *e = l.data[i - 1];
    return OK;
}

int compare(_SQ_ELEM_TYPE l, _SQ_ELEM_TYPE r) {
    if(l == r)
        return 1;

    return 0;
}

// using func to find position of e in l
int LocateElem(SqList l, _SQ_ELEM_TYPE e, compare_func func) {
    for (int i = 0; i < l.length; ++i) {
        if (func(e, l.data[i]))
            return i + 1;
    }

    return 0;
}

// find prior element of cur_e
Status PriorElem(SqList l, _SQ_ELEM_TYPE cur_e, _SQ_ELEM_TYPE *pre_e) {
    int pos = LocateElem(l, cur_e, &compare);
    if(pos != 1)
        return GetElem(l, (pos - 1), pre_e);

    return ERROR;
}

Status NextElem(SqList l, _SQ_ELEM_TYPE cur_e, _SQ_ELEM_TYPE *next_e) {
    int pos = LocateElem(l, cur_e, &compare);
    if (pos != l.length)
        return GetElem(l, (pos + 1), next_e);

    return ERROR;
}

Status ListInsert(SqList *l, int i, _SQ_ELEM_TYPE e) {
    if (i < 1 || (l->length + 1) < i || l->length == _SQ_MAXSIZE_)
        return ERROR;

    for (int pos = l->length; pos > (i - 1); --pos) {
        l->data[pos] = l->data[pos - 1];
    }

    l->data[i - 1] = e;
    ++l->length;
    return OK;
}

Status ListDelete(SqList *l, int i, _SQ_ELEM_TYPE *e) {
    if(i < 1 || (i > l->length))
        return ERROR;

    *e = l->data[i - 1];
    for (int pos = (i - 1); pos < (l->length - 1); ++pos) {
        l->data[pos] = l->data[pos + 1];
    }

    --l->length;
    return OK;
}

void visit(_SQ_ELEM_TYPE e) {
    printf("%d \n", e);
}

void ListTraverse(SqList l, visit_func func) {
    for (int i = 0; i < l.length;++i)
        func(l.data[i]);
}


int main(int argc, char const *argv[])
{
    SqList l;
    InitList(&l);
    printf("is empty: %d\n", ListEmpty(l));
    ListInsert(&l, 1, 100);
    printf("is empty: %d\n", ListEmpty(l));
    for (int i = 2; i < 11;++i)
        ListInsert(&l, i, i + 10);

    _SQ_ELEM_TYPE elem;
    ListDelete(&l, 10, &elem);

    ListTraverse(l, &visit);

    return 0;
}
