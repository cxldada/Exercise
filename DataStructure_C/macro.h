#ifndef __MACRO_H__
#define __MACRO_H__

#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define Status int

#define ElemType int

typedef int (*compare_func)(ElemType l,ElemType  r);
typedef void (*visit_func)(ElemType e);

// sequence macro
#define _SQ_MAXSIZE_ 100

// link list macro
#define _LL_ELEM_TYPE_ int

#endif