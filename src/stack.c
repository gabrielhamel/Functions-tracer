/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** stack
*/

#include <stdlib.h>

static const char *stack_pop(const char **stack)
{
    size_t len = 0;
    const char *data = NULL;

    for (; stack[len] != NULL; len++);
    if (len == 0)
        return (NULL);
    data = stack[len - 1];
    stack[len - 1] = NULL;
    return (data);
}

const char *stack(const char *data)
{
    static const char **stack = NULL;
    size_t len = 0;

    if (data == NULL && stack != NULL)
        return (stack_pop(stack));
    if (stack == NULL) {
        stack = malloc(sizeof(const char *) * 2);
        stack[0] = data;
        stack[1] = NULL;
    } else {
        for (; stack[len] != NULL; len++);
        stack = realloc(stack, sizeof(const char *) * (len + 2));
        stack[len] = data;
        stack[len + 1] = NULL;
    }
    return (NULL);
}