#include <kernel/keyboard.h>

#include <i386/dt.h>
#include <kernel/sys.h>
#include <stddef.h>
#include <stdio.h>

#define KBD_IRQ IRQ1
#define KBD_PORT_IN 0x60

unsigned char kbd_buf[BUF_SIZE];
size_t index = BUF_SIZE-1;

void kbd_callback_func(struct regs r);

#if KBD_LAYOUT_US
const char kbd[128] = {
    0,
    '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, 
    '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
#endif

void keyboard_initialize() {
    register_interrupt_handler(KBD_IRQ, kbd_callback_func);
}

void kbd_callback_func(struct regs r) {
    unsigned char sc = inb(KBD_PORT_IN);
    unsigned char c  = kbd[sc];
    if (sc & 0x80)
        c = 0;
    else {
        kbd_buf[index] = c;
        if (index != 0) index--;
        else index = BUF_SIZE-1;
    }
}

unsigned char keyboard_read() {
    if (index < BUF_SIZE-1 && kbd_buf[index+1] != 0) {
        char a = kbd_buf[++index];
        return a;
    }
    return 0;
}

void print_buf() {
    puts(kbd_buf);
}
