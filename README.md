# relf
lib for simple Parser Format ELF, 
a lib that makes an elf32 and elf64 format parser

# Usage lib
```C
...
 struct SELF elf;
 ...
 PELF("/to/path/bin.elf");
 ...
 ElfStruct(&elf);
 if(elf->elfClass == ELFCLASS64)
   ...
   printf("Entry Point -> %x", elf->elf64Header->e_entry);
   ...
 else
   printf("Entry Point -> %x", elf->elf32Header->e_entry);
   ...
```
# Infos

is parser this parser is just a project I'm keeping to 
study elf format, the features for now are elf header

# Compile Example

* mkdir build
* cd build
* cmake ..
* make 
