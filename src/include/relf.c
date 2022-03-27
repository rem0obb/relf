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

const char *ElfPointer; //  pointer for  ElfMap
Elf64_Ehdr *elf64Header; // elf header 64
Elf32_Ehdr *elf32Header; // elf header 32

/**
* @brief elf header
* @param [in] p_elf64Header struct for usage elf header
* @return void
*/
void ElfStruct ( struct SELF *p_elf )
{
  if ( elf64Header->e_ident[EI_CLASS] == ELFCLASS32 ){
    p_elf->elf32Header = elf32Header;
    p_elf->classElf = ELFCLASS32;
  }else{
    p_elf->elf64Header = elf64Header;
    p_elf->classElf = ELFCLASS64;
  }
  // verify endian
  if ( elf64Header->e_ident[EI_DATA] != ELFDATANATIVE )
  {     
    
  }
  
}

/**
* @brief verify format elf for analisy
* @return bool if format elf true, return "true" else false
*/
static bool VElfMagic()
{
  bool status_exit = false;

  if ( elf64Header->e_ident[EI_MAG0] == 0x7f &&
       elf64Header->e_ident[EI_MAG1] == 0x45 &&
       elf64Header->e_ident[EI_MAG2] == 0x4c &&
       elf64Header->e_ident[EI_MAG3] == 0x46 )
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
      elf64Header = ( Elf64_Ehdr * ) ElfPointer;
      if(elf64Header->e_ident[EI_CLASS] == ELFCLASS32)
          elf32Header = (Elf32_Ehdr*)elf64Header;

      if ( VElfMagic() == true ) // elf valid
        status_exit = ELF_VALID;
    }
  }
  else
    perror ( p_path ), status_exit = OPEN_FAIL;


  // close file
  close ( fd );

  return status_exit;
}


/**
* @brief get pointer e_ident elf
* @return char*
* @details limit EI_NIDENT
*/
char *ElfMagic()
{
  return elf64Header->e_ident;
}
