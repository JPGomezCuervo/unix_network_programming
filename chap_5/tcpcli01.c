#include "unp.h"

int main(int argc, char **argv)
{
        int sockfd;
        struct sockaddr_in srvaddr = {0};

        if (argc != 2)
                err_quit("Usage: echocli <IPAddress>");

        sockfd = Socket(AF_INET, SOCK_STREAM, 0);

        srvaddr.sin_family = AF_INET;
        srvaddr.sin_port = htons(SERV_PORT);

        /* remember, inet_pton uses the sockaddr_in.sin_addr as the dest,
         * because it takes a string a converts it into a network address
         * structure */

        Inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);

        Connect(sockfd, (struct sockaddr *) &srvaddr, sizeof(srvaddr));

        str_cli(stdin, sockfd);

        exit(0);
}
