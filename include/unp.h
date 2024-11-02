#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <syslog.h>
#include <unistd.h>

#define MAXLINE         4096
#define BUFFSIZE        8192
#define LISTENQ         1024

void err_doit(int8_t errnoflag, int level, const char *fmt, va_list ap );
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);

int Socket(int domain, int type, int protocol);
char *Sock_ntop(const struct sockaddr *sa, socklen_t addrlen);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addr_len);
size_t Write(int fd, const void *buf, size_t count);
int Close(int sockfd);
ssize_t Readn(int fd, void *vptr, size_t nbytes);
ssize_t Writen(int fd, void *vptr, size_t nbytes);
