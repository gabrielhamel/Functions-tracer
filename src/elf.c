/*
** EPITECH PROJECT, 2019
** PSU_ftrace_2018
** File description:
** elf
*/

#include <gelf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "ftrace.h"

static Elf_Scn *find_sym_table(Elf *elf)
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;

    if (elf == NULL)
        return (NULL);
    do {
        scn = elf_nextscn(elf, scn);
        if (scn != NULL) {
            gelf_getshdr(scn, &shdr);
            if (shdr.sh_type == SHT_SYMTAB)
                return (scn);
        }
    } while (scn);
    return (NULL);
}

static size_t size_sym_table(Elf_Scn *symtab)
{
    GElf_Shdr shdr;

    if (symtab == NULL)
        return (0);
    gelf_getshdr(symtab, &shdr);
    return (shdr.sh_size / shdr.sh_entsize);
}

static char *find_symname(Elf *elf, Elf_Scn *stab, size_t size, long addr)
{
    GElf_Shdr shdr;
    GElf_Sym sym;
    Elf_Data *data = NULL;

    if (elf == NULL || stab == NULL)
        return (NULL);
    data = elf_getdata(stab, NULL);
    for (size_t i = 0; i < size; i++) {
        gelf_getsym(data, i, &sym);
        if ((Elf64_Addr)addr == sym.st_value && sym.st_name) {
            gelf_getshdr(stab, &shdr);
            return (elf_strptr(elf, shdr.sh_link, sym.st_name));
        }
    }
    return (NULL);
}

char *get_name_sym(char *filename, long addr)
{
    Elf *elf = NULL;
    Elf_Scn *symtab = NULL;
    char *name = NULL;
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
        return (NULL);
    elf_version(EV_CURRENT);
    elf = elf_begin(fd, ELF_C_READ, NULL);
    if (elf == NULL)
        return (NULL);
    symtab = find_sym_table(elf);
    if (symtab == NULL)
        return (NULL);
    name = find_symname(elf, symtab, size_sym_table(symtab), addr);
    elf_end(elf);
    close(fd);
    return (name);
}