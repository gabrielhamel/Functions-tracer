/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** print
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <syscall.h>
#include "ftrace.h"

void print_syscall(const char *elf, pid_t pid,
struct user_regs_struct *regs, int *status)
{
    struct user_regs_struct next;

    (void)elf;
    forward_next_step(pid, status, 0);
    printf("Syscall %s(", syscalls_tab[regs->rax].name);
    for (int i = 0; i < syscalls_tab[regs->rax].nb; i++) {
        printf("0x%llx", get_arg_no(regs, i));
        if (i + 1 != syscalls_tab[regs->rax].nb)
            printf(", ");
    }
    ptrace(PTRACE_GETREGS, pid, NULL, &next);
    if (regs->rax != SYS_exit && regs->rax != SYS_exit_group)
        printf(") = 0x%llx\n", next.rax);
    else
        printf(") = ?\n");
    if (regs->rax == SYS_openat) {
         stack_lib("test");
         printf("%lld\n", regs->orig_rax);
     }
}

void print_call(const char *elf, pid_t pid, struct user_regs_struct *regs)
{
    long rip_addr = ptrace(PTRACE_PEEKTEXT, pid, regs->rip);
    long offset = (rip_addr >> 8) + regs->rip + 5;
    char str[15] = {0};
    char *sym = NULL;

    snprintf(str, 15, "%x", (unsigned int)offset);
    offset = strtol(str, NULL, 16);
    sym = get_name_sym(elf, offset);
    if (sym != NULL) {
        printf("Entering function %s at 0x%x\n", sym, (unsigned int)offset);
        stack(sym);
    }
}

void print_ret(const char *elf, pid_t pid, struct user_regs_struct *regs)
{
    const char *name = stack(NULL);

    (void)elf;
    (void)pid;
    (void)regs;
    if (name != NULL)
        printf("Leaving function %s\n", name);
}