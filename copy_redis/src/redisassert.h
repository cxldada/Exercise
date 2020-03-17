#ifndef __REDIS_ASSERT_H__
#define __REDIS_ASSERT_H__

#include <unistd.h> /* for _exit() */

#define assert(_e) ((_e) ? (void)0 : (_serverAssert(#_e, __FILE__, __LINE__), _exit(1)))
#define panic(...) _serverPanic(__FILE__, __LINE__, __VA_ARGS__), _exit(1)

void _serverAssert(char *estr, char *file, int line);
void _serverPanic(const char *file, int line, const char *msg, ...);

#endif
