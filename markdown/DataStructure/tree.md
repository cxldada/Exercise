[TOC]

## 树形结构

> 树是以分支关系定义的层次结构
>
> 在树形结构中每个结点最多只有一个前驱，但可以有多个后继。

### 树的基本术语

* 结点的度：结点的非空子树的个数叫做结点的度
* 分支结点：度不为0的结点，也称为非终端结点或内部结点
* 叶子结点：度为0的结点，也称为终端结点
* 树的高度：树的最大层数称为二叉树的高度
* 叶子结点：左右子树都为空的结点
* 满二叉树：如果一棵二叉树的除了叶子结点以外的所有结点，它们的左右子树非空，则此二叉树称为满二叉树
* 完全二叉树：如果一棵二叉树中，只有最下面的两层结点读书小于2，其余各层结点度数都等于2，并且最下面一层的结点都集中在该层最左边的若干位置上，则此二叉树称为完全二叉树

### 树的抽象数据类型

```c
ADT Tree{
   Data:
    具有相同性质的数据元素的集合
   operate:
    InitTree(&T);
    DestroyTree(&T);
    CreateTree(&T,definition);
    ClearTree(&T);
    TreeEmpty(T);
    TreeDepth(T);
    Root(T);
    Value(T,cur_e);
    Assign(T,cur_e,value);
    Parent(T,cur_t);
    LeftChild(T,cur_e);
    RightChild(T,cur_t);
    InsertChild(&T,&p,i,c);//插入c为T中p所指节点的第i棵子树
    DeleteChild(&T,&p,i);// 删除T中p所指结点的第i棵子树
    TraverseTree(T,visit());
}
```

### 二叉树

> 每个结点最多只有两个子结点的特殊属性结构，且两个子结点有左右之分，其次序不能任意颠倒

#### 二叉树的主要性质

1. 在非空二叉树的`i`层上，最多有$$ 2^i $$个结点$$(i \geq 0)$$
2. 高度为`k`的二叉树中，最多有$$ 2 ^ {k + 1} - 1$$个结点$$(k \geq 0)$$ (根节点的在第0层)
3. 对于任何一棵非空的二叉树，如果叶结点个数为$$n_0$$，度数为2的结点个数为$$n_2$$，则有$$n_0 = n_2 + 1$$
4. 一棵深度为`k`其有$$ 2^k-1$$个结点的二叉树称为满二叉树
5. 具有`n`个节点的完全二叉树的高度`k`为$$ log_2n + 1$$
6. 对于具有`n`个结点的完全二叉树，如果按照从第一层到最后一层，每层按照从左到右的顺序对二叉树中的所有结点从`1`到`n `进行编号，则对于任意的下标为`i`的结点有：
   1. 如果`i = 0`，则它是根节点，他没有父节点，如果是`i >0`，则它的父节点的下标为$$ (i - 1) / 2 $$
   2. 如果$$ 2i \leq n - 1 $$，则下标为`i`的结点的左子节点的下标为$$ 2i $$，否则下标为`i`的结点没有左子节点
   3. 如果$$ 2i + 1 \le n - 1 $$，则下标为`i`的结点的左子节点的下标为$$ 2i + 1$$，否则下标为`i`的结点没有左子节点
7. 在满二叉树中，叶结点的个数比分支结点的个数多`1`。
8. 在扩充二叉树中，外部结点的个数比内部结点的个数多`1`。
9. 对任意扩充二叉树，外部路径长度`E`和内部路径长度`I`之间满足$$ E = I + 2n $$，其中`n`是内部结点的个数

#### 二叉树的抽象数据类型

```c
ADT BinaryTree {
    Data:
    	具有相同特性的数据元素的集合;
    operate:
    	InitBiTree(&T);
    	DestroyBiTree(&T);
    	CreateBiTree(&T,definition);
    	ClearBiTree(&T);
    	BiTreeEmpty(T);
    	BiTreeDepth(T);
    	Root(T);
    	Value(T,e);
    	Assign(T,&e,value);
    	Parent(T,e);
    	LeftChild(T,e);
    	RightChild(T,e);
    	LeftSibling(T,e);
    	RightSibling(T,e);
    	InsertChild(T,p,LR,c);
    	DeleteChild(T,p,LR);
    	PreOrderTraverse(T,Visit());
    	InOrderTraverse(T,Visit());
    	PostOrderTraverse(T,Visit());
    	LevelOrderTraverse(T,Visit());
}
```

#### 二叉树的顺序存储结构

```c
#define MAX_SIZE 100 // 最大结点数
typedef TElemType SqBiTree[MAX_SIZE]; // 0号单元存储根节点
```

> 使用顺序存储结构时：
>
> 1. 用一组地址连续的存储单元依次自上而下、自左至右存储完全二叉树上的结点元素
> 2. 不存在的结点用0表示
> 3. 这种结构只适用于完全二叉树
> 4. 最最坏的情况下，一个深度为k且只有k个结点的单支树中，需要$$ 2^k -1$$个存储单元

#### 二叉树的链式存储结构

```c
typedef struct BiTNode {
    TElemType data;
    struct BiTNode *lchild,*rchild;
    struct BiTNode *parent; // 有些结构中会有双亲指针域
}BiTNode,*BiTree;
```

