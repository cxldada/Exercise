#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "macro.h"

// 最大值
#define INFINITY INT_MAX
// 最大顶点数
#define MAX_VERTEX_NUM 20

typedef enum {
    DG,  // 有向图
    DN,  // 有向网
    UDG, // 无向图
    UDN  // 无向网
} GraphKink;

/**
 * 邻接矩阵 
 * */

typedef int VertexType; // 无权图为 1或0   带权图为权值

typedef struct InfoType { // 弧的附加信息
    int value;
} InfoType;

typedef struct ArcCell {
    VertexType adj;
    InfoType *info;
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
    int vexs[MAX_VERTEX_NUM];
    AdjMatrix arcs;     // 领接矩阵
    int vexnum, arcnum; // 当前顶点数和弧数
    GraphKink kind;     // 种类标志
} MGraph;

Status CreateGraph(MGraph *graph);
Status CreateUDN(MGraph *graph);

/**
 * 邻接表
 * */

typedef struct ArcNode {
    int adjvex;
    struct ArcNode *nextarc;
    InfoType *info;
} ArcNode;

typedef struct VNode {
    VertexType data;
    ArcNode *firstarc;
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
    int kind;
} ALGraph;

/**
 * 十字链表
 * */

typedef struct ArcBox {
    int tailvex, headvex;
    struct ArcBox *hlink, *tlink;
    InfoType *info;
} ArcBox;

typedef struct VexNode {
    VertexType data;
    ArcBox *firstin, *firstout;
} VexNode;

typedef struct {
    VexNode xlist[MAX_VERTEX_NUM];
    int vexnum, arcnum;
} OLGraph;

#endif
