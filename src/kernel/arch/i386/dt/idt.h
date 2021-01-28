#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed)) idt_gate_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

idt_gate_t IDT[256];
idt_register_t idt_reg;


void set_idt_gate(int n, uint32_t handler);
void set_idt();


#define low_16(address) (uint16_t)((address) & 0xffff)
#define high_16(address) (uint16_t)((address >> 16) & 0xffff)

#endif
