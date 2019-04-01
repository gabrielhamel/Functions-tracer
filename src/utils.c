/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** utils
*/

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "ftrace.h"

unsigned long long get_arg_no(struct user_regs_struct *regs, char no)
{
    switch (no) {
        case 0:
            return (regs->rdi);
        break;
        case 1:
            return (regs->rsi);
        break;
        case 2:
            return (regs->rdx);
        break;
        case 3:
            return (regs->r10);
        break;
        case 4:
            return (regs->r8);
        break;
        case 5:
            return (regs->r9);
    }
    return (0);
}

void forward_next_step(pid_t pid, int *status, int signal_send)
{
    ptrace(PTRACE_SINGLESTEP, pid, 0, signal_send);
    waitpid(pid, status, 0);
}

int get_signal(int status)
{
    for (int i = 0; i < NB_SIGNAL; i++)
        if (WSTOPSIG(status) == signals_tab[i].nb) {
            printf("Received signal %s\n", signals_tab[i].name);
            return (signals_tab[i].nb);
        }
    return (NO_SIGNAL);
}

pid_t launch_process(char **av)
{
    pid_t pid = -1;

    if (av == NULL)
        return (-1);
    pid = fork();
    signal(SIGINT, SIG_IGN);
    if (pid == -1)
        return (-1);
    else if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvp(av[0], av);
        dprintf(STDERR_FILENO, "ftrace: Can't stat '%s': " \
        "No such file or directory\n", av[0]);
        return (-1);
    }
    return (pid);
}

char *get_memstr(pid_t pid, unsigned long long int reg)
{
    string_t str;
    size_t i = 0;
    char *newstr = strdup("");

    memset(str.str, 1, sizeof(long));
    while (!memchr(str.str, 0, sizeof(long))) {
        str.ptr = ptrace(PTRACE_PEEKTEXT, pid, reg + i++ * sizeof(long));
        newstr = realloc(newstr, strlen(newstr) + sizeof(long));
        strncat(newstr + strlen(newstr), str.str, sizeof(long));
    }
    return (newstr);
}