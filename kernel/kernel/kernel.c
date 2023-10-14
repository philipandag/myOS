#include <stdio.h>
#include <stdlib.h>
#include <mylib.h>

#include <kernel/tty.h>

void kernel_main(void){
    terminal_initialize();

    for(int i = 0; i < 1000; i++)
    {
        printf("%d: Hello, kernel World!\n", i);
        waitTicks(1000000000);
    }
}