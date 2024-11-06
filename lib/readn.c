#include <unp.h>

ssize_t readn(int fd, void *vptr, size_t n)
{
        size_t nleft;
        ssize_t nread;
        char *ptr;

        ptr = vptr;
        nleft = n;

        while (nleft > 0)
        {
                if ( (nread = read(fd, ptr, nleft)) < 0)
                {
                        if (errno == EINTR) // EINTER interrupted function call
                                nread = 0;
                        else
                                return -1;
                }
                else if (nread == 0) // EOF
                        break;

                nleft -= nread;
                ptr += nread;
        }
        return n - nleft;
}

ssize_t Readn(int fd, void *vptr, size_t nbytes)
{
        ssize_t n;

        if ( (n = readn(fd, vptr, nbytes)) < 0)
                err_sys("read error");
        return n;
}
