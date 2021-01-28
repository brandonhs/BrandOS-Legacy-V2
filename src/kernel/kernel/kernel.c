#include <kernel/tty.h>
#include <i386/dt.h>
#include <kernel/sys.h>

#include <kernel/keyboard.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kmain(void) {
	tty_initialize();
	gdt_install();
	isr_install();

	asm volatile("sti");
	keyboard_initialize();

	size_t line_index = 0;
	char line_buf[256];
	printf("> ");

	while (1) {
		asm("hlt");
		char c = keyboard_read();
		if (c == '\n') {
			tty_newline();
			//printf("You typed: %s\n", line_buf);
			if (strcmp(line_buf, "abort")) {
				printf("abort");
			}
			printf("> ");
			memset(line_buf, 0, strlen(line_buf));
			line_index = 0;
		} else if (c != 0) {
			line_buf[line_index] = c;
			printf("%c", line_buf[line_index]);
			line_index++;
		}
	}

	return;
}
