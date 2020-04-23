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

#endif