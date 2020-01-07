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
    if (string_size < 1 << 32)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
#else
    return SDS_TYPE_32;
#endif
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

sds sdscatprintf(sds s, const char *fmt, ...);

sds sdscatfmt(sds s, char const *fmt, ...);

sds sdstrim(sds s, const char *cset);

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