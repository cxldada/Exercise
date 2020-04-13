#include "bintree.h"

// create bin-tree.
BinTree createEmptyBinTree(void) {
    TNode *pRoot = malloc(sizoef(TNode));
    if(!pRoot)
        return OVERFLOW;
    
    pRoot->data = 0;
    pRoot->left = pRoot->right = NULL;
    return pRoot;
}

BinTree consBinTree(TNode root, BinTree left, BinTree right) {
    BinTree ret = createEmptyBinTree(void);
    ret->data = root.data;
    ret->left = left;
    ret->right = right;
    return ret;
}

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