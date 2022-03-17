#include "include/relf.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	struct I_ELF elf;

	const char* path = argv[1];
	// if format elf
	if(PElf(path) == ELF_VALID)
	{
		IElf(&elf); // get 16 bytes infos

		puts("Elf Header :");

		// magic header elf
		printf(" Magic: ");
		for(int8_t i =0; i < EI_NIDENT ; i++)
			printf(" %02x", ptrElfMagic()[i]);
		puts(""); // \n

		printf(" Version: 0x%x\n", elf.version);
		printf(" Abi Version: 0x%x\n", elf.abiversion);

		// class elf 64 or 32
		switch(elf.class)
		{
			case ELFCLASS64:
				puts(" Class: ELF64");
				break;
			case ELFCLASS32:
				puts(" Class: ELF32");
				break;
			default:
				puts(" Class: Unknown");
		}

		// big endian or little endian
		switch(elf.data)
		{
			case ELFDATA2MSB:
				puts(" Data: 2's complement, Big endian");
				break;
			case ELFDATA2LSB:
				puts(" Data: 2's complement, Little endian");
				break;
			default:
				puts(" Data: unknown");
		}

		switch(elf.osabi)
		{
			case ELFOSABI_HPUX:
			 	puts(" Os/Abi: Hewlett-Packard HP-UX");
				break;
			case ELFOSABI_NETBSD:
				puts(" Os/Abi: NetBSD");
				break;
			case ELFOSABI_LINUX:
				puts(" Os/Abi: Linux");
				break;
			case ELFOSABI_SOLARIS:
				puts(" Os/Abi: Sun Solaris");
				break;
			case ELFOSABI_AIX:
				puts(" Os/Abi: AIX");
				break;
			case ELFOSABI_IRIX:
				puts(" Os/Abi: IRIX");
				break;
			case ELFOSABI_FREEBSD:
				puts(" Os/Abi: Free BSD");
				break;
			case  ELFOSABI_TRU64:
			 	puts(" Os/Abi: Compaq TRU64 UNIX");
				break;
			case ELFOSABI_MODESTO:
			 	puts(" Os/Abi: Novell Modesto");
				break;
			case ELFOSABI_OPENBSD:
				puts(" Os/Abi: Open BSD");
				break;
			case ELFOSABI_OPENVMS:
				puts(" Os/Abi: Open VMS");
				break;
			case ELFOSABI_NSK:
				puts(" Os/Abi: Hewlett-Packard Non-Stop Kernel");
				break;
			case ELFOSABI_SYSV:
				puts(" Os/Abi: Unix - System V");
				break;
			default:
				puts(" Os/Abi: unknown");

		}

	}

	return 0;
}
