#include <stdio.h>
#include <stdlib.h>
#include "Sqlist.h"

// 构造一个空的顺序表
Status InitList_Sq(Sqlist *l){
    l->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!l->elem)
        exit(OVERFLOW);
    l->length = 0;
    l->listsize = LIST_INIT_SIZE;
    return OK;
}

// 销毁一个已存在的顺序表
Status DestoryList_Sq(Sqlist *l) {
    free(l->elem);
    l->length = 0;
    l->listsize = 0;
    return OK;
}

// 清空顺序表的元素
Status ClearList_Sq(Sqlist *l) {
    l->length = 0;
    return OK;
}

// 判断顺序表是否为空
Status ListEmpty_Sq(Sqlist l) {
    return (l.length == 0);
}

// 获取顺序表的元素个数
Status ListLength_Sq(Sqlist l) {
    return l.length;
}

// 获取元素
Status GetElem_Sq(Sqlist l, int i, ElemType *e) {
    if(l.length < i) {
        return OVERFLOW;
    }

    *e = l.elem[i];
    return OK;
}

// 在第i个位置之前插入新的元素e
Status ListInsert_Sq(Sqlist *l, int i, ElemType e) {
    if (i < 1 || i > (l->listsize + 1))
        return ERROR;
    
    if(l->length >= l->listsize) { // 增加空间
        ElemType *newbase;
        newbase = (ElemType *)realloc(l->elem, ((l->length + LIST_INCREMENT) * sizeof(ElemType)));
        if(!newbase)
            exit(OVERFLOW);

        l->elem = newbase;
        l->listsize += LIST_INCREMENT;
    }

    ElemType *q, *p;
    q = &(l->elem[i - 1]);
    for (p = &(l->elem[l->length - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }

    *q = e;
    ++(l->length);
    return OK;
}

// 删除第i个位置上的元素，并用e返回其值
Status ListDelete_Sq(Sqlist *l, int i, ElemType *e) {
    if(l->length == 0 || i < 1 || i > l->length)
        return ERROR;

    ElemType *p, *q;
    p = &(l->elem[i - 1]);
    q = l->elem + l->length - 1;
    *e = *p;

    for (++p; p <= q; ++p) {
        *(p - 1) = *p;
    }

    --(l->length);
    return OK;
}

// 查找第一个与e符合compare关系的元素
// int compare(ElemType a, ElemType b){}
int LocateElem_Sq(Sqlist l, ElemType e, int *compare(ElemType, ElemType)) {
    for (int i = 0; i < l.length; ++i) {
        if (compare(l.elem[i], e) == 0) {
            return (i + 1);
        }
    }

    return 0;
}

// 遍历打印顺序表
Status ListTraverse(Sqlist l) {
    printf("顺序表中的元素有: ");
    for (int i = 0; i < l.length; ++i) {
        printf("%d ", l.elem[i]);
    }
    printf("\n");
    return OK;
}

// 合并两个递增顺序
void MergeList_Sq(Sqlist la, Sqlist lb, Sqlist *lc) {
    int len_a, len_b, i, j, k;

    len_a = la.length;
    len_b = lb.length;

    lc->elem = (ElemType *)malloc((len_a + len_b) * sizeof(ElemType));
    if(!lc->elem)
        exit(OVERFLOW);
    lc->length = 0;
    lc->listsize = len_a + len_b;

    i = 0;
    j = 0;
    k = 0;
    while (i < la.length && j < lb.length) {
        if(la.elem[i] < lb.elem[j]) {
            lc->elem[k++] = la.elem[i++];
        } else {
            lc->elem[k++] = lb.elem[j++];
        }
    }

    while(i < la.length) {
        lc->elem[k++] = la.elem[i++];
    }
    while(j < lb.length) {
        lc->elem[k++] = lb.elem[j++];
    }
}

int main() {
    Sqlist l;
    if(!InitList_Sq(&l))
        exit(1);

    ListInsert_Sq(&l, 1, 2);

    ListTraverse(l);

    return 0;
}