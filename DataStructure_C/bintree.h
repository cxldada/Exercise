#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "macro.h"

// link structure
typedef struct TNode {
    ElemType data;
    struct TNode *left;
    struct TNode *right;
} TNode, *BinTree;

// create bin-tree.
BinTree createEmptyBinTree(void);
BinTree consBinTree(TNode root, BinTree left, BinTree right);
int isNull(BinTree t);
TNode root(BinTree t);
TNode parent(BinTree t, TNode p);
BinTree leftChild(BinTree t, TNode p);
BinTree rightChild(BinTree t, TNode p);
Status insertElem(BinTree t, ElemType e);
Status deleteElem(BinTree t, ElemType e);

// traverse
// depth order
void preOrder(BinTree t);
void inOrder(BinTree t);
void postOrder(BinTree t);

// breadth order
void levelOrder(BinTree t);

#endif