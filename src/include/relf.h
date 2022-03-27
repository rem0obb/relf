/**
* @file relf.h
* @author VitorMob
* @date 13 Mar 2022
* @copyright 2022 VitorMob
* @brief simple parser for analisys binary ELF for student
*/

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <byteswap.h>
#include <elf.h>

#include "datastructs/erros.h"
#include "datastructs/structs.h"

//=================== functions usage for parser elf ===================
int PElf ( const char * );    // pass elf for analisys
void ElfStruct ( struct ELF * ); // get header information elf
char *ElfMagic();             // return pointer array magic elf

