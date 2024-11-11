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
