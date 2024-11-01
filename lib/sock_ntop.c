#include "../include/unp.h"

char *sock_ntop(const struct sockaddr *sa, socklen_t addrlen)
{
        char portstr[8];
        static char str[128]; /* this static to avoid allocation, just educational */

        switch (sa->sa_family) {

                case AF_INET: {
                                      int n;
                                      struct sockaddr_in *sin = (struct sockaddr_in *) sa;
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
                        }

                case AF_INET6: {
                                       int n;
                                       struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *) sa;

                                       if (inet_ntop(AF_INET6, &sin6->sin6_addr, str, sizeof(str)) == NULL)
                                               return NULL;

                                       if ( (n = ntohs(sin6->sin6_port)) != 0)
                                       {
                                               snprintf(portstr, sizeof(portstr), ":%d", n);
                                              strncat(str, portstr, strlen(portstr));
                                       }
                                       return str;
                               }
                default:
                               snprintf(str, sizeof(str), "sock_ntop: unknown AF_xxx: %d, len %d", 
                                               sa->sa_family, addrlen);
        }
        return NULL;
}

char *Sock_ntop(const struct sockaddr *sa, socklen_t addrlen)
{
        char *ptr;
        if ( (ptr = sock_ntop(sa, addrlen)) == NULL)
                err_sys("inet_ntop"); // inet_ntop sets errno

        return ptr;
}
