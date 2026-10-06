#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#define BIT(n) (1U << (n))
#define SET_BIT(reg, n) (reg |= BIT(n))
#define CLEAR_BIT(reg, n) (reg &= ~BIT(n))

int reverseBits(int n)
{
    // typecast into unsigned type so as to avoid making modifications to the input
    unsigned int N = (unsigned int)n;
    unsigned int rev = 0;

    for (size_t i = 0; i < 32; i += 1)
    {
        if ((N >> i) & 1UL)
            SET_BIT(rev, 31 - i);
    }
    return rev;
}

int main(int argc, char const *argv[])
{
    printf("43261596 -> %u \n", reverseBits(43261596));
    return 0;
}
