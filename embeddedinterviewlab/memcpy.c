#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

// Implement memcpy() — C starter (adapt types/structs as needed)
void *my_memcpy(void *dest, const void *src, size_t n)
{
    // Uses unsigned char for byte level copying
    unsigned char *d = dest;
    const unsigned char *s = src;
    if (n == 0)
        return dest;
    // the dest is of type void pointer
    for (size_t i = 0; i < n; i += 1)
        d[i] = s[i];
    return dest;
}

int main(int argc, char const *argv[])
{

    return 0;
}
