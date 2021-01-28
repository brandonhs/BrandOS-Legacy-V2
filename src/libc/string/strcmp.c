#include <string.h>

int strcmp(const char* a, const char* b) {
    size_t l = strlen(a);
    if (strlen(b) != l) return 0;
    for (size_t i = 0; i < l; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}