#include "unp.h"

int main(int argc, char **argv)
{
        int sockfd [5];
        struct sockaddr_in srvaddr = {0};

        if (argc != 2)
                err_quit("Usage: echocli <IPAddress>");


        for (int i = 0; i < 5; i++)
        {
                sockfd[i] = Socket(AF_INET, SOCK_STREAM, 0);
                Inet_pton(AF_INET, argv[1], &srvaddr.sin_addr);
                srvaddr.sin_family = AF_INET;
                srvaddr.sin_port = htons(SERV_PORT);
                Connect(sockfd[i], (struct sockaddr *) &srvaddr, sizeof(srvaddr));
        }



        str_cli(stdin, sockfd[0]);

        exit(0);
}
