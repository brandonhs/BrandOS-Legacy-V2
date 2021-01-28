#include <kernel/tty.h>
#include <kernel/sys.h>

#include <string.h>

#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t tty_col, tty_row;
static uint8_t tty_color;
static uint16_t* tty_buffer;

void tty_initialize(void) {
    tty_row = 0;
	tty_col = 0;
	tty_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	tty_buffer = VGA_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
}


void tty_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	tty_buffer[index] = vga_entry(c, color);
}


void tty_setcolor(uint8_t color) {
	tty_color = color;
}

void tty_putchar(char c) {
    unsigned char uc = c;
	if (uc == '\n') tty_newline();
	else {
		tty_putentryat(uc, tty_color, tty_col, tty_row);
		if (++tty_col == VGA_WIDTH) {
			tty_newline();
        }
	}
	if (tty_row == VGA_HEIGHT) {
		--tty_row;
		tty_scroll();
	}
	tty_update_cursor();
}

void tty_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++)
		tty_putchar(data[i]);
}

void tty_writestring(const char* data) {
    tty_write(data, strlen(data));
}


void tty_set_cursor(size_t col, size_t row) {
    uint16_t offset = row * VGA_WIDTH + col;
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (offset & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((offset >> 8) & 0xFF));
}

void tty_update_cursor() {
    tty_set_cursor(tty_col, tty_row);
}

void tty_newline() {
    tty_row++;
	tty_col=0;
    tty_update_cursor();
}

void tty_scroll() {
	for (size_t i = 1; i <= VGA_HEIGHT; i++) {
		tty_vga_memcpy(i-1, i);
	}
}

int get_offset(int col, int row) {
    return row * VGA_WIDTH + col;
}

void tty_vga_memcpy(size_t dstrow, size_t srcrow) {
    if (srcrow == dstrow) return; // dont waste time if source == dest
    else if (srcrow > VGA_WIDTH || dstrow > VGA_HEIGHT) return; // we dont want to write to non vga memory

    unsigned short num_bytes = VGA_WIDTH*2;

    uint16_t *source_mem = (uint16_t*)(VGA_MEMORY + get_offset(0, srcrow));
    uint16_t *dest_mem = (uint16_t*)(VGA_MEMORY + get_offset(0, dstrow));

    memcpy(dest_mem, source_mem, num_bytes);
}
