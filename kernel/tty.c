#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <vga.h>
#include <tty.h>


enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}


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

void terminal_move_cursor(int column, int row)
{
	uint16_t pos = row * VGA_WIDTH + column;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_update_cursor(){
    terminal_move_cursor(terminal_column, terminal_row);
}

void terminal_setcolor(uint8_t color){
    terminal_color = color;
}

void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y){
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

char terminal_character_at(size_t column, size_t row)
{
    return (char)terminal_buffer[column + VGA_WIDTH * row];
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
    terminal_update_cursor();
}

void terminal_delete_last_line(void){
    size_t x, *ptr;

    for(x = 0; x < VGA_WIDTH * 2; x++)
    {
        ptr = (size_t*)terminal_buffer + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
        *ptr = 0;
    }
}

void terminal_tab(){
    do
    {
        terminal_putchar(' ');
    }while(terminal_column % 4 != 0);
    terminal_update_cursor();
}

void terminal_backspace(){

    if(terminal_column == 0)
    {
        if(terminal_row != 0){
            terminal_row--;
            terminal_column = VGA_WIDTH-1;
            
            while(terminal_character_at(terminal_column-1, terminal_row) == ' ' && terminal_column != 0){
                terminal_column--;
            }
            
        }
    }
    else{
     terminal_column --; 
    }

    terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
    terminal_update_cursor();
    return;
}

void terminal_putchar(char c){
    unsigned char uc = c;

    switch(uc)
    {
        case '\n':{
            terminal_newline();
            break;
        }
        case '\0':{
            break;
        }
        case '\b':{
            terminal_backspace();
            break;
        }
        case '\t':{
            terminal_tab();
            break;
        }
        default:{
            terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
            if(++terminal_column == VGA_WIDTH)
            {
                terminal_column = 0;
                terminal_newline();
            }
            terminal_update_cursor();
        }

    }

}

void terminal_write(const char* data, size_t size){
    for(size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* string){
    terminal_write(string, strlen(string));
}

void terminal_writestring_at(const char* string, int column, int row)
{
    int x = terminal_column;
    int y = terminal_row;

    terminal_column = column;
    terminal_row = row;
    terminal_writestring(string);
    terminal_column = x;
    terminal_row = y;
    terminal_move_cursor(x, y);
}