#include "unp.h"

int main()
{
        int listenfd, connfd;
        pid_t childpid;
        struct sockaddr_in srvaddr = {0}, cliaddr = {0};
        socklen_t clilen;

        clilen = sizeof(cliaddr);

        listenfd = Socket(AF_INET, SOCK_STREAM, 0);

        srvaddr.sin_family = AF_INET;
        srvaddr.sin_port = htons(SERV_PORT);
        srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);


        Bind(listenfd, (struct sockaddr *) &srvaddr, sizeof(srvaddr));

        Listen(listenfd, LISTENQ);
        Signal(SIGCHLD, sig_chld);

        for (;;)
        {

                /* for matter of compatibility we should restart manually the
                 * slow syscall (accept) because not all unix-like kernels
                 * restart automatically the syscalls interrupted by EINTR some
                 * functions that should be handled like this are: read, write,
                 * select and open. NOTE: connect can't be restarted*/

                if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
                {
                        /* when a syscall is interrupted by a signal errno is
                         * set to EINTR */

                        if (errno == EINTR)
                                continue;
                        else
                                err_sys("accept error");
                }

                if ((childpid = fork()) == 0)
                {
                        Close(listenfd);
                        str_echo(connfd); /* process request */
                        Close(connfd);
                        exit(0);
                }
                Close(connfd);
        }
        return 0;
}
