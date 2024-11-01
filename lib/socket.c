#include "../include/unp.h"

inline int Socket(int domain, int type, int protocol)
{
        int n;
        if ( (n = socket(domain, type, protocol)) < 0 )
                err_sys("socket error");

        return n;
}

inline int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
        int n;
        if ( (n = bind(sockfd, addr, addrlen)) < 0)
                err_sys("bind error");

        return n;
}

inline int Listen(int sockfd, int backlog)
{
        int n;

        if ( (n = listen(sockfd, backlog)) < 0)
                err_sys("listen error");

        return n;
}

inline int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
        int n;

        if ( (n = connect(sockfd, addr, addrlen)) < 0)
                err_sys("connect error");

        return n;
}

inline int Accept(int sockfd, struct sockaddr *addr, socklen_t *addr_len)
{
        int n;

        if ( (n = accept(sockfd, addr, addr_len)) < 0)
                err_sys("accept error");

        return n;
}

inline size_t Write(int fd, const void *buf, size_t count)
{
        size_t n;

        if ( (n = write(fd, buf, count)) < 0)
                err_sys("write error");
        return n;
}

inline int Close(int sockfd)
{
        int n;

        if ( (n = close(sockfd)) < 0)
                err_sys("close error");

        return n;
}
