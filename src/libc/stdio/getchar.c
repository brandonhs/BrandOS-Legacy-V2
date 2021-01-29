#include <stdio.h>
#include <kernel/keyboard.h>

unsigned char getchar() {
    char* str[512];
    gets(str, 512);
    return str[0];
}
