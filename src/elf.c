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
#include <string.h>

static char *get_sym(Elf *elf, GElf_Shdr *shdr, Elf_Data *data, long addr)
{
    char *ptr;
    GElf_Sym sym;

    for (size_t i = 0; i < shdr->sh_size / shdr->sh_entsize; i++) {
        gelf_getsym(data, i, &sym);
        if ((Elf64_Addr)addr == sym.st_value && sym.st_name) {
            ptr = elf_strptr(elf, shdr->sh_link, sym.st_name);
            if (ptr && strlen(ptr))
                return (ptr);
        }
    }
    return (NULL);
}

char *find_symname(Elf *elf, long addr)
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    Elf_Data *data = NULL;
    char *tmp;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_entsize != 0) {
            data = elf_getdata(scn, NULL);
            tmp = get_sym(elf, &shdr, data, addr);
            if (tmp)
                return (tmp);
        }
    }
    return (NULL);
}