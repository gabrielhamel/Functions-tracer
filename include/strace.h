/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** strace
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/user.h>

#define _GNU_SOURCE

#include <libelf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <gelf.h>

#define OUT 1
#define GETNAME(x) {x, #x}

typedef struct op_t {
    bool s;
    bool p;
    pid_t pid;
    size_t offset;
} op_t;

enum e_type
{
    T_DEFAULT,
    T_INTEGER,
    T_POINTER,
    T_STRING,
    T_STRINGSHORT,
    T_MEMORY,
    T_LONG,
    T_ULONG,
    T_SIZE_T,
    T_SSIZE_T,
};

typedef unsigned long long int reg_t;

typedef size_t (*printer_t)(op_t *, reg_t);

typedef struct syscall_arg_t
{
    bool custom;
    union {
        enum e_type	type;
        printer_t callback;
    } printer;
} syscall_arg_t;

typedef struct syscall_t
{
    unsigned long long id;
    const char *name;
    bool noreturn;
    enum e_type	retval;
    size_t argc;
    syscall_arg_t args[6];
} syscall_t;

typedef struct characters_t
{
    char *str;
} characters_t;

typedef union string_t {
    long ptr;
    char str[sizeof(long) + 1];
} string_t;

typedef struct signal_t
{
    int no;
    char *name;
} signal_t;

extern const syscall_t syscalls_g[];
extern const printer_t printers_g[];
extern const characters_t characters_g[];
extern const signal_t sig_tab[];

void strace(op_t *op, Elf *elf);
size_t print_char(char c);
size_t print_reg(op_t *op, reg_t reg, const syscall_arg_t *type);
reg_t get_reg64(struct user_regs_struct *regs, int i);
size_t print_header(op_t *op, struct user_regs_struct *regs);
size_t print_footer(op_t *op, struct user_regs_struct *regs);
size_t print_memstr(op_t *op, reg_t reg, size_t length);

size_t print_default(op_t *op, reg_t reg);
size_t print_int(op_t *op, reg_t reg);
size_t print_ptr(op_t *op, reg_t reg);
size_t print_string(op_t *op, reg_t reg);
size_t print_string_short(op_t *op, reg_t reg);
size_t print_memory(op_t *op, reg_t reg);
size_t print_long(op_t *op, reg_t reg);
size_t print_ulong(op_t *op, reg_t reg);
size_t print_sizet(op_t *op, reg_t reg);
size_t print_ssizet(op_t *op, reg_t reg);

size_t print_flags_open(op_t *op, reg_t reg);
size_t print_stat_struct(op_t *op, reg_t reg);
size_t print_mmap_flags(op_t *op, reg_t reg);

Elf_Scn *findSymTable(Elf *elf);
size_t sizeSymTable(Elf_Scn *symtab);
char *find_symname(Elf *elf, Elf_Scn *symtab, size_t nbElem, Elf64_Addr value);
char *getNameSym(Elf *elf, Elf64_Addr addr);
Elf *elfFile(const char *filename, bool openfile);

#endif