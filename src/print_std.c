/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** print_std
*/

#include "strace.h"

size_t print_default(op_t *op, reg_t reg)
{
    return (dprintf(OUT, "0x%llx", reg));
}

size_t print_int(op_t *op, reg_t reg)
{
    return (dprintf(OUT, "%d", (int)reg));
}

size_t print_ptr(op_t *op, reg_t reg)
{
    if (reg != 0)
        return (dprintf(OUT, "0x%llx", reg));
    else
        return (dprintf(OUT, "NULL"));
}

size_t print_string(op_t *op, reg_t reg)
{
    if (reg != 0)
        return (print_memstr(op, reg, -1));
    else
        return (dprintf(OUT, "NULL"));
}

size_t print_long(op_t *op, reg_t reg)
{
    return (dprintf(OUT, "%ld", (long)reg));
}