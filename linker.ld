/* entry point of the kernel */
ENTRY(_start)

/* where to put sections of object files in final binary */

SECTIONS
{
    /* 1MB of offset from beginning, conventions */
    /* "." means adress where we are at currently
    setting it at 1M */
    . = 1M;

    /* first .text section with code which
    will contain miltiboot header for bootloader to find
    and only then the actual code */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* Read only data section after the code */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* RW data initialized (zeroed?) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* RW data not initialized (full of trash?)*/\
    /* at the beginning we also put COMMON there which
    means anything not contained inside a section will 
    be at the beginning of .bss of the output binary
    */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

    /* The compiler may produce some other sections and
    by default it will just add another section to the
    output file, if we want to avoid it we need to
    specify those sections here */
}