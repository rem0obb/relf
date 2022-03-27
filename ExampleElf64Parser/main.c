/**
*  @brief example usage library relf.h
*/

#include "../src/include/relf.h"
#include <stdio.h>
#include <stdlib.h>


int main ( int argc, char *argv[] )
{
  struct SELF relf;

  if ( PElf ( argv[1] ) == ELF_VALID )
  {
    ElfStruct ( &relf ); // get 16 bytes infos

    if ( relf.classElf == ELFCLASS64 )
    {
      puts ( "Elf Header :" );

      // magic header elf
      printf ( " Magic:" );

      for ( int8_t i = 0; i < EI_NIDENT ; i++ )
        printf ( " %02x", ElfMagic() [i] );

      puts ( "" ); // \n

      if ( relf.elf64Header->e_version == EV_CURRENT )
        printf ( " Version: %i (Current)\n", relf.elf64Header->e_version );
      else
        printf ( " Version: %i \n", relf.elf64Header->e_version );

      printf ( " Entry Point: 0x%x\n", relf.elf64Header->e_entry );
      printf ( " Start of program headers: %lu\n", relf.elf64Header->e_phoff );
      printf ( " Start of section headers: %lu\n", relf.elf64Header->e_shoff );
      printf ( " Abi Version: 0x%x\n", relf.elf64Header->e_ident[EI_ABIVERSION] );
      printf ( " Flags : 0x%x\n", relf.elf64Header->e_flags );
      printf ( " Size of this header: %i\n", relf.elf64Header->e_ehsize );
      printf ( " Size of program headers: %i\n", relf.elf64Header->e_phentsize );
      printf ( " Number of program headers: %i\n", relf.elf64Header->e_phnum );
      printf ( " Size of section headers: %i\n", relf.elf64Header->e_shentsize );
      printf ( " Number of section headers: %i\n", relf.elf64Header->e_shnum );
      printf ( " Section header string table index: %i\n", relf.elf64Header->e_shstrndx );

      if ( relf.elf64Header->e_ident[EI_CLASS] == ELFCLASS64 )
        puts ( " Class: ELF64" );

      // big endian or little endian
      switch ( relf.elf64Header->e_ident[EI_DATA] )
      {
        case ELFDATA2MSB:
          puts ( " Data: Big endian" );
          break;

        case ELFDATA2LSB:
          puts ( " Data: Little endian" );
          break;

        default:
          puts ( " Data: unknown" );
      }

      switch ( relf.elf64Header->e_ident[EI_OSABI] )
      {
        case ELFOSABI_HPUX:
          puts ( " Os/Abi: Hewlett-Packard HP-UX" );
          break;

        case ELFOSABI_NETBSD:
          puts ( " Os/Abi: NetBSD" );
          break;

        case ELFOSABI_LINUX:
          puts ( " Os/Abi: Linux" );
          break;

        case ELFOSABI_SOLARIS:
          puts ( " Os/Abi: Sun Solaris" );
          break;

        case ELFOSABI_AIX:
          puts ( " Os/Abi: AIX" );
          break;

        case ELFOSABI_IRIX:
          puts ( " Os/Abi: IRIX" );
          break;

        case ELFOSABI_FREEBSD:
          puts ( " Os/Abi: Free BSD" );
          break;

        case  ELFOSABI_TRU64:
          puts ( " Os/Abi: Compaq TRU64 UNIX" );
          break;

        case ELFOSABI_MODESTO:
          puts ( " Os/Abi: Novell Modesto" );
          break;

        case ELFOSABI_OPENBSD:
          puts ( " Os/Abi: Open BSD" );
          break;

        case ELFOSABI_SYSV:
          puts ( " Os/Abi: Unix - System V" );
          break;

        default:
          puts ( " Os/Abi: unknown" );

      }

      switch ( relf.elf64Header->e_type )
      {
        case ET_REL:
          puts ( " Type: Relocatable file" );
          break;

        case ET_EXEC:
          puts ( " Type: Executable file" );
          break;

        case ET_DYN:
          puts ( " Type: Shared object file" );
          break;

        case ET_CORE:
          puts ( " Type: Core file" );
          break;

        case ET_HIOS:
        case ET_LOOS:
          puts ( " Type: Operating system-specific" );
          break;

        case ET_LOPROC:
        case ET_HIPROC:
          puts ( " Type: Processor-specific" );
          break;

        default:
          puts ( " Type: unknown" );

      }

      switch ( relf.elf64Header->e_machine )
      {
        case EM_M32:
          puts ( " Machine: AT&T WE 32100" );
          break;

        case EM_SPARC:
          puts ( " Machine: SPARC" );
          break;

        case EM_PPC64:
          puts ( " Machine: 64-bit PowerPC" );
          break;

        case EM_X86_64:
          puts ( " Machine: x86-64 Architecture" );
          break;

        case EM_386:
          puts ( " Machine: x86-32 Architecture" );
          break;

        case EM_ARM:
          puts ( " Machine: Advanced RISC Machines ARM" );
          break;

        case EF_MIPS_FP64:
        case EM_MIPS:
          puts ( " Machine: MIPS Architecture" );
          break;

        default:
          puts ( " Machine: unknown" );
      }
    }
    else
      fprintf ( stderr, "%s: elf class 32-bits, parser support elf 64-bits\n", argv[0] );
  }
  else
    fprintf ( stderr, "%s:  formatted doesn't look like an elf \n", argv[0] );


  return 0;
}
