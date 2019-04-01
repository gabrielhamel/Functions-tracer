/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** strtab
*/

#include <stdlib.h>
#include <string.h>

static int get_lenght(char *str, int index, char delim)
{
    int counter = -1;

    while (str[++counter + index] != delim &&
    str[index + counter] != '\0');
    return (counter);
}

static int count_arg(char *str, char delim, int len)
{
    int nb = 0;

    for (int i = 0; i < len; i++) {
        while (str[i] == delim && i < len)
            i++;
        if (i < len)
            nb++;
        else
            break;
        while (str[i] != delim && i < len)
            i++;
    }
    return (nb);
}

char **str_to_word_tab(char *str, char delim)
{
    int nb = 0;
    char **tab = NULL;
    int len = strlen(str);
    int cursor = -1;

    if (str == NULL)
        return (NULL);
    nb = count_arg(str, delim, len);
    tab = malloc(sizeof(char *) * (nb + 1));
    for (int i = 0; i < nb; i++) {
        while (str[++cursor] == delim);
        len = get_lenght(str, cursor, delim);
        tab[i] = malloc(sizeof(char) * (len + 1));
        for (int j = 0; j < len; j++)
            tab[i][j] = str[cursor + j];
        tab[i][len] = '\0';
        cursor += len;
    }
    tab[nb] = NULL;
    return (tab);
}

void destroy_tab(char **tab)
{
    if (tab == NULL)
        return;
    for (int i = 0; tab[i] != NULL; i++)
        free(tab[i]);
    free(tab);
}