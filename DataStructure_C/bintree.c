#include "bintree.h"

#define StackElemType (TNode *)
#include "stack.h"

#define QueueElemType (TNode *)
#include "queue.h"

// create bin-tree.
BinTree createEmptyBinTree(void) {
    TNode *pRoot = malloc(sizoef(TNode));
    if(!pRoot)
        return OVERFLOW;
    
    pRoot->data = 0;
    pRoot->lchild = pRoot->rchild = NULL;
    return pRoot;
}

BinTree consBinTree(TNode root, BinTree left, BinTree right) {
    BinTree ret = createEmptyBinTree(void);
    ret->data = root.data;
    ret->lchild = left;
    ret->rchild = right;
    return ret;
}

int isNull(BinTree t);

TNode root(BinTree t);

TNode parent(BinTree t, TNode p);

BinTree leftChild(BinTree t, TNode p);

BinTree rightChild(BinTree t, TNode p);

Status insertElem(BinTree t, BinTreeElemType e);

Status deleteElem(BinTree t, BinTreeElemType e);

int visit(BinTreeElemType e) {
    printf("%d ", e);
    return OK;
}

// traverse
// depth-first
Status preOrder(BinTree t, visit_func func) {
    if(!t)
        return OK;

    if(func)
        func(t->data);
    preOrder(t->lchild, func);
    preOrder(t->rchild, func);

    return OK;
}

Status inOrder(BinTree t, visit_func func) {
    if(!t)
        return OK;

    preOrder(t->lchild, func);
    if (func)
        func(t->data);
    preOrder(t->rchild, func);

    return OK;
}

Status postOrder(BinTree t, visit_func func) {
    if(!t)
        return OK;
    
    preOrder(t->lchild, func);
    preOrder(t->rchild, func);
    if (func)
        func(t->data);

    return OK;
}

Status preOrder_Sq(BinTree t, visit_func func) {
    SqStack stack;
    InitStack(&stack);
    Push(&stack, t);

    while (!StackEmpty(&stack)) {
        TNode *pRoot = NULL;
        while (pRoot = GetTop(&stack) && pRoot) {
            func(pRoot->data);
            Push(&stack, pRoot->lchild);
        }
        Pop(&stack, pRoot);
        if (!StackEmpty(&stack)) {
            Pop(&stack, pRoot);

            if (pRoot)
                Push(&stack, pRoot->rchild);
        }
    }

    return OK;
}

Status inOrder_Sq(BinTree t, visit_func func) {
    SqStack stack;
    TNode *p = t;

    while (p || StackEmpty(&stack)) {
        if (p) {
            Push(&stack, p);
            p = p->lchild;
        } else {
            Pop(&stack, p);
            func(p->data);
            p = p->rchild;
        }
    }

    return OK;
}

Status postOrder_sq(BinTree t, visit_func func) {
    SqStack stack;
    TNode *p = t;

    while (p || StackEmpty(&stack)) {
        if (p) {
            func(p->data);
            Push(&stack, p);
            p = p->lchild;
        } else {
            Pop(&stack, p);
            p = p->rchild;
        }
    }

    return OK;
}

// breadth-first
Status levelOrder(BinTree t, visit_func func) {
    LinkQueue queue;
    InitQueue_LQ(&queue);

    EnQueue_LQ(&queue, t);
    while (!QueueEmpty_LQ(queue)) {
        QueueElemType p;
        DeQueue_LQ(&queue, p);
        if(p)
            func(p->data);

        EnQueue_LQ(&queue, p->lchild);
        EnQueue_LQ(&queue, p->rchild);
    }

    return Ok;
}