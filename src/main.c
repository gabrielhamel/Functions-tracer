/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** main
*/

#include <unistd.h>
#include <stdio.h>
#include "ftrace.h"

int main(int ac, char **av)
{
    pid_t pid = -1;

    if (ac == 1) {
        dprintf(STDERR_FILENO, "USAGE: ftrace <command>\n");
        return (84);
    }
    pid = launch_process(av + 1);
    if (pid == -1)
        return (84);
    ftrace((av + 1)[0], pid);
    return (0);
}