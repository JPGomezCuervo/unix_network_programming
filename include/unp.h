#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXLINE         4096
#define BUFFSIZE        8192
#define LISTENQ         1024
#define SERV_PORT       9877

typedef void Sigfunc(int);

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
ssize_t Readline(int fd, void *vptr, size_t maxlen);
int Sock_pton_loose(int af, const char *src, void *dst);

/*libwrap*/
const char *Inet_ntop(int af, const void *src, char *dst, socklen_t size);
void Inet_pton(int af, const char *pstr, void *dst);
char *Fgets(char *buff, int size, FILE *stream);
int Fputs(char *s, FILE *stream);
Sigfunc *Signal(int signo, Sigfunc *func);
void sig_chld(int signo);

/* echo server */
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
