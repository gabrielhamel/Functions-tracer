/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** gnl
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

static int check_end(char *buffer, int mode)
{
    int counter = -1;
    int size = -1;

    if (buffer == NULL)
        size = 0;
    else
        while (buffer[++size] != '\0');
    if (mode)
        return (size);
    while (++counter < size)
        if (buffer[counter] == '\n')
            return (1);
    return (0);
}

char *add_str(char *base, char *to_add)
{
    char *end = NULL;
    int counter = -1;
    int size_b = check_end(base, 1);
    int size_a = check_end(to_add, 1);

    end = malloc(sizeof(char) * (size_a + size_b + 1));
    if (!end)
        return (NULL);
    end[size_a + size_b] = '\0';
    while (++counter < size_b)
        end[counter] = base[counter];
    if (base != NULL)
        free(base);
    counter = -1;
    while (++counter < size_a)
        end[size_b + counter] = to_add[counter];
    free(to_add);
    return (end);
}

char *str_add(int nb, ...)
{
    va_list liste;
    char *final = NULL;
    char *str = NULL;

    if (nb <= 0)
        return (NULL);
    va_start(liste, nb);
    for (int i = 0; i < nb; i++) {
        str = va_arg(liste, char *);
        final = add_str(final, strdup(str));
    }
    va_end(liste);
    return (final);
}