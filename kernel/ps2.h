
#define COMMAND 0x64
#define DATA 0x60

void init_ps2();

unsigned char scan_code_to_char(unsigned char code);