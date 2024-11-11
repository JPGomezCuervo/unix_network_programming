#include "unp.h"

/* src is void* because it has to handles IPv4 and IPv6 structures */
inline char *Inet_ntop(int af, const void *src, char *dst, socklen_t size)
{
        char *ptr;
        if (dst == NULL)
                error_quit("NULL 3rd argument to Inet_ntop");

        if ( (ptr = inet_ntop(af, src, dst, size)) == NULL)
                error_sys("inet_ntop error"); /* sets errno */

        return ptr;
}
