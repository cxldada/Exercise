/***
 * 功能描述：creat 权限 文件名
 * 可以同时设置用户权限、组权限和其他权限
 */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

void help();
mode_t parsedArgc(const char *who, const char *mode);

int main(int argc, char const *argv[])
{
    if(argc < 4)
    {
        help();
        return 0;
    }


    return 0;
}

void help()
{
    puts("usage: a.out [u,g,o,a] [r,w,x] filename");
    puts("");
    puts("u: user");
    puts("g: group");
    puts("o: other");
    puts("a: all");

    puts("");
    puts("r: read");
    puts("w: write");
    puts("x: exec");
}

mode_t parsedArgc(const char *who, const char *mode)
{
}