/*
** EPITECH PROJECT, 2019
** secondary
** File description:
** signals
*/

#include "ftrace.h"
#include <signal.h>

const struct data_t signals_tab[] = {
    GET_SIGNAME(SIGWINCH),
    GET_SIGNAME(SIGABRT),
    GET_SIGNAME(SIGALRM),
    GET_SIGNAME(SIGBUS),
    GET_SIGNAME(SIGCHLD),
    GET_SIGNAME(SIGCONT),
    GET_SIGNAME(SIGFPE),
    GET_SIGNAME(SIGHUP),
    GET_SIGNAME(SIGILL),
    GET_SIGNAME(SIGINT),
    GET_SIGNAME(SIGKILL),
    GET_SIGNAME(SIGPIPE),
    GET_SIGNAME(SIGQUIT),
    GET_SIGNAME(SIGSEGV),
    GET_SIGNAME(SIGSTOP),
    GET_SIGNAME(SIGTERM),
    GET_SIGNAME(SIGTSTP),
    GET_SIGNAME(SIGTTIN),
    GET_SIGNAME(SIGTTOU),
    GET_SIGNAME(SIGUSR1),
    GET_SIGNAME(SIGUSR2),
    GET_SIGNAME(SIGPOLL),
    GET_SIGNAME(SIGPROF),
    GET_SIGNAME(SIGSYS),
    GET_SIGNAME(SIGURG),
    GET_SIGNAME(SIGVTALRM),
    GET_SIGNAME(SIGXCPU),
    GET_SIGNAME(SIGXFSZ)
};