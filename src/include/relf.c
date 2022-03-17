#include "relf.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>

char e_ident[EI_NIDENT];

/**
* @brief elf header
* @param [in] p_elfHeader struct for usage elf header
* @return void
*/
void IElf(struct I_ELF *p_elfHeader)
{
	p_elfHeader->class      = e_ident[EI_CLASS];
	p_elfHeader->data       = e_ident[EI_DATA];
	p_elfHeader->version    = e_ident[EI_VERSION];
	p_elfHeader->osabi      = e_ident[EI_OSABI];
	p_elfHeader->abiversion = e_ident[EI_ABIVERSION];
}

/**
* @brief verify format elf for analisy
* @return bool if format elf true, return "true" else false
*/
static bool VElfMagic()
{
	bool status_exit = false;

	if( e_ident[EI_MAG0] == 0x7f &&
		e_ident[EI_MAG1] == 'E' &&
		e_ident[EI_MAG2] == 'L' &&
		e_ident[EI_MAG3] == 'F')
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
		const char *map = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if(map == MAP_FAILED)
		{
			perror(map);
			status_exit = ELF_INVALID;
		}else
		{
			// valid if is format ELF
			if(sb.st_size > EI_NIDENT)
			{
					strncpy(e_ident, map, EI_NIDENT);
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
char* ptrElfMagic()
{
	return e_ident;
}
