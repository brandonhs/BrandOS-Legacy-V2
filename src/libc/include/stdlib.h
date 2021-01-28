#ifndef _STLIB_H

#ifdef __cplusplus
extern "C" {
#endif

#define _STLIB_H

__attribute__((__noreturn__))
void abort(void);

char* itoa(int val, int base);

#ifdef __cplusplus
}
#endif

#endif /* _STLIB_H */