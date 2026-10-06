#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

int reverse(int x)
{
    int rev = 0;
    int y = x;
    while (y != 0)
    {
        int digit = y % 10;
        y = y / 10;
        /* check BEFORE multiplying — signed overflow is UB, not wraparound */
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && digit > 7))
            return 0;
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && digit < -8))
            return 0;
        rev = rev * 10 + digit;
    }
    return rev;
}