/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** print
*/

#include "strace.h"

size_t print_char(char c)
{
    if (c >= ' ' && c <= '~')
        return (dprintf(OUT, "%c", c));
    else
        return (dprintf(OUT, "%s", characters_g[c].str));
}

size_t print_reg(op_t *op, reg_t reg, const syscall_arg_t *type)
{
    return (print_default(op, reg));
}

reg_t get_reg64(struct user_regs_struct *regs, int i)
{
    switch (i) {
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

size_t print_header(op_t *op, struct user_regs_struct *regs)
{
    size_t len = 0;

    len += dprintf(OUT, "Syscall ");
    len += dprintf(OUT, "%s(", syscalls_g[regs->rax].name);
    for (int i = 0; i < syscalls_g[regs->rax].argc; i++) {
        len += print_reg(op, get_reg64(regs, i),
        &syscalls_g[regs->rax].args[i]);
        if (i + 1 != syscalls_g[regs->rax].argc)
            len += dprintf(OUT, ", ");
    }
    return (len);
}

size_t print_footer(op_t *op, struct user_regs_struct *regs)
{
    size_t len = 0;

    len += dprintf(OUT, " = ");
    if (syscalls_g[regs->rax].noreturn == false)
        len += print_default(op, regs->orig_rax);
    else
        len += dprintf(OUT, "?");
    len += dprintf(OUT, "\n");
    return (len);
}