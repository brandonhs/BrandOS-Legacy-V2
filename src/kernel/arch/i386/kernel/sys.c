#include <kernel/sys.h>

void outb(uint16_t port, uint8_t data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint8_t inb(uint16_t port) {
    uint8_t data;
    __asm__("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}

void outw(uint16_t port, uint16_t data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

uint16_t inw(uint16_t port) {
    uint16_t data;
    __asm__("in %%dx, %%al" : "=a" (data) : "d" (port));
    return data;
}
