#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

int hammingWeight(int n)
{
    size_t count = 0;
    while (n != 0)
    {
        n = n & (n - 1);
        count += 1;
    }
    return count;
}
