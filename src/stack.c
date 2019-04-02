/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** stack
*/

#include <gelf.h>
#include <stdlib.h>
#include "ftrace.h"

static char *stack_pop(char **stack)
{
    size_t len = 0;
    char *data = NULL;

    for (; stack[len] != NULL; len++);
    if (len == 0)
        return (NULL);
    data = stack[len - 1];
    stack[len - 1] = NULL;
    return (data);
}

char *stack(char *data)
{
    static char **stack = NULL;
    size_t len = 0;

    if (data == NULL && stack != NULL)
        return (stack_pop(stack));
    if (stack == NULL) {
        stack = malloc(sizeof(char *) * 2);
        stack[0] = data;
        stack[1] = NULL;
    } else {
        for (; stack[len] != NULL; len++);
        stack = realloc(stack, sizeof(char *) * (len + 2));
        stack[len] = data;
        stack[len + 1] = NULL;
    }
    return (NULL);
}