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

static void getelf(const char *file, Elf **elf)
{
    int fd = open(file, O_RDONLY);

    if (fd == -1) {
        *elf = NULL;
        return;
    }
    elf_version(EV_CURRENT);
    *elf = elf_begin(fd, ELF_C_READ, NULL);
}

static void empty_stack(void)
{
    char *str = stack(NULL);

    while (str){
        if (str != NULL && strlen(str))
            printf("Leaving function %s\n", str);
        str = stack(NULL);
    }
}

int main(int ac, char **av)
{
    Elf *elf = NULL;
    pid_t pid = -1;

    if (ac == 1) {
        dprintf(STDERR_FILENO, "USAGE: ftrace <command>\n");
        return (84);
    }
    getelf(av[1], &elf);
    pid = launch_process(av + 1);
    if (pid == -1)
        return (84);
    printf("Entering function main\n");
    ftrace(elf, pid);
    empty_stack();
    printf("Leaving function main\n");
    return (0);
}