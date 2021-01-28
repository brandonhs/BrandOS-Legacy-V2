#include "idt.h"


void set_idt_gate(int n, uint32_t handler) {
    IDT[n].offset_low = low_16(handler);
    IDT[n].selector = 0x08;
    IDT[n].zero = 0;
    IDT[n].flags = 0x8e;
    IDT[n].offset_high = high_16(handler);
}

void set_idt() {
    idt_reg.base = (uint32_t) &IDT;
    idt_reg.limit = 256 * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg)); // load idt
}
