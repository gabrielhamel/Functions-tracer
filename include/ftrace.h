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
#include <gelf.h>

#define GET_SIGNAME(x) {x, #x}

#define NB_SIGNAL 28
#define NO_SIGNAL 0
#define INVALID_DYN "ld.so.cache"

struct data_t {
    int nb;
    const char *name;
};

typedef union string_t {
    long ptr;
    char str[sizeof(long)];
} string_t;

extern const struct data_t syscalls_tab[];
extern const struct data_t signals_tab[];

void ftrace(Elf *elf, pid_t pid);
unsigned long long get_arg_no(struct user_regs_struct *regs, char no);
void forward_next_step(pid_t pid, int *status, int signal_send);
int get_signal(int status);
pid_t launch_process(char **av);
void print_syscall(pid_t pid, struct user_regs_struct *regs, int *status);
void print_call(Elf *elf, pid_t pid, struct user_regs_struct *regs);
void print_ret(Elf *elf, pid_t pid, struct user_regs_struct *regs);
char *stack(char *data);
char *find_symname(Elf *elf, long addr);

#endif