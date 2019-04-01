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

void ftrace(char *elf, pid_t pid);
char *get_name_sym(char *elf, long addr);
unsigned long long get_arg_no(struct user_regs_struct *regs, char no);
void forward_next_step(pid_t pid, int *status, int signal_send);
int get_signal(int status);
pid_t launch_process(char **av);
void print_syscall(pid_t pid, struct user_regs_struct *regs, int *status);
void print_call(char *elf, pid_t pid, struct user_regs_struct *regs);
void print_ret(char *elf, pid_t pid, struct user_regs_struct *regs);
char *stack(char *data);
char **stack_lib(char *data);
char *get_memstr(pid_t pid, unsigned long long int reg);
char **str_to_word_tab(char *str, char delim);
void destroy_tab(char **tab);
char *add_str(char *base, char *to_add);
char *str_add(int nb, ...);
char *search_bin(char *bin);

#endif