/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** strace
*/

#include "strace.h"
#include <byteswap.h>

void forward_next_step(pid_t pid, int *status, int signal)
{
    ptrace(PTRACE_SINGLESTEP, pid, 0, signal);
    waitpid(pid, status, 0);
}

void get_registers(pid_t pid, struct user_regs_struct *regs, long *inst)
{
    ptrace(PTRACE_GETREGS, pid, 0, regs);
    if (inst != NULL)
        *inst = ptrace(PTRACE_PEEKTEXT, pid, regs->rip, 0);
}

size_t print_syscall(op_t *op, int *status, struct user_regs_struct *regs)
{
    struct user_regs_struct next;
    size_t len = 0;

    forward_next_step(op->pid, status, 0);
    len += print_header(op, regs);
    get_registers(op->pid, &next, NULL);
    regs->orig_rax = next.rax;
    len += dprintf(OUT, ")");
    len += print_footer(op, regs);
    return (len);
}

size_t print_function(Elf *elf, op_t *op, int *status, struct user_regs_struct *regs)
{
    long rip = ptrace(PTRACE_PEEKTEXT, op->pid, regs->rip);
    long offset = (rip >> 8) + regs->rip + 5;
    char str[15] = {0};
    char *sym = NULL;
    size_t len = 0;

    snprintf(str, 15, "%x", offset);
    offset = strtol(str, NULL, 16);
    sym = getNameSym(elf, offset);
    if (sym)
        len += dprintf(OUT, "Entering function %s at 0x%x\n", sym, offset);
    return (len);
}

int print_signal(int status)
{   
    for (int i = 0; i < 28; i++) {
        if (WSTOPSIG(status) == sig_tab[i].no) {
            dprintf(OUT, "Received signal %s\n", sig_tab[i].name);
            return (sig_tab[i].no);
        }
    }
    return (0);
}

void strace(op_t *op, Elf *elf)
{
    int status;
    long command = 0;
    int signal = 0;
    struct user_regs_struct regs;

    waitpid(op->pid, &status, 0);
    while (WIFSTOPPED(status)) {
        get_registers(op->pid, &regs, &command);
        signal = print_signal(status);
        if ((command & 0xffff) == 0x50f) {
            print_syscall(op, &status, &regs);
            continue;
        }
        else if ((command & 0xff) == 0xe8)
            print_function(elf, op, &status, &regs);
        forward_next_step(op->pid, &status, signal);
    }
}