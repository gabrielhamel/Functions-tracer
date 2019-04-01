/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** path
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ftrace.h"

static char *concat_command(char *command, char **path, int i)
{
    char *pre = NULL;
    char *new = NULL;
    char *pwd = getcwd(NULL, 0);

    if (command[0] == '.') {
        pre = add_str(pwd, strdup("/"));
        new = add_str(pre, strdup(command));
    }
    else {
        pre = add_str(strdup(path[i]), strdup("/"));
        new = add_str(pre, strdup(command));
    }
    return (new);
}

static char **get_path(void)
{
    char *path = getenv("PATH");
    char *location = NULL;
    char **tab = NULL;
    char *tmp = NULL;

    location = malloc(sizeof(1000));
    confstr(_CS_PATH, location, 1000);
    if (path == NULL)
        path = location;
    else {
        tmp = str_add(3, location , ":", path);
        path = tmp;
    }
    tab = str_to_word_tab(path, ':');
    return (tab);
}

char *search_bin(char *bin)
{
    char *new = NULL;
    char **path = get_path();

    if (!access(bin, F_OK))
        return (strdup(bin));
    else if (path == NULL)
        return (strdup(""));
    for (int i = 0; path[i] != NULL; i++) {
        new = concat_command(bin, path, i);
        if (!access(new, F_OK))
            return (new);
        free(new);
    }
    return (strdup(""));
}