#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

bool isAll = false;         // 全部显示(包括隐藏文件)
bool isPerticular = false;  // 显示详细信息

// 处理参数
void handlerArgs(char *args[], unsigned size) {
    if (args == NULL)
        return;

    for (unsigned args_index = 0; args_index < size; ++args_index) {

        char *arg = args[args_index];
        if (arg == NULL)
            continue;
        size_t arg_len = strlen(arg);
        if (arg_len <= 0 || arg[0] != '-')
            break;

        for (unsigned i = 1; i < arg_len; ++i) {
            switch (arg[i]) {
                case 'a': {
                    isAll = true;
                } break;
                case 'l': {
                    isPerticular = true;
                } break;
                default:
                    break;
            }

        }

    }
}

int printTypeAndAccessString(struct stat *file_stat) {
    char res[10];

    if (S_ISDIR(file_stat->st_mode))
        res[0] = 'd';
    else if (S_ISLNK(file_stat->st_mode))
        res[0] = 'l';
    else if (S_ISBLK(file_stat->st_mode))
        res[0] = 'b';
    else if (S_ISSOCK(file_stat->st_mode))
        res[0] = 's';
    else if (S_ISFIFO(file_stat->st_mode))
        res[0] = 'f';
    else
        res[0] = '-';

    if (file_stat->st_mode & S_IRUSR) {
        res[1] = 'r';
    } else {
        res[1] = '-';
    }

    if (file_stat->st_mode & S_IWUSR) {
        res[2] = 'w';
    } else {
        res[2] = '-';
    }

    if (file_stat->st_mode & S_IXUSR) {
        res[3] = 'x';
    } else {
        res[3] = '-';
    }

    if (file_stat->st_mode & S_IRGRP) {
        res[4] = 'r';
    } else {
        res[4] = '-';
    }

    if (file_stat->st_mode & S_IWGRP) {
        res[5] = 'w';
    } else {
        res[5] = '-';
    }

    if (file_stat->st_mode & S_IXGRP) {
        res[6] = 'x';
    } else {
        res[6] = '-';
    }

    if (file_stat->st_mode & S_IROTH) {
        res[7] = 'r';
    } else {
        res[7] = '-';
    }

    if (file_stat->st_mode & S_IWOTH) {
        res[8] = 'w';
    } else {
        res[8] = '-';
    }

    if (file_stat->st_mode & S_IXOTH) {
        res[9] = 'x';
    } else {
        res[9] = '-';
    }

    printf("%10s ", res);
    return 0;
}

void showDir(char *dir) {
}

void showFile(char *file, struct stat *file_stat) {
    if (!isPerticular) {
        printf("%1s ", file);
        return;
    }

    if (printTypeAndAccessString(file_stat) != 0) {
        printf("%s: can't get file mode\n\n", file);
        return;
    }

    printf("%2d ", file_stat->st_nlink);
    struct passwd *uinfo;
    struct group *ginfo;

    if((uinfo = getpwuid(file_stat->st_uid)) != NULL)  {
        printf("%2s ", uinfo->pw_name);
    }

    if((ginfo = getgrgid(file_stat->st_gid)) != NULL) {
        printf("%2s ",ginfo->gr_name);
    }

    printf("%2lld ", file_stat->st_size);
    struct tm *accesstime;
    if ((accesstime = localtime(&file_stat->st_atime)) != NULL) {
      printf("%2d %2d %02d:%02d ", accesstime->tm_mon + 1, accesstime->tm_mday,
             accesstime->tm_hour, accesstime->tm_min);
    }

    printf("%2s ", file);
}

void handlerDirs(char *dirs[], unsigned size) {
    if (dirs == NULL)
        return;

    for (unsigned dir_index = 0; dir_index < size; ++dir_index) {
        char *dir = dirs[dir_index];
        if (dir == NULL)
            return;
        struct stat file_stat;
        if (lstat(dir, &file_stat) != 0) {
            printf("%s: no such file or directory\n\n", dir);
            break;
        }

        if (S_ISDIR(file_stat.st_mode)) {  // 是目录
            showDir(dir);
            break;
        }

        showFile(dir, &file_stat);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: mls [-a | -l] <dir>\n");
        exit(0);
    }
    const unsigned arr_size = argc - 1;

    char *dirs[arr_size];
    char *args[arr_size];
    int dirsz = 0;
    int argsz = 0;

    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            args[argsz++] = argv[i];
        } else {
            dirs[dirsz++] = argv[i];
        }
    }

    handlerArgs(args, arr_size);
    handlerDirs(dirs, arr_size);

    exit(0);
}
