#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "macro.h"

#ifndef BinTreeElemType
#define BinTreeElemType int
#endif

// link structure
typedef struct TNode {
    BinTreeElemType data;
    struct TNode *lchild, rchild;
} TNode, *BinTree;

// create bin-tree.
BinTree createEmptyBinTree(void);
BinTree consBinTree(TNode root, BinTree left, BinTree right);
int isNull(BinTree t);
TNode root(BinTree t);
TNode parent(BinTree t, TNode p);
BinTree leftChild(BinTree t, TNode p);
BinTree rightChild(BinTree t, TNode p);
Status insertElem(BinTree t, BinTreeElemType e);
Status deleteElem(BinTree t, BinTreeElemType e);

// traverse
// depth order
Status preOrder(BinTree t, visit_func func);
Status inOrder(BinTree t, visit_func func);
Status postOrder(BinTree t, visit_func func);

Status preOrder_Sq(BinTree t, visit_func func);
Status inOrder_Sq(BinTree t, visit_func func);
Status postOrder_sq(BinTree t, visit_func func);

// breadth order
Status levelOrder(BinTree t, visit_func func);

#endif