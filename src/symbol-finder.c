/*
** EPITECH PROJECT, 2019
** ftrace
** File description:
** symbol-finder
*/

#define _GNU_SOURCE

#include <libelf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <gelf.h>

Elf_Scn *findSymTable(Elf *elf)
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

size_t sizeSymTable(Elf_Scn *symtab)
{
    GElf_Shdr shdr;

    if (symtab == NULL)
        return (0);
    gelf_getshdr(symtab, &shdr);
    return (shdr.sh_size / shdr.sh_entsize);    
}

char *find_symname(Elf *elf, Elf_Scn *symtab, size_t nbElem, Elf64_Addr value)
{
    GElf_Shdr shdr;
    GElf_Sym sym;
    Elf_Data *data = NULL;

    if (elf == NULL || symtab == NULL)
        return (NULL);
    data = elf_getdata(symtab, NULL);
    for (size_t i = 0; i < nbElem; i++) {
        gelf_getsym(data, i, &sym);
        if (value == sym.st_value && sym.st_name) {
            gelf_getshdr(symtab, &shdr);
            return (elf_strptr(elf, shdr.sh_link, sym.st_name));
        }
    }
    return (NULL);
}

char *getNameSym(Elf *elf, Elf64_Addr addr)
{

    Elf_Scn *symtab = findSymTable(elf);

    if (symtab == NULL)
        return (NULL);
    return (find_symname(elf, symtab, sizeSymTable(symtab), addr));
}

Elf *elfFile(const char *filename, bool openfile)
{
    static int fd = -1;
    Elf *elf = NULL;

    if (openfile) {
        fd = open(filename, O_RDONLY);
        if (fd == -1)
            return (NULL);
        elf_version(EV_CURRENT);
        elf = elf_begin(fd, ELF_C_READ, NULL);
        return (elf);
    }
    else {
        elf_end(elf);
        if (fd > 2)
            close(fd);
    }
    return (NULL);
}