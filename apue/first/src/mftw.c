#include "../include/apue.h"
#include <dirent.h>
#include <limits.h>

// 定义遍历文件名的函数指针
typedef int Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main(int argc, char *argv[])
{
    int ret;
    if (argc != 2)
        err_quit("usage: ftw <starting-pathname>");

    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nchr + nfifo + nslink + nsock;
    if (ntot == 0)
        ntot = 1;

    printf("regular files = %ld, %5.2f %%\n", nreg, nreg * 100.0 / ntot);
    printf("directories files = %ld, %5.2f %%\n", ndir, ndir * 100.0 / ntot);
    printf("block files = %ld, %5.2f %%\n", nblk, nblk * 100.0 / ntot);
    printf("char files = %ld, %5.2f %%\n", nchr, nchr * 100.0 / ntot);
    printf("FIFOs files = %ld, %5.2f %%\n", nfifo, nfifo * 100.0 / ntot);
    printf("symbolic links = %ld, %5.2f %%\n", nslink, nslink * 100.0 / ntot);
    printf("sockets = %ld, %5.2f %%\n", nsock, nsock * 100.0 / ntot);

    exit(ret);
}

// 目录以外的文件类型
#define FTW_F 1
// 文件类型是目录
#define FTW_D 2
// 不能读取目录
#define FTW_DNR 3
// 不能获取文件的stat
#define FTW_NS 4

static char *fullpath; // 完整路径
static size_t pathlen; // 路径长度

static int myftw(char *pathname, Myfunc *func)
{
    fullpath = path_alloc(&pathlen);

    if (pathlen < strlen(pathname))
    {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }

    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath(Myfunc *func)
{
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;
    if (lstat(fullpath, &statbuf) < 0)
        return (func(fullpath, &statbuf, FTW_NS));
    if (S_ISDIR(statbuf.st_mode) == 0)
        return (func(fullpath, &statbuf, FTW_F));

    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
        return ret;

    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen)
    {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            err_sys("realloc failed");
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dp = opendir(fullpath)) == NULL)
        return (func(fullpath, &statbuf, FTW_DNR));

    while ((dirp = readdir(dp)) != NULL)
    {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0)
            break;
    }
    fullpath[n - 1] = 0;
    if (closedir(dp) < 0)
        err_ret("can't close directory %s", fullpath);
    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type)
    {
    case FTW_F:
    {
        switch (statptr->st_mode & S_IFMT)
        {
        case S_IFREG:
            nreg++;
            break;
        case S_IFBLK:
            nblk++;
            break;
        case S_IFCHR:
            nchr++;
            break;
        case S_IFIFO:
            nfifo++;
            break;
        case S_IFLNK:
            nslink++;
            break;
        case S_IFSOCK:
            nsock++;
            break;
        case S_IFDIR:
            err_dump("for S_IFDIR for %s", pathname);
        }
    }
    break;
    case FTW_D:
        ndir++;
        break;
    case FTW_DNR:
        err_ret("can't read directory %s", pathname);
        break;
    case FTW_NS:
        err_ret("stat error for %s", pathname);
        break;
    default:
        err_dump("unknow type %d for pathname %s", type, pathname);
    }
    return 0;
}