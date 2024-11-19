#include "unp.h"

/* src is void* because it has to handles IPv4 and IPv6 structures */
inline const char *Inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
        const char *ptr;
        if (dst == NULL)
                err_quit("NULL 3rd argument to Inet_ntop");

        if ( (ptr = inet_ntop(af, src, dst, size)) == NULL)
                err_sys("inet_ntop error"); /* sets errno */

        return ptr;
}

inline void Inet_pton(int af, const char *pstr, void *dst)
{
        int n;

        if ( (n = inet_pton(af, pstr, dst)) < 0)
                err_sys("inet_pton error for %s\n", pstr);
        else if (n == 0)
                err_quit("inet_pton error for %s\n", pstr);
}

char *Fgets(char *buff, int size, FILE *stream)
{
        char *s;

        if ( (s = fgets(buff, size, stream)) == NULL)
                err_quit("fgets error");

        return s;
}

int Fputs(char *s, FILE *stream)
{
        int n;
        if ( (n = fputs(s, stream)) < 0)
                err_quit("fputs error");

        return n;
}
