/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** strace
*/

#include <sys/ptrace.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "ftrace.h"

void ftrace(const char *elf, pid_t pid)
{
    int status;
    long rip = 0;
    int sig = 0;
    struct user_regs_struct regs;

    signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    while (WIFSTOPPED(status)) {
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        rip = ptrace(PTRACE_PEEKTEXT, pid, regs.rip);
        sig = get_signal(status);
        if ((rip & 0xffff) == 0x50f) {
            forward_next_step(pid, &status, 0);
            print_syscall(elf, pid, &regs);
            continue;
        }
        else if ((rip & 0xff) == 0xe8)
            print_call(elf, pid, &regs);
        forward_next_step(pid, &status, sig);
    }
}