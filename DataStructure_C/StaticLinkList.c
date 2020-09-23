#include <stdio.h>
#include <stdlib.h>
#include "StaticLinkList.h"

Status InitList(SLinkList sl) {
    int i = 0;
    for (i = _SLINK_MAXSIZE_ - 1; i > 0; --i) {
        sl[i].data = 0;
        sl[i].cur = i - 1;
    }
    sl[i + 1].cur = -1; // free end
    sl[_SLINK_MAXSIZE_ - 1].data = _SLINK_MAXSIZE_ - 2; // free length
    sl[0].cur = -1; // list end
    sl[0].data = 0; // list length

    return OK;
}

Status ClearList(SLinkList sl) {
    InitList(sl);
    return OK;
}

int ListEmpty(SLinkList sl) {
    return sl[0].data > 0;
}

int ListLength(SLinkList sl) {
    return sl[0].data;
}

Status GetElem(SLinkList sl, int i, SLinkElemType *data) {
    if (i < 1 || i > sl[0].data)
        return ERROR;

    int next = sl[0].cur;
    while(i > 0 && next != -1) {
        next = sl[next].cur;
        --i;
    }
    if (next == -1 || i > 0)
        return ERROR;

    return sl[next].data;
}

int LocateElem(SLinkList sl, SLinkElemType e) {
    int i = sl[0].cur;
    while (i && sl[i].data != e)
        i = sl[i].cur;

    return i;
}

Status ListInsert(SLinkList sl, int i, SLinkElemType elem) {
    if (i < 1 || i > (sl[0].data + 1))
        return ERROR;
    
    if((sl[0].data + 1) > sl[_SLINK_MAXSIZE_ - 1].data)
        return OVERFLOW;

    int pos = 0;
    while ((i - 1) > 0) {
        pos = sl[pos].cur;
        --i;
    }
    if ((i - 1) > 0 || pos == -1)
        return ERROR;

    int free = sl[_SLINK_MAXSIZE_ - 1].cur;
    sl[_SLINK_MAXSIZE_ - 1].cur = sl[free].cur;
    --sl[_SLINK_MAXSIZE_ - 1].data;

    sl[free].data = elem;
    sl[free].cur = sl[pos].cur;
    sl[pos].cur = free;
    ++sl[0].data;
    return OK;
}

Status ListDelete(SLinkList sl, int i, SLinkElemType *elem) {
    if(i < 1 || i > sl[0].data)
        return 0;

    int pos = 0;
    while ((i - 1) > 0) {
        pos = sl[pos].cur;
        --i;
    }
    if ((i - 1) > 0 || pos == -1)
        return ERROR;

    int del = sl[pos].cur;
    sl[pos].cur = sl[del].cur;
    --sl[0].data;

    *elem = sl[del].data;
    sl[del].cur = 0;
    sl[del].cur = sl[_SLINK_MAXSIZE_ - 1].cur;
    sl[_SLINK_MAXSIZE_ - 1].cur = del;
    ++sl[_SLINK_MAXSIZE_ - 1].data;

    return OK;
}

void printfSlist(SLinkList sl) {
    int pos = 0;
    printf("Static Link List Info:\n");
    while (pos != -1) {
        printf("data: %d,cur: %d\n", sl[pos].data, sl[pos].cur);
        pos = sl[pos].cur;
    }

    pos = _SLINK_MAXSIZE_ - 1;
    printf("Free Link List Info:\n");
    while (pos != -1) {
        printf("data: %d,cur: %d\n", sl[pos].data, sl[pos].cur);
        pos = sl[pos].cur;
    }
}

int main(void) {
    SLinkList slist;

    if (!InitList(slist))
        printf("initialize error !\n");

    printfSlist(slist);

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int data;
        printf("intput data: ");
        scanf("%d", &data);
        ListInsert(slist, ListLength(slist), data);
        printfSlist(slist);
    }

    printf("del pos(intput 0 to exit): ");
    scanf("%d", &n);
    while (n != 0) {
        int data;
        ListDelete(slist, n, &data);
        printfSlist(slist);
    }

    return 0;
}
