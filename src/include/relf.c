#include "relf.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <endian.h>
#include <string.h>
#include <byteswap.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
  #define ELFDATANATIVE ELFDATA2LSB
#elif __BYTE_ORDER == __BIG_ENDIAN
  #define ELFDATANATIVE ELFDATA2MSB
#else
  #error "Unknown machine endian"
#endif

char e_ident[EI_NIDENT];
const char *ElfPointer; //  pointer for  ElfMap

/**
* @brief elf header
* @param [in] p_elfHeader struct for usage elf header
* @return void
*/
void ElfStruct ( struct ELF *p_elf )
{
  // ELF HEADER
  p_elf->class      = e_ident[EI_CLASS];
  p_elf->data       = e_ident[EI_DATA];
  p_elf->eversion   = e_ident[EI_VERSION];
  p_elf->osabi      = e_ident[EI_OSABI];
  p_elf->abiversion = e_ident[EI_ABIVERSION];

  memcpy ( &p_elf->type, ElfPointer + 0x10, 0x2 );
  memcpy ( &p_elf->machine, ElfPointer +  0x12, 1 );
  memcpy ( &p_elf->entry, ElfPointer   +  0x18, 4 );
  memcpy ( &p_elf->phoff, ElfPointer   +  0x20, 2 );
  memcpy ( &p_elf->shoff, ElfPointer   +  0x28, 4 );
  memcpy ( &p_elf->flags, ElfPointer   + 0x2a, 2 );
  memcpy ( &p_elf->ehsize, ElfPointer   +  0x34, 4 );
  memcpy ( &p_elf->phentsize, ElfPointer + 0x36, 4 );
  memcpy ( &p_elf->phnum, ElfPointer + 0x38, 4 );
  memcpy ( &p_elf->shentsize, ElfPointer + 0x3a, 4 );
  memcpy ( &p_elf->shnum, ElfPointer + 0x3c, 4 );
  memcpy ( &p_elf->shstrndx, ElfPointer + 0x3e, 4 );

  // verify endian
  if ( e_ident[EI_DATA] != ELFDATANATIVE )
  {
    p_elf->machine = __bswap_16 ( p_elf->machine );
    p_elf->type    = __bswap_16 ( p_elf->type );
    p_elf->shoff   = __bswap_64 ( p_elf->shoff );
    p_elf->phoff   = __bswap_64 ( p_elf->shoff );
    p_elf->shnum   = __bswap_16 ( p_elf->shnum );
    p_elf->shstrndx = __bswap_16 ( p_elf->shstrndx );
    p_elf->shentsize = __bswap_16 ( p_elf->shentsize );
    p_elf->phentsize = __bswap_16 ( p_elf->phentsize );
  }

}

/**
* @brief verify format elf for analisy
* @return bool if format elf true, return "true" else false
*/
static bool VElfMagic()
{
  bool status_exit = false;

  if ( e_ident[EI_MAG0] == 0x7f &&
       e_ident[EI_MAG1] == 0x45 &&
       e_ident[EI_MAG2] == 0x4c &&
       e_ident[EI_MAG3] == 0x46 )
    status_exit = true;

  return status_exit;
}

/**
* @brief map binary in memory to analyze ELF
* @param [in] p_path path name bin ELF for mapper
* @return int if file is found and opened, return OPEN_SUCESS, else OPEN_FAIL
* @details it will just map elf binaries, that is, it will do a check when mapping
the file checking if the file in question is an ELF format
*/
int PElf ( const char *p_path )
{
  int status_exit = OPEN_SUCESS;
  struct stat sb;

  int fd = open ( p_path, O_RDONLY );

  if ( fd != -1 )
  {
    fstat ( fd, &sb ); // get size file for mapping

    // mapper file ELF
    ElfPointer = mmap ( NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0 );

    if ( ElfPointer == MAP_FAILED )
    {
      perror ( ElfPointer );
      status_exit = ELF_INVALID;
    }
    else
    {
      // valid if is format ELF
      if ( sb.st_size > EI_NIDENT )
      {
        memcpy ( e_ident, ElfPointer, EI_NIDENT );

        if ( VElfMagic() == true ) // elf valid
          status_exit = ELF_VALID;
      }
    }

    // close file
    close ( fd );
  }
  else
    perror ( p_path ), status_exit = OPEN_FAIL;


  return status_exit;
}

/**
* @brief get pointer e_ident elf
* @return char*
* @details limit EI_NIDENT
*/
char *ElfMagic()
{
  return e_ident;
}
