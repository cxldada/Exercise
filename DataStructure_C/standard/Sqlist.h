#ifndef _SEQUENCE_LIST_H_
#define _SEQUENCE_LIST_H_

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

// 线性表的存储空间的初始分配量
#define LIST_INIT_SIZE 100

// 线性表存储空间的分配增量
#define LIST_INCREMENT 10

typedef int Status;
typedef int ElemType;

typedef struct {
    ElemType *elem; // 存储空间基址
    int length; // 当前长度
    int listsize; // 当前分配的存储容量(以sizeof(ElemType))为单位
} Sqlist;

/******************** 操作声明 **************************/

// 构造一个空的顺序表
Status InitList_Sq(Sqlist *l);

// 销毁一个已存在的顺序表
Status DestoryList_Sq(Sqlist *l);

// 清空顺序表的元素
Status ClearList_Sq(Sqlist *l);

// 判断顺序表是否为空
Status ListEmpty_Sq(Sqlist l);

// 获取顺序表的元素个数
Status ListLength_Sq(Sqlist l);

// 获取元素
Status GetElem_Sq(Sqlist l, int i, ElemType *e);

// 在第i个位置之前插入新的元素e
Status ListInsert_Sq(Sqlist *l, int i, ElemType e);

// 删除第i个位置上的元素，并用e返回其值
Status ListDelete_Sq(Sqlist *l, int i, ElemType *e);

// 查找第一个与e符合compare关系的元素
// int compare(ElemType a, ElemType b);
int LocateElem_Sq(Sqlist l, ElemType e, Status *compare(ElemType, ElemType));

// 遍历打印顺序表
Status ListTraverse(Sqlist l);

// 合并两个递增顺序
void MergeList_Sq(Sqlist la, Sqlist lb, Sqlist *lc);

#endif