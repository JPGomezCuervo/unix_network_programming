#include "unp.h"

int main()
{
        int listenfd, connfd;
        struct sockaddr_in servaddr, cliaddr;
        char buf [MAXLINE + 1];
        time_t ticks;
        socklen_t len;

        listenfd = Socket(AF_INET, SOCK_STREAM, 0);

        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;

        /* in IPv4 s_addr is a struct of uint32_t, the reason for doing this it's
         * because it's easier to read, and because in the past the developers thought
         * they would use that propperty to create other types of addresses. At the
         * end of the day IPv6 was created and a whole new structure was created:
         * sockaddr_in6*/
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
        servaddr.sin_port = htons(13);

        Bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

        Listen(listenfd, LISTENQ);

        printf("%s", "Listening on port 13 of 127.0.0.1 ...\n");


        for ( ; ; )
        {
                len = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &len);
                printf("Connection from %s, port %d\n",
                        Inet_ntop(AF_INET, &cliaddr.sin_family, buf, sizeof(buf)),
                        ntohs(cliaddr.sin_port));

                ticks = time(NULL);

                snprintf(buf, MAXLINE, "%.24s\r\n", ctime(&ticks));
                
                for (int i = 0; i < strlen(buf); i++)
                        Write(connfd, &buf[i], 1);
               
                Close(connfd);
        }

        return 0;
}
