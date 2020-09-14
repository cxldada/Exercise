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
    list->data = 0; // lenght
    return OK;
}

void CreateList(LinkList list, int n) {
    list = (LinkList)malloc(sizeof(LNode));
    list->data = 0;
    list->next = NULL;

    for (int i = 0; i < n; ++i) {
        LNode *p = malloc(sizeof(LNode));
        scanf(&p->data);
        p->next = list->next;
        list->next = p;
        ++(list->data); // add length
    }
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

Status GetElem(LinkList list, int i, LinkElemType *data) {
    if (i < 1 || i > list->data)
        return ERROR;

    LNode *p = list->next;
    int pos = 1;
    while (p && pos < i) {
        p = p->next;
        ++pos;
    }

    *elem = p->data;
    return OK;
}

LNode *LocateElem(LinkList list, LinkElemType elem) {
    LNode *p = list->next;
    while (p) {
        if (elem == p->data))
            return p;

        p = p->next;
    }

    return NULL;
}

Status ListInsert(LinkList list, int i, LinkElemType elem) {
    if (i < 1 || i > list->data + 1)
        return ERROR;

    int pos = 0;
    LNode *pPrior = list;
    while (pPrior && pos < (i - 1)) {
        pPrior = pPrior->next;
        ++pos;
    }
    if(!pPrior || pos > (i - 1))return ERROR;

    LNode *pNew = malloc(sizeof(LNode));
    if (pNew == NULL)
        exit(OVERFLOW);

    pNew->data = elem;

    pNew->next = pPrior->next;
    pPrior->next = pNew;

    ++list->data;
    return OK;
}

Status ListDelete(LinkList list, int i, LinkElemType *elem) {
    if (i < 1 || i > list->data)
        return ERROR;

    int pos = 0;
    LNode *pPrior = list;
    while (pPrior && pos < (i - 1)) {
        pPrior = pPrior->next;
        ++pos;
    }
    if (!pPrior || pos > (i - 1))
        return ERROR;

    LNode *pDel = pPrior->next;
    pPrior->next = pDel->next;

    *elem = pDel->data;
    free(pDel);
    return OK;
}

void MergeList(LinkList la, LinkList lb, LinkList lc) {
    lc = la;
    LNode *pA = la->next, *pB = lb->next, *pC = lc;
    while (pA && pB) {
        if(pA->data <= pB->data){
            pC->next = pA;
            pC = pA;
            pA = pA->next;
        } else {
            pC->next = pB;
            pC = pB;
            pB = pB->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(lb);
}

int main(int argc, char const *argv[]) {
    return 0;
}
