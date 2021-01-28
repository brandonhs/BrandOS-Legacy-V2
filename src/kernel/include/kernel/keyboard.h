#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#define KBD_LAYOUT_US 1
#define BUF_SIZE 512

void keyboard_initialize();
unsigned char keyboard_read();
void print_buf();

#endif
