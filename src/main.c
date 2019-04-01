/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** main
*/

#include "strace.h"
#include <signal.h>

pid_t get_pid(char *str)
{
    if (str == NULL) {
        dprintf(2, "strace: option requires an argument -- 'p'\n" \
        "Try 'strace -h' for more information.\n");
        return (-1);
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9')) {
            dprintf(2, "strace: Invalid process id: '%s'\n", str);
            return (-1);
        }
    }
    return (atoi(str));
}

int parsing(op_t *op, char **av)
{
    for (int i = 1; av[i] != NULL && i < 4; i++) {
        if (!strcmp(av[i], "-s")) {
            op->s = true;
            op->offset++;
        }
        else if (!strcmp(av[i], "-p")) {
            op->p = true;
            op->pid = get_pid(av[i + 1]);
            op->offset += 2;
        }
    }
    if (op->pid == -1)
        return (-1);
    return (0);
}

pid_t launch_process(char **av)
{
    pid_t pid;

    if (av == NULL)
        return (-1);
    pid = fork();
    if (pid == -1)
        return (-1);
    else if (pid == 0) {
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        execvp(av[0], av);
        dprintf(2, "strace: Can't stat '%s': " \
        "No such file or directory\n", av[0]);
        exit(84);
    }
    return (pid);
}

int main(int ac, char **av, char **env)
{
    Elf *elf = NULL;
    pid_t pid = -1;
    op_t op = {.p = false, .s = false, .pid = 0, .offset = 1};

    if (ac == 1) {
        dprintf(2, "USAGE: %s [-s] [-p <pid>|<command>]\n", av[0]);
        return (84);
    }
    signal(SIGINT, SIG_IGN);
    if (parsing(&op, av))
        return (84);
    else if (op.p == false)
        op.pid = launch_process(av + op.offset);
    if (op.pid == -1)
        return (84);
    elf = elfFile((av + op.offset)[0], true);
    strace(&op, elf);
    elfFile(NULL, false);
    return (0);
}