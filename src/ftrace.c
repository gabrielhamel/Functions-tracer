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

    waitpid(pid, &status, 0);
    while (WIFSTOPPED(status)) {
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        rip = ptrace(PTRACE_PEEKTEXT, pid, regs.rip);
        sig = get_signal(status);
        if ((rip & 0xffff) == 0x50f) {
            print_syscall(elf, pid, &regs, &status);
            continue;
        }
        else if ((rip & 0xff) == 0xe8)
            print_call(elf, pid, &regs);
        else if ((rip & 0xff) == 0xc3)
            print_ret(elf, pid, &regs);
        forward_next_step(pid, &status, sig);
    }
}