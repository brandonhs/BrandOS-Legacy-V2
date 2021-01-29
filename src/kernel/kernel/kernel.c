#include <kernel/tty.h>
#include <kernel/sys.h>

#include <kernel/keyboard.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __i386
#include <i386/dt.h>
#include <i386/vga.h>
#endif

int kmain(void) {
	tty_initialize();
	gdt_install();
	isr_install();

	asm volatile("sti");
	keyboard_initialize();
	
	const char line_buf[512];
	for (;;) {
		printf("> ");
		gets(line_buf, 512);
		printf("\n%s\n", line_buf);
		memset(line_buf, 0, 512);
	}

	return;
}
