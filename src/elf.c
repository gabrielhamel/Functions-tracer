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

char *find_symname(Elf *elf, long addr)
{
    Elf_Scn *scn = NULL;
    GElf_Shdr shdr;
    Elf_Data *data = NULL;
    GElf_Sym sym;
    char *ptr;

    while ((scn = elf_nextscn(elf, scn)) != NULL) {
        gelf_getshdr(scn, &shdr);
        if (shdr.sh_entsize != 0) {//shdr.sh_type == SHT_SYMTAB) {//(SHT_DYNSYM | SHT_RELA | SHT_STRTAB | SHT_SYMTAB)) {
            data = elf_getdata(scn, NULL);
            for (size_t i = 0; i < shdr.sh_size / shdr.sh_entsize; i++) {
                gelf_getsym(data, i, &sym);
                if ((Elf64_Addr)addr == sym.st_value && sym.st_name) {
                    ptr = elf_strptr(elf, shdr.sh_link, sym.st_name);
                    if (ptr && strlen(ptr))
                        return (ptr);
                }
            }
        }
    }
    return (NULL);
}