#include "unp.h"

// Signal returns the old handler because we don't want to lose the default handler

Sigfunc *signal(int signo, Sigfunc *func)
{
        struct sigaction act, oact;

        act.sa_handler = func;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        if (signo != SIGALRM)
                act.sa_flags |= SA_RESTART;

        // sigaction subscribes a handler and a behavior to certain signal
        if (sigaction(signo, &act, &oact) < 0)
                return SIG_ERR;

        return oact.sa_handler;
}

Sigfunc *Signal(int signo, Sigfunc *func)
{
        Sigfunc *sigfunc;

        if ( (sigfunc = signal(signo, func)) == SIG_ERR)
                err_sys("signal error");

        return sigfunc;
}
