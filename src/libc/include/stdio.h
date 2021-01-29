#ifndef _STDIO_H
#ifdef __cplusplus

extern "C" {
#endif

#define _STDIO_H

#include <sys/cdefs.h>
#include <stddef.h>

#define EOF (-1)

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);

unsigned char getchar();
unsigned char* gets(unsigned char* buf, size_t buf_len);

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H */