#include "linklist.h"

/**
 * 带头结点的单链表
 * */

// initialize
Status InitList(LinkList list) {
    list = malloc(sizeof(LNode));
    if (!list)
        return OVERFLOW;

    list->next = NULL;
    list->data = 0;
    return OK;
}

Status DestoryList(LinkList list) {
    LNode *p, *q;
    p = list;
    q = NULL;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }

    return OK;
}

Status ClearList(LinkList list) {
    return DestoryList(list);
}

// head node data save list length;
int ListEmpty(LinkList list) {
    return (list->data == 0);
}

int ListLength(LinkList list) {
    return list->data;
}

int GetElem(LinkList list, int i, ElemType *elem) {
    if (i < 1 || i > list->data)
        return ERROR;

    LNode *p = list->next;
    int pos = 0;
    while (p && pos < i) {
        p = p->next;
        ++pos;
    }

    *elem = p->data;
    return OK;
}

int compare(ElemType l, ElemType r) {
    return (l == r);
}

LNode *LocateElem(LinkList list, ElemType elem, compare_func func) {
    LNode *p = list->next;
    while (p) {
        if (func(elem, p->data))
            return p;

        p = p->next;
    }

    return NULL;
}

int ListInsert(LinkList list, int i, ElemType elem) {
    if (i < 1 || i > list->data)
        return ERROR;

    LNode *pNew = malloc(sizeof(LNode));
    if (pNew == NULL)
        return OVERFLOW;
    pNew->data = elem;

    int pos = 1;
    LNode *pPrior = list;
    while (pPrior && pos < i) {
        pPrior = pPrior->next;
        ++pos;
    }

    pNew->next = pPrior->next;
    pPrior->next = pNew;

    ++list->data;
    return OK;
}

int ListDelete(LinkList list, int i, ElemType *elem) {
    if (i < 1 || i > list->data)
        return ERROR;

    int pos = 1;
    LNode *pPrior = list;
    while (pPrior && pos < i) {
        pPrior = pPrior->next;
        ++pos;
    }

    LNode *pDel = pPrior->next;
    pPrior->next = pDel->next;

    *elem = pDel->data;
    free(pDel);
    return OK;
}

int main(int argc, char const *argv[]) {
    return 0;
}

// have head node
Status ListInsert_Dul(DuLinkList list, int i, ElemType e) {
    if (i < 1 || i > list->data)
        return ERROR;

    DuLNode *pNew = malloc(sizeof(DuLNode));
    if (!pNew)
        return ERROR;
    pNew->data = e;

    int pos = 1;
    DuLNode *pNode = list->next;
    while (pNode && pos < i) {
        pNode = pNode->next;
        ++pos;
    }

    pNew->prior = pNode->prior;
    pNew->prior->next = pNew;
    pNew->next = pNode;
    pNode->prior = pNew;

    ++list->data;
    return OK;
}

Status ListDelete_Dul(DuLinkList list, int i, ElemType *elem) {
    if (i < 1 || i > list->data)
        return ERROR;

    int pos = 1;
    DuLNode *pNode = list->next;
    while (pNode && pos < i) {
        pNode = pNode->next;
        ++pos;
    }

    pNode->prior->next = pNode->next;
    pNode->next->prior = pNode->prior;
    free(pNode);
    --list->data;
    return OK;
}
