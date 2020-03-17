
#ifndef __ADLIST_H__
#define __ADLIST_H__

typedef struct listNode {
    struct listNode *prev;
    struct listNode *next;
    void *value;
} listNode;

typedef struct listIter {
    listNode *next;
    int direction;
} listIter;

typedef struct list {
    listNode *head;
    listNode *tail;
    // 都是对值得操作
    void *(*dup)(void *ptr);             // 复制函数
    void (*free)(void *ptr);             // 释放空间函数
    int (*match)(void *ptr, void *key);  // 比较函数
    unsigned long len;                   //   长度
} list;

// 宏定义函数

#define listLength(l) ((l)->len)
#define listFirst(l) ((l)->head)
#define listLast(l) ((l)->tail)
#define listPrevNode(n) ((n)->prev)
#define listNextNode(n) ((n)->next)
#define listNodeValue(n) ((n)->value)

#define listSetDupMethod(l, m) ((l)->dep = (m))
#define listSetFreeMethod(l, m) ((l)->free = (m))
#define listSetMatchMethod(l, m) ((l)->match = (m))

#define lstGetDupMethod(l) ((l)->dup)
#define lstGetFreeMethod(l) ((l)->free)
#define lstGetMatchMethod(l) ((l)->match)

list *listCreate(void);
void listRelease(list *list);
void listEmpty(list *list);
list *listAddNodeHead(list *list, void *value);
list *listAddNodeTail(list *list, void *value);
list *listInsertNode(list *list, listNode *old_node, void *value, int after);
void listDelNode(list *list, listNode *node);
listIter *listGetIterator(list *list, int direction);
listNode *listNext(listIter *iter);
void listReleaseIterator(listIter *iter);
list *listDup(list *orig);
listNode *listSearchKey(list *list, void *key);
listNode *listIndex(list *list, long index);
void listRewind(list *list, listIter *li);
void listRewindTail(list *list, listIter *li);
void listRotate(list *list);
void listJoin(list *l, list *o);

// 迭代器遍历的方向
#define AL_START_HEAD 0
#define AL_START_TAIL 1

#endif /* __ADLIST_H__ */
