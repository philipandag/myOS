CC := i686-elf-gcc

CFLAGS := -ffreestanding -O2 -Wall -Wextra -fno-exceptions -I include
ASMFLAGS := -f elf32
LINKFLAGS := -ffreestanding -O2 -nostdlib

C_LIB_OBJS := \
	include/tty.o \
	include/gdt.o \
	include/idt.o \
	include/mylib.o \
	include/stdio.o \
	include/stdlib.o \
	include/string.o 



ASM_LIB_OBJS := \
	include/interrupts.o

C_KERNEL_OBJS := \
	kernel/kernel.o 

ASM_KERNEL_OBJS := \
	kernel/boot.o 


C_OBJS := $(C_LIB_OBJS) $(C_KERNEL_OBJS)
ASM_OBJS := $(ASM_LIB_OBJS) $(ASM_KERNEL_OBJS)

all: iso

iso: link
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

link: $(C_OBJS) $(ASM_OBJS)
	i686-elf-gcc -T linker.ld -o myos.bin $(LINKFLAGS) $(C_OBJS) $(ASM_OBJS) -lgcc

$(C_OBJS): %.o: %.c

$(ASM_OBJS): %.o: %.asm
	nasm $(ASMFLAGS) $^

clean:
	rm -f include/*.o
	rm -f kernel/*.o
	rm -f *.bin
	rm -f *.iso
	rm -rf isodir





