#include <stdio.h>
#include <sys/socket.h>
int main() {
  int sockfd;
  /* int socket (int domain, int type, int protocol);
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
   */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  return 0;
}
