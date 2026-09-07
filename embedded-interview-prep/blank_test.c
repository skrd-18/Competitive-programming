#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

/*
 *   Part 1
 */

bool reverse_int(int n, int *out)
{
    int reversed = 0;
    while (n != 0)
    {
        int digit = n % 10;
        n = n / 10;
        if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && digit > 7))
            return false;
        if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && digit < -8))
            return false;
        reversed = reversed * 10 + digit;
    }
    *out = (int)reversed;
    return true;
}

bool count_digits(int n, int *out)
{
    // base case
    if (n == 0)
    {
        *out = 1;
        return true;
    }

    int count = 0;
    while (n != 0)
    {
        n = n / 10;
        count += 1;
    }
    *out = (int)count;
    return true;
}

bool sum_digits(int n, int *out)
{
    int sum = 0;
    while (n != 0)
    {
        sum += n % 10;
        n = n / 10;
    }
    *out = (int)sum;
    return true;
}
/*
 * End Part 1
 */

/*
 *   Part 2: MSB
 */

int msb_value(uint32_t x)
{
    return (int)x >> 31;
}

int sign_bit(int x)
{
    return (int)(x >> 31);
}

int highest_msb_bit(int n)
{
    int count = 0;
    while (n >>= 1)
        count += 1;

    return count;
}

int lowest_set_bit_pos(uint32_t x)
{
    if (x == 0)
        return -1;

    int pos = 0;
    while (!(x & 1u))
    {
        x = x >> 1;
        pos += 1;
    }
    return pos;
}

uint32_t isolate_lowest_set_bit(uint32_t x)
{
    return x & -x;
}

/*
 * End of Part 2: MSB
 */

int main(int argc, char const *argv[])
{
    int out = 0;
    if (reverse_int(-12367, &out))
        printf("out is %d\n", out);

    if (count_digits(123, &out))
        printf("count = %d\n", out);

    if (sum_digits(123, &out))
        printf("sum = %d\n", out);

    printf("sign_bit of -32 is %d\n", sign_bit(-32));

    printf("highest msb bit = %d\n", highest_msb_bit(8));
    printf("lowest set bit pos is %d\n", lowest_set_bit_pos(240));

    printf("isolate lowest set bit of x = 12, %b \n", isolate_lowest_set_bit(12));
    return 0;
}
