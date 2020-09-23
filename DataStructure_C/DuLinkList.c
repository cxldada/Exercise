#include "DuLinkList.h"

DuLNode *GetElem(Clinklist list, int i) {
    DuLNode *pNode = list->next;
    while (pNode && i > 0) {
        pNode = pNode->next;
        --i;
    }

    return pNode;
}

Status ListInsert(DuLinkList list, int i, LinkElemType e) {

    DuLNode *pNode = GetElem(list, i);
    if(!pNode)
        return ERROR;

    DuLNode *pNew = malloc(sizeof(DuLNode));
    if (!pNew)
        return ERROR;
    pNew->data = e;

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

    DuLNode *pNode = GetElem(list, i);
    if(pNode)
        return ERROR;

    pNode->prior->next = pNode->next;
    pNode->next->prior = pNode->prior;
    free(pNode);
    --list->data;
    return OK;
}