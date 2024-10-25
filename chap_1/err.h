#include <stdarg.h>
#include <stdlib.h>

void err_doit(int8_t errnoflag, int level, const char *fmt, va_list ap );
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);

