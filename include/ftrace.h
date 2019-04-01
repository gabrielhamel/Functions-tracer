/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** strace
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <sys/types.h>
#include <sys/user.h>
#include <libelf.h>

#define GET_SIGNAME(x) {x, #x}

#define NB_SIGNAL 28
#define NO_SIGNAL 0

struct data_t {
    int nb;
    const char *name;
};

extern const struct data_t syscalls_tab[];
extern const struct data_t signals_tab[];

void ftrace(const char *elf, pid_t pid);
char *get_name_sym(const char *elf, long addr);
unsigned long long get_arg_no(struct user_regs_struct *regs, char no);
void forward_next_step(pid_t pid, int *status, int signal_send);
int get_signal(int status);
pid_t launch_process(char **av);
void print_syscall(const char *elf, pid_t pid,
struct user_regs_struct *regs, int *status);
void print_call(const char *elf, pid_t pid, struct user_regs_struct *regs);
void print_ret(const char *elf, pid_t pid, struct user_regs_struct *regs);
const char *stack(const char *data);

#endif