#include "DuLinkList.h"

Status ListInsert(DuLinkList list, int i, LinkElemType e) {
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

Status ListDelete(DuLinkList list, int i, LinkElemType *elem) {
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