#include "unp.h"

void sig_chld(int signo)
{
        pid_t pid;
        int stat;

        /* wait() blocks until a childprocess has terminated, it acknowledges
         * that a child has finished and retrieves his status */
        pid = wait(&stat);

        /* we loop on while because we want to check if another child has
         * terminated at the exact same moment. We use waitpid() because it let
         * us customized the wait default behavior. We can pass, for example,
         * WNOHANG for immediately return 0 in case no child has terminated,
         * hence we say that waitpid() with WNOHANG is non-blocking */

        /* -1 means wait for any child process.*/
        while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
                printf("child %d terminated\n", pid);

        return;
}
