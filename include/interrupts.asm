section .data

section .text

global _interrupt_ignore
global _interrupt_print_int

extern terminal_putchar
extern terminal_writestring

_irq_end_interrupt:
    push eax
    mov al, 0x20
    out 0x20, al
    pop eax
    ret

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
_interrupt_IRQ_0:
    cli
    pushad


    push dword 'I'
    call terminal_putchar
    add esp, 4
    push dword 'R'
    call terminal_putchar
    add esp, 4
    push dword 'Q'
    call terminal_putchar
    add esp, 4
    push dword '0'
    call terminal_putchar
    add esp, 4
    push dword 0xa
    call terminal_putchar
    add esp, 4
    

    call _irq_end_interrupt
    
    popad
    sti
    iret

    
