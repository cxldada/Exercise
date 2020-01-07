#ifndef __SDS_H
#defind __SDS_H

#define SDS_MAX_PREALLOC(1024 * 1024)
const char *SDS_NOINIT;

#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>

typedef char *sds;

/**
 * 永远不会使用sdshdr5，只是使用它的flags
 * flags第三位表示类型
 * 高5位表示长度
 * __attribute__((__packed__)) 紧凑模式，按字节数对齐
 * */
struct __attribute__((__packed__)) sdshdr5 {
    unsigned char flags;
    char buf[];
};
struct __attribute__((__packed__)) sdshdr8 {
    uint8_t len;
    uint8_t alloc;
    unsigned char flags;
    char buf[];
};
struct __attribute__((__packed__)) sdshdr16 {
    uint16_t len;
    uint16_t alloc;
    unsigned char flags;
    char buf[];
};
struct __attribute__((__packed__)) sdshdr32 {
    uint32_t len;
    uint32_t alloc;
    unsigned char flags;
    char buf[];
};
struct __attribute__((__packed__)) sdshdr64 {
    uint64_t len;
    uint64_t alloc;
    unsigned char flags;
    char buf[];
};

#define SDS_TYPE_5 0
#define SDS_TYPE_8 1
#define SDS_TYPE_16 2
#define SDS_TYPE_32 3
#define SDS_TYPE_64 4

// 只取低三位
#define SDS_TYPE_MASK 7
// 表示sds类型的位数
#define SDS_TYPE_BITS 3

// 定义指向sds结构头的变量
#define SDS_HDR_VAR(T, s) struct sdshdr##T *sh = (void *)((s) - (sizeof(struct sdshdr##T)))
// 将变量s指向结构的初始位置
#define SDS_HDR(T, s) ((struct sdshdr##T *)((s) - (sizeof(struct sdshdr##T))))

// ? OMG
#define SDS_TYPE_5_LEN(f) ((f) >> SDS_TYPE_BITS)

// 获取sds的长度
static inline size_t sdslen(const sds s) {
    unsigned char flags = s[-1];
    switch (flags & SDS_TYEPS_MASK) {
        case SDS_TYPE_5:
            return SDS_TYPE_5_LEN(flags);
        case SDS_TYPE_8:
            return SDS_HDR(8, s)->len;
        case SDS_TYPE_16:
            return SDS_HDR(16, s)->len;
        case SDS_TYPE_32:
            return SDS_HDR(32, s)->len;
        case SDS_TYPE_64:
            return SDS_HDR(64, s)->len;
    }

    return 0;
}

// 获取sds的可用空间
static inline size_t sdsavail(const sds s) {
    unsigned char flags = s[-1];
    switch (flags & SDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return 0;
        case SDS_TYPE_8:
            SDS_HDR_VAR(8, s);
            return sh->alloc - sh->len;
        case SDS_TYPE_16:
            SDS_HDR_VAR(16, s);
            return sh->alloc - sh->len;
        case SDS_TYPE_32:
            SDS_HDR_VAR(32, s);
            return sh->alloc - sh->len;
        case SDS_TYPE_64:
            SDS_HDR_VAR(64, s);
            return sh->alloc - sh->len;
    }

    return 0;
}

// 设置sds的长度
static inline void sdssetlen(sds s, size_t newlen) {
    unsigned char flags = s[-1];
    switch (flags & SDS_TYPE_MASK) {
        case SDS_TYPE_5: {
            unsigned char *fp = ((unsigned char *)s) - 1;
            *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
        } break;
        case SDS_TYPE_8:
            SDS_HDR(8, s)->len = newlen;
            break;
        case SDS_TYPE_16:
            SDS_HDR(16, s)->len = newlen;
            break;
        case SDS_TYPE_32:
            SDS_HDR(32, s)->len = newlen;
            break;
        case SDS_TYPE_64:
            SDS_HDR(64, s)->len = newlen;
            break;
    }
}

// 增加sds的长度
static inline void sdsinclen(sds s, size_t inc) {
    unsigned char *flags = s[-1];
    switch (flags & SDS_TYPE_MASK) {
        case SDS_TYPE_5: {
            unsigned char *fp = ((unsigned char *)s) - 1;
            size_t newlen = SDS_TYPE_5_LEN(flags) + inc;
            *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
        } break;
        case SDS_TYPE_8:
            SDS_HDR(8, s)->len += inc;
            break;
        case SDS_TYPE_16:
            SDS_HDR(16, s)->len += inc;
            break;
        case SDS_TYPE_32:
            SDS_HDR(32, s)->len += inc;
            break;
        case SDS_TYPE_64:
            SDS_HDR(64, s)->len += inc;
            break;
    }
}

