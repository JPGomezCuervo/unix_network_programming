#include "../include/unp.h"

/* standard error functions
 
 * Function     |       strerror (errno)        |       terminate       |      syslog level
 * err_dump     |               yes             |       abort           |       LOG_ERR
 * err_msg      |               no              |       return          |       LOG_INFO
 * err_quit     |               no              |       exit(1)         |       LOG_ERR
 * err_ret      |               yes             |       return          |       LOG_INFO
 * err_sys      |               yes             |       exit(1)         |       LOG_ERR
 
 */

// erronoflag -> 1 prints errno | 0 doesn't print errno
void err_doit(int8_t errnoflag, int level, const char *fmt, va_list ap )
{
        char buf[1024];
        vsnprintf(buf, sizeof(buf),fmt, ap);

        if (errnoflag)
                snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), ": %s", strerror(errno));

        syslog(level, "%s\n", buf);
        fprintf(stderr, "%s\n", buf);
}

void err_sys(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        err_doit(1, LOG_ERR, fmt, ap);
        va_end(ap);
        exit(1);
}

void err_ret(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        err_doit(1, LOG_INFO, fmt, ap);
        va_end(ap);
        return;
}

void err_dump(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        err_doit(1, LOG_ERR, fmt, ap);
        va_end(ap);
        abort();
        exit(1);
}

void err_msg(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        err_doit(0, LOG_INFO, fmt, ap);
        va_end(ap);
        return;
}

void err_quit(const char *fmt, ...)
{
        va_list ap;
        va_start(ap, fmt);
        err_doit(0, LOG_ERR, fmt, ap);
        va_end(ap);
        exit(1);
}
