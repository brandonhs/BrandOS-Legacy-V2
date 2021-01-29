#include <kernel/keyboard.h>

#include <i386/dt.h>
#include <kernel/sys.h>
#include <stddef.h>
#include <stdio.h>

#define KBD_IRQ IRQ1
#define KBD_PORT_IN 0x60

unsigned char kbd_buf[BUF_SIZE];
size_t index = BUF_SIZE-1;

kbd_flags_t kbd_flags;

void kbd_callback_func(struct regs r);

#if KBD_LAYOUT_US
const char kbd[128] = {
    0,
    '\e', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 
    0, /* ctrl */
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, /* shift */
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, /* caps lock */ 
    '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
const char kbd_sh[128] = {
    0,
    '\e', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', 
    0, /* ctrl */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, /* shift */
    '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 
    0, /* right shift */ 
    '*', 
    0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-', 0, 0, 0, '+', 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};
#define CTRL_KEY 29
#define LSHIFT_KEY 42
#define RSHIFT_KEY 54
#endif

void keyboard_initialize() {
    register_interrupt_handler(KBD_IRQ, kbd_callback_func);
}

void kbd_callback_func(struct regs r) {
    unsigned char sc = inb(KBD_PORT_IN);
    unsigned char c  = kbd[sc];
    if (sc & 0x80) {
        c = 0;
        if (sc-0x80 == LSHIFT_KEY || sc-0x80 == RSHIFT_KEY) {
            kbd_flags.shift = KEY_UP;
        }
    }
    else {
        if (sc == LSHIFT_KEY || sc == RSHIFT_KEY) {
            kbd_flags.shift = KEY_DOWN;
        } else {
            if (kbd_flags.shift == KEY_DOWN) {
                c = kbd_sh[sc];
            }
            kbd_buf[index] = c;
            if (index != 0) index--;
            else index = BUF_SIZE-1;
        }
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
