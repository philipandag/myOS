section .data

section .text
global _interrupt_ignore
extern terminal_writestring
align 4
_interrupt_ignore:
    cli
    pushad
    
    mov al,20h
    out 20h,al

    ; push byte 0
    ; push byte 0xa ; newline
    ; push byte 't'
    ; push byte 'p'
    ; push byte 'u'
    ; push byte 'r'
    ; push byte 'r'
    ; push byte 'e'
    ; push byte 't'
    ; push byte 'n'
    ; push byte 'i'
    ; call terminal_writestring
    ; add esp, 11

    

    popad
    sti
    iret
