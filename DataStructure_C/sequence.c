#include "sequence.h"

// initialize sequence list
Status InitList(SqList *l) {
    l->data = malloc(_MAXSIZE_ * sizeof(SequenceElemType));
    if (!l->data)
        exit(OVERFLOW);

    l->length = 0;
    l->size = _MAXSIZE_;
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
Status GetElem(SqList l, int i, SequenceElemType *e) {
    if (i < 1 || i > l.length)
        return ERROR;

    *e = l.data[i - 1];
    return OK;
}

int LocateElem(SqList l, SequenceElemType e) {
    for (int i = 0; i < l.length; ++i) {
        if (e == l.data[i])
            return i + 1;
    }

    return 0;
}

Status ListInsert(SqList *l, int i, SequenceElemType e) {
    if (i < 1 || i > (l->length + 1) || l->length == l->size)
        return ERROR;

    for (int pos = l->length; pos > (i - 1); --pos) {
        l->data[pos] = l->data[pos - 1];
    }

    l->data[i - 1] = e;
    ++l->length;
    return OK;
}

Status ListDelete(SqList *l, int i, SequenceElemType *e) {
    if (i < 1 || i > l->length || l->length == 0)
        return ERROR;

    *e = l->data[i - 1];
    for (int pos = (i - 1); pos < (l->length - 1); ++pos) {
        l->data[pos] = l->data[pos + 1];
    }

    --l->length;
    return OK;
}

void ListTraverse(SqList l, Status (*visit)(SequenceElemType e)) {
    for (int i = 0; i < l.length; ++i)
        if (visit(l.data[i]) == ERROR)
            return;
}

int main(int argc, char const *argv[]) {
    SqList l;
    InitList(&l);
    printf("is empty: %d\n", ListEmpty(l));
    ListInsert(&l, 1, "aaa");
    printf("is empty: %d\n", ListEmpty(l));
    for (int i = 2; i < 11; ++i)
        ListInsert(&l, i, i + 10);

    SequenceElemType elem;
    ListDelete(&l, 10, &elem);

    ListTraverse(l, &visit);
    DestroyList(&l);

    return 0;
}
