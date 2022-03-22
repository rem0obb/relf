#include "relf.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <endian.h>
#include <string.h>

char e_ident[EI_NIDENT];
const char *ElfPointer; //  pointer for  ElfMap

/**
* @brief elf header
* @param [in] p_elfHeader struct for usage elf header
* @return void
*/
void ElfStruct(struct ELF *p_elf)
{
	// ELF HEADER
	p_elf->class      = e_ident[EI_CLASS];
	p_elf->data       = e_ident[EI_DATA];
	p_elf->eversion   = e_ident[EI_VERSION];
	p_elf->osabi      = e_ident[EI_OSABI];
	p_elf->abiversion = e_ident[EI_ABIVERSION];

	memcpy(&p_elf->type, ElfPointer+16, 0x2);
	memcpy(&p_elf->machine, ElfPointer+(EI_NIDENT+0x1), 2);
	memcpy(&p_elf->entry, ElfPointer+(EI_NIDENT+0x8), 4);
	memcpy(&p_elf->phoff, ElfPointer+(EI_NIDENT+0x10), 2);
	memcpy(&p_elf->shoff, ElfPointer+(EI_NIDENT+0x18), 4);

// swap bit data
#if BYTE_ORDER == LITTLE_ENDIAN
	// big endian
	if(e_ident[EI_DATA] == ELFDATA2LSB)
	{
		p_elf->machine =  __bswap_16(p_elf->machine);
	}
#else
	if(e_ident[EI_DATA] == ELFDATA2MSB)
	{
		p_elf->machine =  __bswap_16(p_elf->machine);
		p_elf->type =  __bswap_16(p_elf->type);
	}
#endif


}

/**
* @brief verify format elf for analisy
* @return bool if format elf true, return "true" else false
*/
static bool VElfMagic()
{
	bool status_exit = false;

	if( e_ident[EI_MAG0] == 0x7f &&
		e_ident[EI_MAG1] == 0x45 &&
		e_ident[EI_MAG2] == 0x4c &&
		e_ident[EI_MAG3] == 0x46)
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
int PElf(const char* p_path)
{
	int status_exit = OPEN_SUCESS;
	struct stat sb;

	int fd = open(p_path, O_RDONLY);
	if(fd != -1)
	{
		fstat(fd, &sb); // get size file for mapping

		// mapper file ELF
		ElfPointer = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if(ElfPointer == MAP_FAILED)
		{
			perror(ElfPointer);
			status_exit = ELF_INVALID;
		}else
		{
			// valid if is format ELF
			if(sb.st_size > EI_NIDENT)
			{
					memcpy(e_ident, ElfPointer, EI_NIDENT);
					if(VElfMagic() == true) // elf valid
							status_exit = ELF_VALID;
			}
		}

		// close file
		close(fd);
	}else
		perror(p_path), status_exit = OPEN_FAIL;


	return status_exit;
}

/**
* @brief get pointer e_ident elf
* @return char*
* @details limit EI_NIDENT
*/
char* ElfMagic()
{
	return e_ident;
}
