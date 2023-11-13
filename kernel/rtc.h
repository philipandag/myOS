#include <io.h>
#include <pic.h>

#define BCD2BIN(bcd) ((((bcd)&15) + ((bcd)>>4)*10))
// rtc cmos saves time in bcf format

void init_rtc();