/**
 * 获取sds的分配的空间大小
 * 满足 sdsalloc() = sdsavail() + sdslen()
 * */
static inline size_t sdsalloc(const sds s) {
    unsigned char *flags = s[-1];
    switch (flags & SDS_TYPE_MASK) {
        case SDS_TYPE_5:
            return SDS_TYPE_5_LEN(flags);
            break;
        case SDS_TYPE_8:
            return SDS_HDR(8, s)->alloc;
            break;
        case SDS_TYPE_16:
            return SDS_HDR(16, s)->alloc;
            break;
        case SDS_TYPE_32:
            return SDS_HDR(32, s)->alloc;
            break;
        case SDS_TYPE_64:
            return SDS_HDR(64, s)->alloc;
            break;
    }

    return 0;
}

// 设置sds的分配空间大小
// sdshdr5 是无效的
static inline void sdssetalloc(sds s, size_t newlen) {
    unsigned char *flags = s[-1];
    switch (flags & SDS_TYPE_MASK) {
        case SDS_TYPE_5:
            // 这个结构不存在分配空间信息
            break;
        case SDS_TYPE_8:
            return SDS_HDR(8, s)->alloc = newlen;
            break;
        case SDS_TYPE_16:
            return SDS_HDR(16, s)->alloc = newlen;
            break;
        case SDS_TYPE_32:
            return SDS_HDR(32, s)->alloc = newlen;
            break;
        case SDS_TYPE_64:
            return SDS_HDR(64, s)->alloc = newlen;
            break;
    }
}

sds sdsnewlen(const void *init, size_t inilen);
sds sdsnew(const char *init);
sds sdsempty(void);
sds sdsdup(const sds s);
void sdsfree(sds s);
sds sdsgrowzero(sds s, size_t len);
sds sdscatlen(sds s, const void *t, size_t len);
sds sdscat(sds s, cosnt char *t);
sds sdscatsds(sds s, const sds t);
sds sdscpylen(sds s, const char *t, size_t len);
sds sdscpy(sds s, const char *);

sds sdscatvprintf(sds s, const char *fmt, ...);
/**
 * __GNUC__ 表示 gcc编译器的主版本号
 * __GNUC_MINOR__ 表示gcc编译器的副版本号
 * __GNUC_PATCHLEVEL__ 表示gcc编译器的修正版本号
 * 
 * __attribute__((format(printf, 2, 3))) 
 * 原型: format(archetype,string-index,first-to-check)
 * 参数: archetype 指定风格
 *       string-index 指定传入函数的第几个参数是格式化字符串
 *       first-to-check 指定从函数的第几个参数开始按上述规则进行检查
 * format属性告诉编译器，按照printf, scanf等标准C函数参数格式规则对该函数的参数进行检查
 * 
 * 
 * */
#ifdef __GNUC__
sds sdscatprintf(sds s, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
#else
sds sdscatprintf(sds s, const char *fmt, ...);
#endif

sds sdscatfmt(sds s, char const *fmt, ...);
sds sdstrim(sds s, const char *cset);
// ssize_t 指 有符号int
void sdsrange(sds s, ssize_t start, ssize_t end);
void sdsupdatelen(sds s);
void csdsclear(sds s);
int sdscmp(const sds s1, const sds s2);
sds *sdssplitlen(const char *s, ssize_t len, const char *sep, int seplen, int *count);
void sdsgreesplitres(sds *tokens, int count);
void sdstolower(sds s);
void sdstoupper(sds s);
sds sdsfromlonglong(long long value);
sds sdscatrepr(sds s, const char *p, size_t len);
sds *sdssplitargs(const char *line, int *argc);
sds sdsmapchars(sds s, const char *from, const char *to, size_t setlen);
sds sdsjoin(char **argv, int argc, char *sep);
sds sdsjoinsds(sds *argv, int argc, const char *sep, size_t seplen);

// 提供给用户的低级API
sds sdsMakeRoomFor(sds s, size_t addlen);
void sdsIncrLen(sds s, ssize_t incr);
sds sdsRemoveFreeSpace(sds s);
size_t sdsAllocSize(sds s);
void *sdsAllocPtr(sds s);

#endif