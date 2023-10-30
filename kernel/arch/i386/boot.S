# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot 

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bss

# Reserve space for GDT
.align 16
GDT_start:
.skip 64*5
GDT_end:

# Reserve a stack for the initial thread.
.align 16
stack_bottom:
.skip 16*1024 # 16 KiB
stack_top:

# The kernel entry point.

.section .text
.global _start
.type _start, @function
_start:
	# set the stack pointer
	mov $stack_top, %esp

	# Create GDT 
	push $GDT_start
	call GDTCreate

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	push $GDT_start
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
