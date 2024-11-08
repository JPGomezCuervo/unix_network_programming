#include "unp.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t addrlen)
{
        char portstr[8];
        static char str[128]; /* this static to avoid allocation, just educational */
        int n;

        switch (sa->sa_family) {
        case AF_INET:
                struct sockaddr_in *sin; 

                sin = (struct sockaddr_in *) sa;

                if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
                      return NULL;
                /* we compare nthos to zero because in network
                * programming zero in sin_port means that the OS
                * haven't assign a port to the socket. Then it's
                * an error*/
                if ( (n = ntohs(sin->sin_port)) != 0) 
                {
                        snprintf(portstr, sizeof(portstr), ":%d", n);
                        strncat(str, portstr, strlen(portstr));
                }
                return str;

        case AF_INET6: 
                struct sockaddr_in6 *sin6;

                sin6 = (struct sockaddr_in6 *) sa;

                if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
                        return NULL;

                if ( (n = ntohs(sin6->sin6_port)) != 0)
                {
                        snprintf(portstr, sizeof(portstr), ":%d", n);
                        strncat(str, portstr, strlen(portstr));
                }
                return str;
                               
        default:
                snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d", 
                                sa->sa_family, addrlen);
                return str;
        }
        return NULL;
}

int sock_pton_loose(int af, const char *src, void *dst)
{
        int n;

        switch(af) {
        case AF_INET:
                if ( (n = inet_pton(af, src, dst)) <= 0)
                        if (n == 0)
                                n = inet_aton(src, (struct in_addr *)dst);
                break;

        case AF_INET6:
                if ( (n = inet_pton(af, src, dst)) <= 0) 
                        if (n == 0)
                                n = inet_aton(src, (struct in_addr *)dst);
                break;

        default:
                err_sys("sock_pton_loose error: unknown AF_xxx: %d", af);
        }
        return n;
}

int Sock_pton_loose(int af, const char *src, void *dst)
{
        int n;
        if ( (n = sock_pton_loose(af, src, dst)) < 0)
                err_sys("sock_pton_loose error");

        return n;
}

char *Sock_ntop(const struct sockaddr *sa, socklen_t addrlen)
{
        char *ptr;
        if ( (ptr = sock_ntop(sa, addrlen)) == NULL)
                err_sys("inet_ntop error"); // inet_ntop sets errno

        return ptr;
}
