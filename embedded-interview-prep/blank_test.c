#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define BIT(N) (1UL << (N))
#define SET_BIT(reg, N) ((reg) |= BIT(N))
#define CLEAR_BIT(reg, N) ((reg) &= ~BIT(N))
#define TOGGLE_BIT(reg, N) ((reg) ^= BIT(N))
#define TEST_BIT(reg, N) (((reg) >> N) & 1UL)

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
    for (uint32_t i = 0; i < 32; i += 1)
    {
        r = (r << 1) | (v & 1U);
        v >> 1;
    }
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

int deduped_unsorted_stable(int *a, int n)
{
    size_t w = 0;
    for (size_t r = 0; r < n; r += 1)
    {
        bool seen = false;
        for (size_t k = 0; k < w; k += 1)
        {
            if (a[k] == a[r])
            {
                seen = true;
                break;
            }
        }
        if (!seen)
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

#define RB_SIZE 8
#define RB_MASK (RB_SIZE - 1)
/**
index:   0    1    2    3    4    5    6    7
value:   F    G    ?    A    B    C    D    E
                   ^
              head=2 (next write goes here — currently stale, not real data)
                        ^
                  tail=3 (oldest unread item, "A" — next to be popped)
 */
typedef struct
{
    uint8_t buf[RB_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
} ring_buffer_t;

static void ring_buffer_init(ring_buffer_t *rb)
{
    rb->head = rb->tail = 0;
}

static bool rb_is_empty(const ring_buffer_t *rb)
{
    return rb->head == rb->tail;
}
static bool rb_is_full(const ring_buffer_t *rb)
{
    return (rb->head + 1) & RB_MASK == rb->tail;
}
static bool rb_push(ring_buffer_t *rb, uint8_t v) /* called from ISR */
{
    if (rb_is_full(rb))
        return false;
    rb->buf[rb->head] = v;
    rb->head = (uint16_t)(rb->head + 1) & RB_MASK;
    return true;
}

static bool rb_pop(ring_buffer_t *rb, uint8_t *out) /* called from main */
{
    if (rb_is_empty(rb))
        return false;
    *out = rb->buf[rb->tail];
    rb->tail = (uint16_t)(rb->tail + 1) & RB_MASK;
    return true;
}

void reverse_string(char *s)
{
    if (!s)
        return;
    size_t j = strlen(s);
    size_t i = 0;

    if (j == 0)
        return;

    j -= 1; // remove the null character

    while (i < j)
    {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i += 1;
        j -= 1;
    }
}

size_t my_strlen(const char *s)
{
    const char *p = s;
    while (*p)
        p += 1;
    return (size_t)(p - s);
}

// Linked List
typedef struct node
{
    int data;
    struct node *next;
} node_t;

static node_t *list_push_front(node_t *head, int v)
{
    node_t *n = (node_t *)malloc(sizeof *n);
    if (!n)
    {
        return head;
    }
    n->data = v;
    n->next = head;
    return n;
}

static void list_print(const char *label, const node_t *h)
{
    printf("%-20s", label);
    for (const node_t *p = h; p; p->next)
        printf("%d -> ", p->data);
    puts("NULL");
}

static node_t *list_reverse(node_t *head)
{
    node_t *prev = NULL, *curr = head;
    while (curr)
    {
        node_t *next = curr->next; /* save before we clobber it */
        curr->next = prev;         /* flip the arrow */
        prev = curr;               /* advance */
        curr = next;
    }
    return prev; /* prev is the new head */
}

#define STACK_CAP 32
typedef struct
{
    int buf[STACK_CAP];
    int top;
} stack_t;

static void stack_init(stack_t *s)
{
    s->top = 0;
}

static bool stack_push(stack_t *s, int v)
{
    if (s->top >= STACK_CAP)
        return false;
    s->buf[s->top] = v;
    s->top += 1;
    return true;
}
static bool stack_pop(stack_t *s, int *out)
{
    if (s->top <= 0)
        return false;

    s->top -= 1;
    *out = s->buf[s->top];
}

int binary_search(int *a, int target, int n)
{
    int lo = 0;
    int hi = n - 1;
    while (lo <= hi)
    {
        int mid = lo + ((hi - lo) / 2);
        if (a[mid] == target)
            return mid;
        if (a[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
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

    int arr[3] = {5, 1, 5};
    printf("deduped unsorted stable = %d\n", deduped_unsorted_stable(arr, 3));

    /**
     * Ring buffer
     */
    ring_buffer_t rb;
    ring_buffer_init(&rb);
    rb_push(&rb, 99);
    uint8_t v = 0;
    rb_pop(&rb, &v);
    printf("%u is popped value \n", v);

    /**
     * My implementation of string length
     */

    const char *s = "Hello";
    printf("mystrlen = %zu \n", my_strlen(s));

    /**
     *
     * Stack / Queue
     */
    stack_t test;
    stack_init(&test);
    printf("top is %d\n", test.top);

    /**
     * Binary Search
     */
    int array[5] = {5, 3, 4, 6, 2};
    printf("Binary search is %d\n", binary_search(array, 3, 5));
    return 0;
}
