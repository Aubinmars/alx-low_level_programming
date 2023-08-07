#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void close_elf(int elf);

void close_elf(int elf)
{
    if (close(elf) == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", elf);
        exit(98);
    }
}

int main(int __attribute__((__unused__)) argc, char *argv[])
{
    Elf64_Ehdr header;
    int o, r;
    unsigned int e_type;
    unsigned long int e_entry;
    int i;

    o = open(argv[1], O_RDONLY);
    if (o == -1)
    {
        dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
        exit(98);
    }

    r = read(o, &header, sizeof(Elf64_Ehdr));
    if (r == -1)
    {
        close_elf(o);
        dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
        exit(98);
    }

    if (header.e_ident[EI_MAG0] != 0x7f ||
        header.e_ident[EI_MAG1] != 'E' ||
        header.e_ident[EI_MAG2] != 'L' ||
        header.e_ident[EI_MAG3] != 'F')
    {
        dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
        close_elf(o);
        exit(98);
    }

    printf("ELF Header:\n");
    printf(" Magic: ");
    for (i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x", header.e_ident[i]);
        if (i == EI_NIDENT - 1)
            printf("\n");
        else
            printf(" ");
    }

    printf(" Class: ");
    switch (header.e_ident[EI_CLASS])
    {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", header.e_ident[EI_CLASS]);
    }

    printf(" Data: ");
    switch (header.e_ident[EI_DATA])
    {
        case ELFDATANONE:
            printf("none\n");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", header.e_ident[EI_CLASS]);
    }

    printf(" Version: %d", header.e_ident[EI_VERSION]);
    switch (header.e_ident[EI_VERSION])
    {
        case EV_CURRENT:
            printf(" (current)\n");
            break;
        default:
            printf("\n");
            break;
    }

    printf(" OS/ABI: ");
    switch (header.e_ident[EI_OSABI])
    {
        case ELFOSABI_NONE:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("UNIX - HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("UNIX - NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("UNIX - Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        case ELFOSABI_IRIX:
            printf("UNIX - IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("UNIX - FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("UNIX - TRU64\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Standalone App\n");
            break;
        default:
            printf("<unknown: %x>\n", header.e_ident[EI_OSABI]);
    }

    printf(" ABI Version: %d\n", header.e_ident[EI_ABIVERSION]);

    printf(" Type: ");
    e_type = header.e_type;
    if (header.e_ident[EI_DATA] == ELFDATA2MSB)
        e_type >>= 8;

    switch (e_type)
    {
        case ET_NONE:
            printf("NONE (None)\n");
            break;
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %x>\n", e_type);
    }

    printf(" Entry point address: ");
    e_entry = header.e_entry;
    if (header.e_ident[EI_DATA] == ELFDATA2MSB)
    {
        e_entry = ((e_entry << 8) & 0xFF00FF00) |
                  ((e_entry >> 8) & 0xFF00FF);
        e_entry = (e_entry << 16) | (e_entry >> 16);
    }

    if (header.e_ident[EI_CLASS] == ELFCLASS32)
        printf("%#x\n", (unsigned int)e_entry);
    else
        printf("%#lx\n", e_entry);

    close_elf(o);
    return (0);
}
