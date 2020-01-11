#include "sds.h"
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sdsalloc.h"

const char *SDS_NOINIT = "SDS_NOINIT";

// 获取sds结构体的大小
static inline int sdsHdrSize(char type) {
    switch (type & SDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return sizeof(struct sdshdr5);
        case SDS_TYPE_8:
            return sizeof(struct sdshdr8);
        case SDS_TYPE_16:
            return sizeof(struct sdshdr16);
        case SDS_TYPE_32:
            return sizeof(struct sdshdr32);
        case SDS_TYPE_64:
            return sizeof(struct sdshdr64);
    }

    return 0;
}

// 根据字符串长度提供合适的sds类型
static inline char sdsReqType(size_t string_size) {
    if (string_size < 1 << 5)
        return SDS_TYPE_5;
    if (string_size < 1 << 8)
        return SDS_TYPE_8;
    if (string_size < 1 << 16)
        return SDS_TYPE_16;
#if (LONG_MAX == LLONG_MAX)
    // 字面量 1 是int 左移超过位数会有编译警告信息
    if (string_size < 1ll << 32)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
#else
    return SDS_TYPE_32;
#endif
}

sds sdsnewlen(const void *init, size_t initlen) {
    /**
     * 1. 获取类型
     * 2. 获取类型结构的大小
     * 3. 分配空间
     * 4. 设置结构的属性
     * 5. 拷贝内容
     * 6. 设置结束符
     * */
    void *sh;  // 指向结构体的指针
    sds s;     // 指向结构体内容的指针
    char type = sdsReqType(initlen);
    if (type == SDS_TYPE_5 && initlen == 0) type = SDS_TYPE_8;
    int hdrlen = sdsHdrSize(type);
    unsigned char *fp;

    sh = s_malloc(hdrlen + initlen + 1);  //  结构大小 + 内容大小 + 结束符
    if (sh == NULL) return NULL;
    memset(sh, 0, hdrlen + initlen + 1);  // 初始化内存块

    if (init == SDS_NOINIT)
        init = NULL;

    s = (char *)sh + hdrlen;
    fp = ((unsigned char *)s) - 1;

    switch (type) {
        case SDS_TYPE_5: {
            *fp = type | (initlen << SDS_TYPE_BITS);
            break;
        }
        case SDS_TYPE_8: {
            SDS_HDR_VAR(8, s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
        case SDS_TYPE_16: {
            SDS_HDR_VAR(16, s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
        case SDS_TYPE_32: {
            SDS_HDR_VAR(32, s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
        case SDS_TYPE_64: {
            SDS_HDR_VAR(64, s);
            sh->len = initlen;
            sh->alloc = initlen;
            *fp = type;
            break;
        }
    }
    if (initlen && init)
        memcpy(s, init, initlen);
    s[initlen] = '\0';
    return s;
}

// 创建一个空的长度为0的sds
sds sdsempty(void) {
    return sdsnewlen("", 0);
}

sds sdsnew(const char *init) {
    size_t initlen = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, initlen);
}

// 拷贝构造
sds sdsdup(const sds s) {
    return sdsnewlen(s, sdslen(s));
}

// sds为空时，释放sds的空间
void sdsfree(sds s) {
    if (s == NULL) return;
    s_free((char *)s - sdsHdrSize(s[-1]));
}

// 更新sds的长度
void sdsupdatelen(sds s) {
    size_t reallen = strlen(s);
    sdssetlen(s, reallen);
}

// 清空sds的内容
void sdsclear(sds s) {
    sdssetlen(s, 0);
    s[0] = '\0';
}

/************************* 提供给用户的低级API *************************/

// 扩展sds的大小
sds sdsMakeRoomFor(sds s, size_t addlen)
{
    void *sh, *newsh;
    size_t avail = sdsavail(s);
    size_t len = sdslen(s), newlen;
    char type, oldtype = s[-1] & SDS_TYPE_MASK;
    size_t hdrlen;

    // 如果当前可用长度大于要添加的长度 可以直接使用
    if (avail >= addlen)
        return s;

    // 计算newsize
    hdrlen = sdsHdrSize(oldtype);
    newlen = len + addlen;
    if (newlen < SDS_MAX_PREALLOC)
        newlen *= 2;
    else
        newlen += SDS_MAX_PREALLOC;

    // 获取建议的长度
    type = sdsReqType(newlen);
    if (type == SDS_TYPE_5)
        type = SDS_TYPE_8;

    sh = (char *)s - hdrlen;
    hdrlen = sdsHdrSize(type);
    if (type == oldtype) {
        newsh = s_realloc(sh, hdrlen + newlen);
        if (newsh == NULL) return NULL;
        s = (char *)newsh + hdrlen;
    } else {
        newsh = s_malloc(hdrlen + newlen + 1);
        if (newsh == NULL) return NULL;
        memcpy((char *)newsh + hdrlen, s, len + 1);
        s_free(sh);
        s = (char *)newsh + hdrlen;
        s[-1] = type;
        sdssetlen(s, len);
    }
    sdssetalloc(s, newlen);
    return s;
}

// 删除sds多余的可用空间
sds sdsRemoveFreeSpace(sds s) {
    void *sh, *newsh;
    char type, oldtype = s[-1] & SDS_TYPE_MASK;
    int hdrlen, oldhdrlen = sdsHdrSize(oldtype);
    size_t len = sdslen(s);
    size_t avail = sdsavail(s);
    sh = (char *)s - oldhdrlen;

    // 如果没有可用空间了，直接返回
    if (avail == 0) return s;

    type = sdsReqType(len);
    hdrlen = sdsHdrSize(type);

    if (type == oldtype || type > SDS_TYPE_8) {
        newsh = s_realloc(sh, len + 1);
        if (newsh == NULL) return NULL;
        s = (char *)newsh + hdrlen;
    } else {
        newsh = s_malloc(hdrlen + len + 1);
        if (newsh == NULL) return NULL;
        memcpy((char *)newsh + hdrlen, s, len + 1);
        s_free(sh);
        s = (char *)newsh + hdrlen;
        s[-1] = type;
        sdssetlen(s, len);
    }

    sdssetalloc(s, len);
    return s;
}

/** 返回sds所使用的总内存
 * 包括：
 * 1 结构体大小
 * 2 字符串大小
 * 3 未使用的空间大小
 * 4 结束符
 * */
size_t sdsAllocSize(sds s) {
    size_t alloc = sdsalloc(s);
    return (alloc + sdsHdrSize(s[1]) + 1);
}

/**
 * 放回实际分配的指针
 * */
void *sdsAllocPtr(sds s) { return (void *)(s - sdsHdrSize(s[-1])); }

/**
 * 增加sds的长度并且删除结束符左侧多余的空间。通常会重新定位结束符的位置
 * 
 * 这个函数解决用户调用sdsMakeRoomFor()函数后字符串长度问题，在当前字符串后面添加一些内容，需要设置需的长度
 * 
 * 可以使用负增量
 * */
void sdsIncrLen(sds s, ssize_t incr) {

}

/*
sds sdsgrowzero(sds s, size_t len);

sds sdscatlen(sds s, const void *t, size_t len);

sds sdscat(sds s, cosnt char *t);

sds sdscatsds(sds s, const sds t);

sds sdscpylen(sds s, const char *t, size_t len);

sds sdscpy(sds s, const char *);

sds sdscatvprintf(sds s, const char *fmt, ...);

sds sdscatprintf(sds s, const char *fmt, ...);

sds sdscatfmt(sds s, char const *fmt, ...);

sds sdstrim(sds s, const char *cset);

void sdsrange(sds s, ssize_t start, ssize_t end);

int sdscmp(const sds s1, const sds s2);

sds *sdssplitlen(const char *s, ssize_t len, const char *sep, int seplen, int
*count);

void sdsgreesplitres(sds *tokens, int count);

void sdstolower(sds s);

void sdstoupper(sds s);

sds sdsfromlonglong(long long value);

sds sdscatrepr(sds s, const char *p, size_t len);

sds *sdssplitargs(const char *line, int *argc);

sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen);

sds sdsjoin(char **argv, int argc, char *sep);

sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen);

*/