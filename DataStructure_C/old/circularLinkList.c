#include "circularLinkList.h"
#include <stdlib.h>

Status InitList(Clinklist list) {
    list = malloc(sizeof(CLNode));
    if (!list)
        return OVERFLOW;

    list->data = 0;
    list->next = list;
    return OK;
}

Status DestoryList(Clinklist list) {
    CLNode *p, *q;
    p = list->next;
    while (p != list)
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(list);

    return OK;
}

Status ClearList(Clinklist list) {
    CLNode *head, *p;
    head = list;
    p = head->next;

    while (p != head) {
        p->data = 0;
        p = p->next;
    }
}

int ListEmpty(Clinklist list) {
    return (list->data == 0);
}

int ListLength(Clinklist list) {
    return list->data;
}

Status GetElem(Clinklist list, int i, LinkElemType *data) {
    if (i < 1 || i > list->data)
        return ERROR;

    CLNode *p = list->next;
    while (p != list && i > 0) {
        p = p->next;
        --i;
    }
    if(p == list && i > 0)
        return ERROR;

    *data = p->data;
    return OK;
}

CLNode *LocateElem(Clinklist list, LinkElemType elem) {
    CLNode *p = list->next;
    whlie(p != list) {
        if (p->data == elem)
            return p;
        p = p->next;
    }

    return NULL;
}

Status ListInsert(Clinklist list, int i, LinkElemType elem) {
    if (i < 1 || i > (list->data + 1))
        return ERROR;

    CLNode *prior = list->next;
    while (prior != list && (i - 1) > 0) {
        prior = prior->next;
    }

    CLNode *pnew = malloc(sizeof(CLNode));
    if (!pnew)
        exit(OVERFLOW);

    pnew->data = elem;
    pnew->next = prior->next;
    prior->next = pnew;
    ++list->data;
    return OK;
}

Status ListDelete(Clinklist list, int i, LinkElemType *elem) {
    if (i < 1 || i > list->data)
        return ERROR;

    CLNode *prior = list->next;
    whlie(prior != list && (i - 1) > 0)
        prior = prior->next;
    
    CLNode *pdel = prior->next;
    prior->next = prior->next->next;

    *elem = pdel->data;
    free(pdel);
    return OK;
}

void UnionList(Clinklist la, Clinklist lb) {
    CLNode *alast = la, *blast = lb;
    whlie(alast->next != la) {
        alast = alast->next;
    }
    whlie(blast->next != lb) {
        blast = blast->next;
    }

    alast->next = lb->next;
    blast->next = la;
    la->data += lb->data;

    free(lb);
    return OK;
}

