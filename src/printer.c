/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** print_std
*/

#include "strace.h"

size_t print_flags_open(op_t *op, reg_t reg)
{
    if (reg != 0)
        return (dprintf(OUT, "0x%llx", reg));
    else
        return (dprintf(OUT, "NULL"));
}

size_t print_stat_struct(op_t *op, reg_t reg)
{
    if (reg != 0)
        return (dprintf(OUT, "0x%llx", reg));
    else
        return (dprintf(OUT, "NULL"));
}

size_t print_mmap_flags(op_t *op, reg_t reg)
{
    if (reg != 0)
        return (dprintf(OUT, "0x%llx", reg));
    else
        return (dprintf(OUT, "NULL"));
}