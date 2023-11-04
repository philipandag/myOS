#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void){
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    for(size_t y = 0; y < VGA_HEIGHT; y++)
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
}

void terminal_setcolor(uint8_t color){
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y){
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_clearline(size_t row){
    uint16_t empty = vga_entry(' ', terminal_color);
    for(size_t index = 0; index < VGA_WIDTH; index++)
        terminal_buffer[(row)*VGA_WIDTH + index] = empty;
}

void terminal_scroll(){
    //copy whole terminal buffer one line up
    memmove(&terminal_buffer[0], &terminal_buffer[VGA_WIDTH], VGA_WIDTH*sizeof(uint16_t)*(VGA_HEIGHT-1));
    terminal_clearline(VGA_HEIGHT-1);
}

void terminal_newline(void)
{
    if(++terminal_row == VGA_HEIGHT)
    {
        terminal_scroll();
        terminal_row = VGA_HEIGHT - 1;
    }
    terminal_column = 0;
}

void terminal_delete_last_line(void){
    size_t x, *ptr;

    for(x = 0; x < VGA_WIDTH * 2; x++)
    {
        ptr = (size_t*)terminal_buffer + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
        *ptr = 0;
    }
}

void terminal_putchar(char c){
    unsigned char uc = c;

    if(uc == '\n')
    {
        terminal_newline();
        return;
    }

    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    if(++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_newline();
    }
}

void terminal_write(const char* data, size_t size){
    for(size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* string){
    terminal_write(string, strlen(string));
}
