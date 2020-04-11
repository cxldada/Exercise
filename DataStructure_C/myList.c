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

int GetElem(LinkList list, int i, ListNode *elem) {
    if (i < 0 || i > list->data)
        return OVERFLOW;

    ListNode *p = list->next;
    while (i > 0) {
        p = p->next;
        i--;
    }

    elem = p;
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
    if (i < 0 || i > list->data)
        return OVERFLOW;

    ListNode *addNode = (ListNode *)malloc(sizeof(ListNode));
    if (addNode == NULL)
        return OVERFLOW;

    addNode->data = elem;
    ListNode *prior;
    if(GetElem(list, i, prior) != OK){
        return ERROR;
    }

    addNode->next = prior->next;
    prior->next = addNode;
    list->data++;

    return OK;
}

int ListDelete(LinkList list, int i, int *elem) {
    if(i < 0 || i > list->data)
        return OVERFLOW;

    ListNode *prior;
    if (GetElem(list, (i - 1), prior) != OK)
        return ERROR;

    *elem = prior->next->data;
    prior->next = prior->next->next;

    return OK;
}

// 合并两个有序链表，合并后还是有序的
int UniteList(LinkList p, LinkList q) {
    ListNode *cur, *star;
    cur = star = p;
    star->data = 0;
    ListNode *a = p->next;
    ListNode *b = q->next;
    while (a && b) {
        if (a->data > b->data) {
            cur->next = b;
            cur = b;
            b = b->next;
        } else {
            cur->next = a;
            cur = a;
            a = a->next;
        }
        star->data++;
    }
    while (a) {
        cur->next = a;
        a = a->next;
        star->data++;
    }
    while (b) {
        cur->next = b;
        b = b->next;
        star->data++;
    }

    p = star;
    return OK;
}

int main(int argc, char const *argv[]) {
    return 0;
}
