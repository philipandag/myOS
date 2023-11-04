
CFLAGS=-g --freestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
LINKERFLAGS=-ffreestanding -O2 -nostdlib
LIBRARIES=mylib.c stdio.c stdlib.c

OBJECTFILES=boot.o kernel.o mylib.o stdio.o stdlib.o

boot: boot.asm
	nasm -felf32 boot.asm -o boot.o
	
kernel: kernel.o
	i686-elf-gcc -c kernel.c -o kernel.0

link: $(OBJECTFILES)
	i686-elf-gcc -T linker.ld -0 myos.bin $(LINKERFLAGS) $(OBJECTFILES) -lgcc

