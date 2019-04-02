/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** print
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <syscall.h>
#include "ftrace.h"

void print_syscall(pid_t pid, struct user_regs_struct *regs, int *status)
{
    struct user_regs_struct next;

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
}

void print_call(Elf *elf, pid_t pid, struct user_regs_struct *regs)
{
    long rip_addr = ptrace(PTRACE_PEEKTEXT, pid, regs->rip);
    long offset = (rip_addr >> 8) + regs->rip + 5;
    char str[15] = {0};
    char *sym = NULL;

    (void)elf;
    snprintf(str, 15, "%x", (unsigned int)offset);
    offset = strtol(str, NULL, 16);
    sym = find_symname(elf, offset);
    if (sym == NULL)
        stack("");
    if (sym && strlen(sym)) {
        printf("Entering function %s at 0x%x\n", sym, (unsigned int)offset);
        stack(sym);
        return;
    }
}

void print_ret(Elf *elf, pid_t pid, struct user_regs_struct *regs)
{
    char *name = stack(NULL);

    (void)elf;
    (void)pid;
    (void)regs;
    if (name != NULL && strlen(name))
        printf("Leaving function %s\n", name);
}