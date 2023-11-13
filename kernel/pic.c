#include <pic.h>
#include <stdint.h>
#include <io.h>

void PIC_remap(int offsetMaster, int offsetSlave)
{
    unsigned char a1, a2;

    asm("cli");

    // save masks
    a1 = inb(PIC1_COMMAND);
    a2 = inb(PIC2_COMMAND);

    // ICW1 - start the initialization sequence
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);

    // ICW2 - setting vector offsets
    outb(PIC1_DATA, offsetMaster);
    outb(PIC2_DATA, offsetSlave);

    // ICW3 - tell the master pic that theres a slave at irq2
    outb(PIC1_DATA, 0x4);
    // ICW3 - tell the slave pic its cascade identity
    outb(PIC2_DATA, 0x2);

    // ICw4 - tell the PICs to use 8086 mode (default is 8080)
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    // restoring masks
    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);

    asm("sti");

}

void PIC_disable()
{
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}

void PIC_set_mask(unsigned char IRQLine)
{
    uint16_t port;
    uint8_t value;

    if(IRQLine < 8){
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQLine -= 8;
    }

    value = inb(port) | (1 << IRQLine);
    outb(port, value);
}

void PIC_clear_mask(unsigned char IRQLine)
{
    uint16_t port;
    uint8_t value;

    if(IRQLine < 8){
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQLine -= 8;
    }

    value = inb(port) & ~(1 << IRQLine);
    outb(port, value);
}


 
/* Helper func */
static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t pic_get_irr()
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t pic_get_isr()
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}