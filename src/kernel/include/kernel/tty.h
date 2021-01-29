#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void tty_initialize(void);

void tty_setcolor(uint8_t color);
void tty_putchar(char c);
void tty_write(const char* data, size_t size);
void tty_writestring(const char* data);

void tty_set_cursor(size_t col, size_t row);
void tty_update_cursor();
void tty_newline();
void tty_vga_memcpy(size_t dstrow, size_t srcrow);
void tty_scroll();

void tty_backspace();

#endif
