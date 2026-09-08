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

uint32_t reverse_bits(uint32_t v)
{
    uint32_t r = 0;
    for (size_t i = 0; i < 32; i++)
    {
        r = (r << 1) | (v & 1u);
        v = v >> 1;
    }
    return r;
}

uint32_t insert_field(uint32_t reg, int pos, int width, uint32_t val)
{
    uint32_t mask = ((1U << width) - 1) << pos;
    return (reg & ~mask) | ((val << pos) & mask);
}

/* a state machine with switch -- the other classic embedded use */
typedef enum
{
    ST_IDLE,
    ST_SELECTED,
    ST_AUTHENTICATED,
    ST_LOCKED
} state_t;

state_t next_state(state_t s, char event)
{
    switch (s)
    {
    case ST_IDLE:
        return (event == 's') ? ST_SELECTED : ST_IDLE;
    case ST_SELECTED:
        switch (event)
        { /* nested switch is fine */
        case 'a':
            return ST_AUTHENTICATED;
        case 'x':
            return ST_LOCKED;
        default:
            return ST_SELECTED;
        }
    case ST_AUTHENTICATED:
        return (event == 'r') ? ST_IDLE : ST_AUTHENTICATED;
    case ST_LOCKED:
        return ST_LOCKED; /* terminal */
    default:
        return ST_IDLE;
    }
}

/*
 * End of Part 2: MSB
 */

int my_atoi(const char *s)
{
    long long r = 0;
    int i = 0;
    int sign = 0;

    while ((s[i] != ' ') || (s[i] != '\t'))
        i += 1;
    if ((s[i] == '+') || s[i] == '-')
        sign = s[i] == '-' ? -1 : 1;
    i += 1;
    while (s[i] >= '0' && s[i] <= '9')
    {
        r = r * 10 + (s[i] - '0');
        if (sign * r > INT_MAX)
            return INT_MAX;
        if (sign * r < INT_MIN)
            return INT_MIN;
        i += 1;
    }
    return (int)sign * r;
}

void pyramid_stars(int rows)
{
    for (int i = 1; i <= rows; i++)
    {
        for (int s = 0; s < rows - i; s += 1)
            putchar(' ');
        for (int stars = 0; stars < 2 * i - 1; stars += 1)
            putchar('*');
        putchar('\n');
    }
}

void pyramid_char_array(int rows)
{
    size_t width = 2 * rows - 1;
    char *line = (char *)malloc((size_t)width + 1u);
    if (!line)
        return;

    for (int i = 1; i <= rows; i += 1)
    {
        size_t pad = rows - i;
        size_t stars = 2 * i - 1;
        memset(line, ' ', (size_t)pad);
        for (size_t c = 0; c < stars; c += 1)
            line[pad + c] = (char)('A' + i - 1);
        line[pad + stars] = '\0';
        puts(line);
    }
    free(line);
}

typedef struct
{
    uint8_t pos;
    uint32_t bit_pos;
    uint32_t bit_size;
} bitstream;

int dedup_sorted(int *a, int n)
{
    // O(n) time and O(1)
    if (n <= 1)
        return n;
    size_t w = 1;
    for (size_t r = 1; r < n; r += 1)
    {
        if (a[r] != a[w - 1])
        {
            a[w] = a[r];
            w += 1;
        }
    }
    return w;
}

int popcount_kernighan(uint32_t v)
{
    int c = 0;
    while (v)
    {
        v = v & (v - 1);
        c += 1;
    }
    return c;
}

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

    printf("s = ST_SELECTED, event = 'a' return = %d\n", next_state(ST_SELECTED, 'a'));

    printf("string to integer is atoi() = %d\n", atoi("-43"));

    printf("pyramid = \n");
    pyramid_stars(5);

    return 0;
}
