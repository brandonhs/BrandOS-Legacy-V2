#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#define KBD_LAYOUT_US 1
#define BUF_SIZE    512

#define KEY_DOWN 1
#define KEY_UP   0

#include <stdint.h>

typedef struct {
    uint8_t caps_lock, shift; /* shift and caps key states */
    uint8_t ctrl, alt; /* ctrl and alt states */
} kbd_flags_t;

void keyboard_initialize();
unsigned char keyboard_read();
void print_buf();

#endif
