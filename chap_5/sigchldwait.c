#include "unp.h"

void sig_chld(int signo)
{
        pid_t pid;
        int stat;

        pid = wait(&stat);

        /* -1 means wait for any child process */
        while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
                printf("child %d terminated\n", pid);

        return;
}
