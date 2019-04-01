/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** print_std
*/

#include "strace.h"

size_t print_ulong(op_t *op, reg_t reg)
{
    return (dprintf(OUT, "%lu", (unsigned long)reg));
}

size_t print_sizet(op_t *op, reg_t reg)
{
    return (dprintf(OUT, "%zu", (size_t)reg));
}

size_t print_ssizet(op_t *op, reg_t reg)
{
    return (dprintf(OUT, "%zu", (ssize_t)reg));
}

size_t print_memstr(op_t *op, reg_t reg, size_t length)
{
    int i = 0;
    size_t len = 0;
    size_t print = 0;
    string_t data;

    print += dprintf(OUT, "\"");
    memset(data.str, 1, sizeof(data.ptr) + 1);
    while (!memchr(data.str, '\0', sizeof(data.ptr)) && len <= length) {
        memset(data.str, '\0', sizeof(data.ptr) + 1);
        data.ptr = ptrace(PTRACE_PEEKDATA, op->pid, reg + i *
        sizeof(data.ptr));
        for (int j = 0; j < sizeof(long) && j + len < length &&
        data.str[j]; j++)
            print += print_char(data.str[j]);
        len += strlen(data.str);
        i++;
    }
    print += dprintf(OUT, len > length ? "\"..." : "\"");
    return (print);
}

size_t print_string_short(op_t *op, reg_t reg)
{
    if (reg != 0)
        return (print_memstr(op, reg, 32));
    else
        return (dprintf(OUT, "NULL"));
}