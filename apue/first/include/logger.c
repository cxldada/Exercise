#ifndef LOGGER_H
#define LOGGER_H

#include "apue.h"
#include <errno.h>
#include <stdarg.h>
#include <syslog.h>

static void log_doit(int, int, int, const char *, va_list ap);

// 调用者必须定义并且设置：非0的情况
extern int log_to_stderr;

// 初始化 syslog()
void log_open(const char *ident, int option, int facility)
{
    if (log_to_stderr == 0)
        openlog(ident, option, facility);
}

// 非重大错误
// 打印系统错误值和信息并返回
void log_ret(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
}

// 重大错误，调用系统函数
// 打印信息并终止
void log_sys(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, errno, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

// 非重大错误，不调用系统函数
// 打印信息并返回
void log_msg(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
}

// 非重大错误，不调用系统函数
// 打印信息并终止
void log_quit(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(0, 0, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

// 重大错误，调用系统函数
// 打印传过来的错误码参数和信息，并终止
void log_exit(int error, const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_doit(1, error, LOG_ERR, fmt, ap);
    va_end(ap);
    exit(2);
}

// 打印信息并返回调用者
static void log_doit(int errnoflog, int error, int priority, const char *fmt,va_list ap)
{
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflog)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));

    strcat(buf, "\n");
    if (log_to_stderr)
    {
        fflush(stdout);
        fputs(buf, stderr);
        fflush(stderr);
    }
    else
    {
        syslog(priority, "%s", buf);
    }
}

#endif