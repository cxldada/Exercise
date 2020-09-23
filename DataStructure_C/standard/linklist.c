#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

Status InitList_Link(LinkList list) {
    list = (LinkList)malloc(sizeof(LNode));
    if(!list)
        exit(OVERFLOW);

    list->data = 0;
    list->next = NULL;

    return OK;
}

void CreateList_Link_Head(LinkList list, int n) {
    LNode *p;
    list = (LinkList)malloc(sizeof(LNode));
    if(!list)
        exit(OVERFLOW);
    list->next = NULL;
    for (int i = n; i > 0; --i) {
        p = (LNode *)malloc(sizeof(LNode));
        if(!p)
            exit(OVERFLOW);
        scanf(&(p->data));
        p->next = list->next;
        list->next = p;
    }
}

void CreateList_Link_Tail(LinkList list, int n) {
    LNode *p, *t;
    list = (LinkList)malloc(sizeof(LNode));
    if(!list)
        exit(OVERFLOW);
    list->next = NULL;
    t = list;
    for (int i = n; i > 0; --i) {
        p = (LNode *)malloc(sizeof(LNode));
        if(!p)
            exit(OVERFLOW);
        scanf(&p->data);
        p->next = t->next;
        t->next = p;
        t = p;
    }
}

Status DestoryList_Link(LinkList list) {
    LNode *p, *q;
    p = list->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    free(list);
    return OK;
}

Status ClearList_Link(LinkList list) {
    LNode *p, *q;
    p = list->next;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    return OK;
}

int ListEmpty_Link(LinkList list) {
    if (list)
        return (list->next == NULL);
    return TRUE;
}

int ListLength_Link(LinkList list) {
    if (list)
        return list->data;
    return 0;
}

Status GetElem_Link(LinkList list, int i, ElemType *data) {
    LNode *p = list->next;
    int j = 1;
    while(p && j < i) {
        p = p->next;
    }
    if(!p || j > i)
        return ERROR;

    *data = p->data;
    return OK;
}

LNode *LocateElem_Link(LinkList list, ElemType elem) {
    LNode *p = list->next;
    while (p && (p->data != elem)) {
        p = p->next;
    }

    if (p && (p->data == elem))
        return p;
    else
        return NULL;
}

// 单链表的插入和删除操作
Status ListInsert_Link(LinkList list, int i, ElemType elem) {
    LNode *p = list;
    int j = 0;
    while (p && j < (i - 1)) {
        p = p->next;
        ++j;
    }

    if (!p || j > (i - 1))
        return ERROR;

    LNode *s = (LNode *)malloc(sizeof(LNode));
    if(!s)
        exit(OVERFLOW);

    s->data = elem;
    s->next = p->next;
    p->next = s;
    ++list->data;
    return OK;
}

Status ListDelete_Link(LinkList list, int i, ElemType *elem) {
    LNode *p = list;
    int j = 0;
    while (p && j < (i - 1)) {
        p = p->next;
        ++j;
    }

    if (!p || !(p->next) || j > (i - 1))
        return ERROR;

    LNode *q = p->next;
    p->next = q->next;
    *elem = q->data;
    free(q);
    --list->data;
    return OK;
}

void ListTraverse_Link(LinkList list) {
    printf("单链表中的元素有: \n");
    LNode *p = list->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

void MergeList_Link(LinkList la, LinkList lb, LinkList lc) {
    LNode *pa, *pb, *pc;
    pa = la->next;
    pb = lb->next;
    lc = pc = la;
    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        } else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;
    free(lb);
}

int main() {
    return 0;
}