section .data

section .text

global _interrupt_ignore
global _interrupt_print_int
global _interrupt_IRQ_ignore
global _interrupt_IRQ_0
global _interrupt_IRQ_1
global _interrupt_IRQ_8
global _interrupt_13_general_protection_fault

extern terminal_putchar
extern terminal_writestring


extern __IRQ0
extern __IRQ1
extern __IRQ8
; 0-31 	Protected Mode Exceptions (Reserved by Intel) 

_interrupt_ignore:  
    ; cli
    ; pushad

    ; add byte [0xB8000], 10
    ; push 'i'
    ; call terminal_putchar
    ; add esp, 1

    ; sti
    iret

_interrupt_print_int:
    cli
    pushad

    push dword 'i'
    call terminal_putchar
    add esp, 4
    
    push dword 'n'
    call terminal_putchar
    add esp, 4
    
    push dword 't'
    call terminal_putchar
    add esp, 4

    push dword 0xa
    call terminal_putchar
    add esp, 4

    popad
    sti
    iret

_interrupt_13_general_protection_fault:
    cli
    pushad

    push dword 'G'
    call terminal_putchar
    add esp, 4
    
    push dword 'P'
    call terminal_putchar
    add esp, 4
    
    push dword 'F'
    call terminal_putchar
    add esp, 4

    push dword 0xa
    call terminal_putchar
    add esp, 4

    popad
    sti
    iret    

; IRQ Interrupts

; 20h & 21h 	control/mask ports of the master PIC
; A0h & A1h 	control/mask ports of the slave PIC

_interrupt_IRQ_ignore:
    cli
    pushad
    
    push dword 'Q'
    call terminal_putchar
    add esp, 4
    push dword 0xa
    call terminal_putchar
    add esp, 4
    

    mov al, 0x20
    out 0x20, al

    popad
    sti
    iret

; IRQ_0 - Programmable Interrupt Timer Interrupt
_interrupt_IRQ_0:
    cli
    pushad


    call __IRQ0

    ; notify PIC about receiving the interrupt
    mov al, 0x20
    out 0x20, al
    
    popad
    sti
    iret

    
    ;IRQ 1 	Keyboard Interrupt 
_interrupt_IRQ_1:
    cli
    pushad


    call __IRQ1

    ; notify PIC about receiving the interrupt
    mov al, 0x20
    out 0x20, al

    popad
    sti
    iret

    
    ;60h 	data port from the keyboard controller
    ;64h 	command port for keyboard controller - use to enable/disable kbd interrupts, etc. 

    ;IRQ  2 	Cascade (used internally by the two PICs. never raised) 
    ;IRQ  3 	COM2 (if enabled) 
    ;IRQ  4 	COM1 (if enabled) 
    ;IRQ  5 	LPT2 (if enabled)  
    ;IRQ  6 	Floppy Disk 
    ;IRQ  7     LPT1 / Unreliable "spurious" interrupt (usually) 
    ;IRQ  8 	CMOS real-time clock (if enabled) 
_interrupt_IRQ_8:
    cli
    pushad

    call __IRQ8

    mov al, 0x20
    out 0x20, al

    popad 
    sti
    iret

    ;IRQ  9 	Free for peripherals / legacy SCSI / NIC 
    ;IRQ  10 	Free for peripherals / SCSI / NIC
    ;IRQ  11 	Free for peripherals / SCSI / NIC
    ;IRQ  12 	PS2 Mouse
    ;IRQ  13 	FPU / Coprocessor / Inter-processor
    ;IRQ  14 	Primary ATA Hard Disk
    ;IRQ  15 	Secondary ATA Hard Disk 