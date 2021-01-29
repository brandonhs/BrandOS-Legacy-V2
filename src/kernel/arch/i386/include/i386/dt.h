#ifndef _ARCH_I386_DT_H
#define _ARCH_I386_DT_H

#include <stdint.h>

// typedef struct {
//    uint32_t ds;
//    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
//    uint32_t int_no, err_code;
//    uint32_t eip, cs, eflags, useresp, ss;
// } registers_t;

#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

void gdt_install();
// void idt_install();
void isr_install();


/* TODO: FIX STACK ISSUES */
struct regs {
    uint32_t gs, fs, es, ds;      /* pushed the segs last */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    uint32_t err_code, int_no;    /* our 'push byte #' and ecodes do this */
    uint32_t eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

typedef void (*isr_t)(struct regs); // define isr_t type as a callback function with registers_t as a parameter
void register_interrupt_handler(uint8_t n, isr_t handler);
void unregister_interrupt_handler(uint8_t n);

#endif /* _ARCH_I386_DT_H */
