#include "../include/unp.h"

ssize_t writen(int fd, void *vptr, size_t n)
{
        ssize_t nleft;
        ssize_t nwritten;
        char *ptr; 
        ptr = vptr;
        nleft = n;

        while (n > 0)
        {
                if ( (nwritten = write(fd, ptr, nleft)) < 0)
                {
                        if (nwritten < 0 && errno == EINTR)
                                nwritten = 0;
                        else
                                return -1;
                }
                nleft -= nwritten;
                ptr += nwritten;
        }

        return n;
}

ssize_t Writen(int fd, void *vptr, size_t nbytes)
{
        ssize_t n;

        if ( (n = writen(fd, vptr,nbytes)) < 0)
                err_sys("write error");

        return n;
}
