#include <stdio.h>
#include <stddef.h>
#include <kernel/keyboard.h>
#include <kernel/tty.h>

unsigned char* gets(unsigned char* buf, size_t buf_len) {
    size_t line_index = 0;
    for (;;) {
		asm("hlt");
		char c = keyboard_read();
		if (c == '\n') return buf;
	    else if (c == '\b') {
			if (line_index != 0) {
				buf[--line_index] = ' ';
				tty_backspace();
			}
		} else if (c != 0) {
			buf[line_index] = c;
			printf("%c", buf[line_index]);
			line_index++;
            if (line_index >= buf_len) return buf;
		}
	}
}
