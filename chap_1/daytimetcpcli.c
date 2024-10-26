#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/syslog.h>
#include <syslog.h>
#include <unistd.h>
#include "err.h"
#include "unp.h"

int main(int argc, char **argv) {
  int sockfd, n;
  char recvline [MAXLINE + 1];
  struct sockaddr_in servaddr;
  /*
   * int socket (int domain, int type, int protocol);
   *
   * domain -> address family scheme to be used.
   *      AF_INET = IPv4 | AF_INET6 = IPv6
   *
   * type -> communication characteristics.
   *    SOCK_STREAM = connection-oriented. Reliable two-way communication connection 
   *    based, like TCP. Data is read in a continuos stream. eg. send (1-2-3), received
   *    (1-2-3). Has no boundaries.
   *
   *    SOCK_DGRAM = connectionless. No connection is stablished before sending packets.
   *    It's unreliable and the order isn't guaranteed. Has boundaries
   *
   *    SOCK_RAW = Low level control of packets or to create custom protocols.
   *
   * protocol -> specifies the protocol. If its set in 0 the function will set their
   * defaults according to the args. 
   *    eg. AF_INET + SOCK_STREAM = TCP. AF_INET + SOCK_DGRAM = UDP
   *
   * ON_ERROR -> -1.
   */

  if (argc != 2)
    printf("Usage: ./daytimetcp <IPaddress>\n");

  if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
          err_sys("socket error");

  /*
   * bzero has to be called with the struct sockaddr_in because it has be initialized
   * with all values at zero. Otherwise there's going to be garbage values in the 
   * array property sin_zero[]. This property needs to be on zero because it is required
   * by other low level networking functions. sin_zero[] is used as a padding to
   * maintain the castability with the struct sockaddr.
   *    struct sockaddr {
   *            unsigned short    sa_family;    // address family, AF_xxx
   *            char              sa_data[14];  // 14 bytes of protocol address
   *                              |
   *                              *--> contains a destination address and port number for the socket
   *     }; 
   *
   *
   * because filling the struct sockaddr was error prone and arguably inconveniant,
   * programmers created the parallel struct sockaddr_in, which made easy to fill
   * the properties. struct sockaddr_in is castable to sockaddr and viceversa.
   *
   *    struct sockaddr_in {
   *            short int          sin_family;  // Address family, AF_INET
   *            unsigned short int sin_port;    // Port number
   *            struct in_addr     sin_addr;    // Internet address
   *            unsigned char      sin_zero[8]; // Same size as struct sockaddr
   *     };
   *
   */
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(13);

  /*
   * int inet_pton(int domain, char ip_address, uint32_t s_addr | uint64_t s_addr);
   *                                                    |
   *                                                    *-> 4 bytes, direction in case
   *                                                    of IPv4 and 8 bytes direction in
   *                                                    case of IPv6.
   *
   * receives a string with the ip address (IPv4 || IPv6) and translates that to
   * network address structure. On success returns 1.
   * ON_ERROR -> 0 (malformed ip address), -1 (does not support the AF_FAMILY)
   */
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) < 1)
          err_sys("inet_pton error");

  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
          err_sys("connect error");

  while ( (n = read(sockfd, recvline, MAXLINE )) > 0)
  {
          recvline[n] = '\0';

          if(fputs(recvline, stdout) == EOF) 
                  err_sys("fputs error");
  }

  if (n < 0)
          err_sys("read error");

  exit(0);
}
