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

        for (;;)
        {
                connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

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
