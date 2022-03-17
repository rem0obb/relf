/**
* @file relf.h
* @author VitorMob
* @date 13 Mar 2022
* @copyright 2022 VitorMob
* @brief simple parser for analisys binary ELF
*/

#pragma once

#include <stdio.h>
#include <stdint.h>
#include "datastructs/erros.h"
#include "datastructs/structs.h"

// =================== elf_ident 16 bytes ===================
#define EI_NIDENT 16 // 16 bytes e_ident[]

#define EI_MAG0 0    // [0x7f]
#define EI_MAG1 1    // [E]
#define EI_MAG2 2    // [L]
#define EI_MAG3 3    // [F]

#define EI_CLASS 4   //  identification class elf
#define ELFCLASS32 1
#define ELFCLASS64 2

#define EI_DATA  5    // little endian or big endian
#define ELFDATA2LSB 1 // big endian
#define ELFDATA2MSB 2 // little endian

#define EI_VERSION 6        // version elf

#define EI_OSABI 7          // os abi
#define ELFOSABI_HPUX 	 1  // Hewlett-Packard HP-UX
#define ELFOSABI_NETBSD  2  // NetBSD
#define ELFOSABI_LINUX 	 3  // Linux
#define ELFOSABI_SOLARIS 6  // Sun Solaris
#define ELFOSABI_AIX 	 7  // AIX
#define ELFOSABI_IRIX 	 8  // IRIX
#define ELFOSABI_FREEBSD 9  // FreeBSD
#define ELFOSABI_TRU64 	 10 // Compaq TRU64 UNIX
#define ELFOSABI_MODESTO 11 // Novell Modesto
#define ELFOSABI_OPENBSD 12 // Open BSD
#define ELFOSABI_OPENVMS 13 // Open VMS
#define ELFOSABI_NSK 	 14 // Hewlett-Packard Non-Stop Kernel
#define ELFOSABI_SYSV    0  // System V

#define EI_ABIVERSION 8 // version os abi
#define EI_PAD 9

//=================== functions usage for parser elf ===================
int PElf(const char*); // pass elf for analisys
void IElf(struct I_ELF *); // get header information elf
char* ptrElfMagic(); // return pointer array magic elf
