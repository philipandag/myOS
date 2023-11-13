#ifndef PIC_H
#define PIC_H PIC_H

#define PIC1            0x20
#define PIC2            0xA0
#define PIC1_COMMAND    PIC1
#define PIC1_DATA      (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)

#define ICW1_ICW4       0x01 // indicates that icw4 will be present
#define ICW1_SINGLE     0x02 // single (cascade) mode
#define ICW1_INTERVAL4  0x04 // call address interval 4 (8)
#define ICW1_LEVEL      0x08 // level triggered (edge) mode
#define ICW1_INIT       0x10 // initialization - required!

#define ICW4_8086       0x01 // 8086/88 (MCS-80/85) mode
#define ICW4_AUTO       0x02 // auto (normal) EOI
#define ICW4_BUF_SLAVE  0X08 // buffered mode/slave
#define ICW4_BUF_MASTER 0X0C // buffered mode/master
#define ICW4_SFNM       0X10 // special fully nested (not)

#define PIC_READ_IRR                0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR                0x0b    /* OCW3 irq service next CMD read */

#include <stdint.h>

void PIC_remap(int offsetMaster, int offsetSlave);
void PIC_disable();
void PIC_set_mask(unsigned char IRQLine);
void PIC_clear_mask(unsigned char IRQLine);

uint16_t pic_get_irr();
uint16_t pic_get_isr();

extern int IRQ1_Offset;
extern int IRQ2_Offset;

#endif