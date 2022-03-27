// =================== structs for usage elf64 or elf32 ===================
struct ELF
{
  char      class,
            data,
            eversion,
            osabi,
            abiversion;

  uint16_t  type,
            machine,
            ehsize,
            phentsize,
            phnum,
            shentsize,
            shnum,
            shstrndx;

  uint32_t  version,
            flags;

  uint64_t  entry,
            phoff,
            shoff;
};
