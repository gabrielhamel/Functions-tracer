/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** print_std3
*/

#include "strace.h"

size_t print_memory(op_t *op, reg_t reg)
{
    int i = 0;
    size_t len = 0;
    size_t print = 0;
    string_t data;

    print += dprintf(OUT, "\"");
    memset(data.str, 1, sizeof(data.ptr) + 1);
    while (!memchr(data.str, '\0', sizeof(data.ptr)) && len <= 32) {
        memset(data.str, '\0', sizeof(data.ptr) + 1);
        data.ptr = ptrace(PTRACE_PEEKDATA, op->pid, reg + i *
        sizeof(data.ptr));
        for (int j = 0; j < sizeof(long) && j + len < 32; j++)
            print += print_char(data.str[j]);
        len += strlen(data.str);
        i++;
    }
    print += dprintf(OUT, len > 32 ? "\"..." : "\"");
    return (print);
}