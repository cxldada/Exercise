#include "macro.h"
#include "myList.h"
#include <stdlib.h>

int InitList(LinkList list) {
    list->data = 0;
    list->next = NULL;
    return OK;
}

int ClearList(LinkList list) {
    ListNode *p, *q;
    p = list->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;
}

bool ArrayEmpty(LinkList list) {
    return (list->data == 0);
}

int ListLength(LinkList list) {
    return list->data;
}

int GetElem(LinkList list, int i, int *elem) {
    if (i < 0 || i > list->data)
        return OVERFLOW;

    ListNode *p = list->next;
    while (i > 0) {
        p = p->next;
        i--;
    }

    *elem = p->data;
    return OK;
}

int LocateElem(LinkList list, int elem) {
    int i = 0;
    ListNode *p = list->next;
    while(p) {
        i++;
        if(p->data == elem)
            return i;
    }

    return ERROR;
}

int ListInsert(LinkList list, int i, int elem) {
    ListNode *addNode = (ListNode *)malloc(sizeof(ListNode));
    if (addNode == NULL)
        return OVERFLOW;
}

int ListDelete(LinkList list, int i, int *elem);
int UniteList(LinkList p, LinkList q);

int main(int argc, char const *argv[]) {
    return 0;
}
