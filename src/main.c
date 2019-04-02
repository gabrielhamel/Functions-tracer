/*
** EPITECH PROJECT, 2019
** PSU_strace_2018
** File description:
** main
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "ftrace.h"

static Elf *getelf(const char *file)
{
    Elf *elf = NULL;
    int fd = open(file, O_RDONLY);

    if (fd == -1)
        return (NULL);
    elf_version(EV_CURRENT);
    elf = elf_begin(fd, ELF_C_READ, NULL);
    return (elf);
}

int main(int ac, char **av)
{
    Elf *elf = getelf(av[1]);
    pid_t pid = -1;
    char *str;

    if (ac == 1) {
        dprintf(STDERR_FILENO, "USAGE: ftrace <command>\n");
        return (84);
    }
    pid = launch_process(av + 1);
    if (pid == -1)
        return (84);
    printf("Entering function main\n");
    ftrace(elf, pid);
    str = stack(NULL);
    while (str){
        if (str != NULL && strlen(str))
            printf("Leaving function %s\n", str);
        str = stack(NULL);
    }
    printf("Leaving function main\n");
    return (0);
}