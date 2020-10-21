#include "common.h"
#include <stdio.h>
#include <stdlib.h>

// 非零个数的最大值
#define MAXSIZE 12500

typedef struct {
  int i,j; // 非零的行下标和列下标
  ElemType e;
}Triple;

typedef struct {
  Triple data[MAXSIZE + 1]; // 非零三元组表，data[0]未使用
  int mu,nu,tu; // 矩阵的行数、列数和非零元素的个数
}TSMatrix;

Status TransposeSMatrix(TSMatrix M,TSMatrix *T) {
  // 采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
  T->mu = M.mu;
  T->nu = M.nu;
  T->tu = M.tu;
  if(T->tu) {
      int q = 1;
      for (int col = 1; col < M.mu; ++col) {
          for (int p = 1; p < M.tu; ++p) {
            if(M.data[p].j == col) {
                T->data[q].i = M.data[p].j;
                T->data[q].j = M.data[p].i;
                T->data[q].e = M.data[p].e;
                ++q;
            }
          }
      }
  }
  return OK;
}
