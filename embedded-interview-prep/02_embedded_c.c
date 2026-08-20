/* =====================================================================
 * 02_embedded_c.c  --  The C that Thales actually asks about.
 *
 * Build:  gcc -Wall -Wextra -O2 -o 02_embedded_c 02_embedded_c.c
 * Run:    ./02_embedded_c
 *
 * Reported Thales technical-assessment questions are NOT LeetCode-hard.
 * They are things like "print a pyramid using a char array" and "remove
 * duplicates from an array and print the result", judged on whether the
 * OUTPUT FORMATTING IS EXACTLY RIGHT. Sections 1-2 are those, done
 * properly. Sections 3-8 are the embedded-C staples that follow.
 * ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

/* =====================================================================
 * 1. PYRAMID PRINTING WITH A CHAR ARRAY   (reported Thales question)
 *
 * The trap is not the algorithm. It is that they diff your output against
 * an expected string. Trailing spaces, the newline at the end, whether
 * row 1 is centred -- get those exactly right and say out loud what you
 * assumed. "I'm assuming no trailing whitespace on each line; tell me if
 * you want it padded" is a better answer than silently guessing.
 * ------------------------------------------------------------------- */
void pyramid_stars(int rows)
{
    for (int i = 1; i <= rows; i++) {
        for (int s = 0; s < rows - i; s++) putchar(' ');
        for (int c = 0; c < 2 * i - 1; c++) putchar('*');
        putchar('\n');                   /* no trailing spaces */
    }
}

/* char-array variant: builds each line in a buffer first, which is what
 * "using a char array" is hinting at. Also shows you can size a buffer. */
void pyramid_char_array(int rows)
{
    int width = 2 * rows - 1;
    char *line = malloc((size_t)width + 1);   /* +1 for the NUL */
    if (!line) return;

    for (int i = 1; i <= rows; i++) {
        int pad   = rows - i;
        int stars = 2 * i - 1;
        memset(line, ' ', (size_t)pad);
        for (int c = 0; c < stars; c++) line[pad + c] = (char)('A' + i - 1);
        line[pad + stars] = '\0';                  /* terminate, don't print junk */
        puts(line);
    }
    free(line);
}

/* =====================================================================
 * 2. REMOVE DUPLICATES IN PLACE        (reported Thales question)
 *
 * Two versions. Lead with the O(n log n) one, then ASK: "is the input
 * sorted, and must I preserve the original order?" That question is worth
 * more than the code. If order must be preserved you need O(n) extra
 * space or O(n^2) time -- say that trade-off explicitly.
 * ------------------------------------------------------------------- */

/* (a) input already sorted: classic two-pointer, O(n), O(1) space */
int dedup_sorted(int *a, int n)
{
    if (n <= 1) return n;
    int w = 1;                            /* write cursor */
    for (int r = 1; r < n; r++)
        if (a[r] != a[w - 1]) a[w++] = a[r];
    return w;                             /* new length */
}

/* (b) unsorted, ORDER PRESERVED, no extra memory: O(n^2) but O(1) space.
 *     On an MCU this is often the right call for small n. */
int dedup_unsorted_stable(int *a, int n)
{
    int w = 0;
    for (int r = 0; r < n; r++) {
        bool seen = false;
        for (int k = 0; k < w; k++)
            if (a[k] == a[r]) { seen = true; break; }
        if (!seen) a[w++] = a[r];
    }
    return w;
}

/* =====================================================================
 * 3. BIT MANIPULATION -- the bread and butter of register programming
 *
 * Every one of these should be instant. On a secure element / SIM you are
 * packing flags into bytes constantly.
 * ------------------------------------------------------------------- */
#define BIT(n)              (1UL << (n))
#define SET_BIT(reg, n)     ((reg) |=  BIT(n))
#define CLEAR_BIT(reg, n)   ((reg) &= ~BIT(n))
#define TOGGLE_BIT(reg, n)  ((reg) ^=  BIT(n))
#define TEST_BIT(reg, n)    (((reg) >> (n)) & 1UL)

/* count set bits -- Brian Kernighan's trick, loops once per SET bit */
int popcount_kernighan(uint32_t v)
{
    int c = 0;
    while (v) { v &= v - 1; c++; }        /* clears the lowest set bit */
    return c;
}

/* power of two? (0 is deliberately excluded) */
bool is_power_of_two(uint32_t v) { return v && !(v & (v - 1)); }

/* reverse the bits of a byte */
uint8_t reverse_byte(uint8_t b)
{
    b = (uint8_t)((b & 0xF0) >> 4 | (b & 0x0F) << 4);
    b = (uint8_t)((b & 0xCC) >> 2 | (b & 0x33) << 2);
    b = (uint8_t)((b & 0xAA) >> 1 | (b & 0x55) << 1);
    return b;
}

/* SAY: "I would not use the XOR swap trick in production -- it breaks when
 *       both pointers alias the same object, and any modern compiler emits
 *       the same code for the temp version anyway." */

/* =====================================================================
 * 4. ENDIANNESS
 *
 * SAY: "Little-endian stores the least significant byte at the lowest
 *       address. It matters the moment bytes leave the chip -- ARM is
 *       little-endian but network byte order and most smart-card / APDU
 *       protocols are big-endian, so a struct cast over a byte stream is
 *       a portability bug waiting to happen. I serialise byte by byte."
 * ------------------------------------------------------------------- */
bool is_little_endian(void)
{
    uint32_t x = 1;
    return *(uint8_t *)&x == 1;
}

uint32_t swap32(uint32_t v)
{
    return ((v >> 24) & 0x000000FFu) |
           ((v >>  8) & 0x0000FF00u) |
           ((v <<  8) & 0x00FF0000u) |
           ((v << 24) & 0xFF000000u);
}

/* the portable way: never cast, always shift */
void store_be32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v >> 24);
    p[1] = (uint8_t)(v >> 16);
    p[2] = (uint8_t)(v >>  8);
    p[3] = (uint8_t)(v);
}

uint32_t load_be32(const uint8_t *p)
{
    return ((uint32_t)p[0] << 24) | ((uint32_t)p[1] << 16) |
           ((uint32_t)p[2] <<  8) |  (uint32_t)p[3];
}

/* =====================================================================
 * 5. RING BUFFER (lock-free, single producer / single consumer)
 *
 * This is THE embedded data-structure question. It is also a CS2040C
 * queue, so it bridges both halves of your prep -- point that out.
 *
 * SAY: "Power-of-two capacity so the wrap is a mask, not a modulo -- no
 *       division on a Cortex-M0. The one-slot-empty convention
 *       distinguishes full from empty without a separate count, so with a
 *       single producer and a single consumer each index has exactly one
 *       writer and I need no critical section. head and tail are volatile
 *       because the ISR writes one of them behind the compiler's back."
 * ------------------------------------------------------------------- */
#define RB_SIZE 8                          /* MUST be a power of two */
#define RB_MASK (RB_SIZE - 1)

typedef struct {
    uint8_t buf[RB_SIZE];
    volatile uint16_t head;                /* producer writes */
    volatile uint16_t tail;                /* consumer writes */
} ring_buffer_t;

static void rb_init(ring_buffer_t *rb) { rb->head = rb->tail = 0; }

static bool rb_is_empty(const ring_buffer_t *rb) { return rb->head == rb->tail; }

static bool rb_is_full(const ring_buffer_t *rb)
{
    return ((rb->head + 1) & RB_MASK) == rb->tail;   /* one slot kept free */
}

static bool rb_push(ring_buffer_t *rb, uint8_t v)    /* called from ISR */
{
    if (rb_is_full(rb)) return false;                /* drop, never block */
    rb->buf[rb->head] = v;
    rb->head = (uint16_t)((rb->head + 1) & RB_MASK); /* publish LAST */
    return true;
}

static bool rb_pop(ring_buffer_t *rb, uint8_t *out)  /* called from main */
{
    if (rb_is_empty(rb)) return false;
    *out = rb->buf[rb->tail];
    rb->tail = (uint16_t)((rb->tail + 1) & RB_MASK);
    return true;
}

/* =====================================================================
 * 6. STRUCT PADDING AND ALIGNMENT
 *
 * SAY: "The compiler inserts padding so each member sits on its natural
 *       alignment; the struct is then padded to a multiple of its largest
 *       member's alignment so arrays stay aligned. Reordering members
 *       largest-to-smallest often shrinks the struct for free -- which on
 *       a part with 8 KB of RAM is a real win. I never use __packed for a
 *       wire format on ARM either, because unaligned access is slow and
 *       on some cores it faults; I serialise field by field instead."
 * ------------------------------------------------------------------- */
struct bad_layout  { char a; int b; char c; short d; };   /* wastes space */
struct good_layout { int b; short d; char a; char c; };   /* packed tight */

/* =====================================================================
 * 7. STRING / ARRAY CLASSICS -- write these without thinking
 * ------------------------------------------------------------------- */
void reverse_string(char *s)
{
    if (!s) return;
    size_t i = 0, j = strlen(s);
    if (j == 0) return;
    j--;
    while (i < j) { char t = s[i]; s[i] = s[j]; s[j] = t; i++; j--; }
}

bool is_palindrome(const char *s)
{
    if (!s) return false;
    size_t i = 0, n = strlen(s);
    if (n == 0) return true;
    size_t j = n - 1;
    while (i < j) { if (s[i] != s[j]) return false; i++; j--; }
    return true;
}

/* my_strlen / my_memcpy: they sometimes ask you to reimplement these */
size_t my_strlen(const char *s) { const char *p = s; while (*p) p++; return (size_t)(p - s); }

void *my_memcpy(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst; const unsigned char *s = src;
    while (n--) *d++ = *s++;
    return dst;
}

/* SAY: "memmove is the one that handles overlapping regions -- it checks
 *       whether dst is above src and copies backwards if so. memcpy is
 *       undefined on overlap, and on a target with DMA-accelerated memcpy
 *       that undefined behaviour really does bite." */
void *my_memmove(void *dst, const void *src, size_t n)
{
    unsigned char *d = dst; const unsigned char *s = (const unsigned char *)src;
    if (d == s || n == 0) return dst;
    if (d < s) { while (n--) *d++ = *s++; }
    else       { d += n; s += n; while (n--) *--d = *--s; }
    return dst;
}

/* =====================================================================
 * 8. THE POINTER-DECLARATION QUESTION  (near-certain to be asked)
 *
 *   const char *p;         -> pointer to const char. *p is read-only,
 *                             p can be repointed.
 *   char * const p;        -> const pointer to char. p is fixed,
 *                             *p is writable.
 *   const char * const p;  -> both fixed.
 *
 * READ IT RIGHT-TO-LEFT from the identifier. Say that rule out loud.
 *
 * volatile: "tells the compiler this object can change outside the
 *   program's control, so it must reload it from memory on every access
 *   rather than caching it in a register. Three cases: memory-mapped
 *   peripheral registers, variables shared with an ISR, and variables
 *   touched across a setjmp. Without it, `while (!flag);` where flag is
 *   set in an ISR compiles to an infinite loop at -O2 -- I have hit that."
 *
 * volatile is NOT atomicity. If they ask "does volatile make it thread
 *   safe?", the answer is no -- you still need a critical section or an
 *   atomic for read-modify-write. Getting this right separates you from
 *   most candidates.
 *
 * static: at file scope -> internal linkage (invisible to other TUs).
 *   Inside a function -> lifetime is the whole program, but scope stays
 *   local. In embedded, file-scope static is how you keep a driver's
 *   state private and out of the global namespace.
 * ------------------------------------------------------------------- */

/* =====================================================================
 * MAIN -- exercises everything so you can see real output
 * ------------------------------------------------------------------- */
int main(void)
{
    puts("=== 1. Pyramid (stars, 5 rows) ===");
    pyramid_stars(5);

    puts("\n=== 1b. Pyramid (char array, 5 rows) ===");
    pyramid_char_array(5);

    puts("\n=== 2. Dedup ===");
    { int a[] = {1,1,2,3,3,3,4,5,5};
      int n = dedup_sorted(a, 9);
      printf("sorted   -> len %d : ", n);
      for (int i = 0; i < n; i++) printf("%d ", a[i]);
      putchar('\n'); }

    { int a[] = {5,1,5,2,1,9,2,9,3};
      int n = dedup_unsorted_stable(a, 9);
      printf("unsorted -> len %d : ", n);
      for (int i = 0; i < n; i++) printf("%d ", a[i]);
      putchar('\n'); }

    puts("\n=== 3. Bit manipulation ===");
    { uint32_t reg = 0;
      SET_BIT(reg, 3); SET_BIT(reg, 5); TOGGLE_BIT(reg, 3);
      printf("reg = 0x%08X, bit5=%lu, bit3=%lu\n",
             reg, (unsigned long)TEST_BIT(reg, 5), (unsigned long)TEST_BIT(reg, 3)); }
    printf("popcount(0xF0F0F0F0) = %d  (expect 16)\n", popcount_kernighan(0xF0F0F0F0u));
    printf("is_power_of_two(1024)= %d, (1000)= %d\n",
           is_power_of_two(1024), is_power_of_two(1000));
    printf("reverse_byte(0b11010010=0xD2) = 0x%02X (expect 0x4B)\n", reverse_byte(0xD2));

    puts("\n=== 4. Endianness ===");
    printf("host is %s-endian\n", is_little_endian() ? "little" : "big");
    printf("swap32(0x12345678) = 0x%08X\n", swap32(0x12345678u));
    { uint8_t w[4]; store_be32(w, 0xDEADBEEFu);
      printf("store_be32 -> %02X %02X %02X %02X ; load_be32 -> 0x%08X\n",
             w[0], w[1], w[2], w[3], load_be32(w)); }

    puts("\n=== 5. Ring buffer (capacity 8, usable 7) ===");
    { ring_buffer_t rb; rb_init(&rb);
      int pushed = 0;
      for (uint8_t i = 1; i <= 10; i++) if (rb_push(&rb, i)) pushed++;
      printf("pushed %d of 10 (expect 7 -- one slot reserved)\n", pushed);
      printf("popped: ");
      uint8_t v = 0; while (rb_pop(&rb, &v)) printf("%u ", v);
      printf("\nempty now? %s\n", rb_is_empty(&rb) ? "yes" : "no");
      /* wrap-around check */
      rb_push(&rb, 99); rb_push(&rb, 100);
      rb_pop(&rb, &v); printf("after wrap, first pop = %u (expect 99)\n", v); }

    puts("\n=== 6. Struct padding ===");
    printf("sizeof(bad_layout)  = %zu  {char,int,char,short}\n", sizeof(struct bad_layout));
    printf("sizeof(good_layout) = %zu  {int,short,char,char}\n", sizeof(struct good_layout));
    printf("offsetof(bad.b) = %zu (padding before it)\n", offsetof(struct bad_layout, b));

    puts("\n=== 7. Strings ===");
    { char s[] = "embedded";
      reverse_string(s); printf("reversed: %s\n", s); }
    printf("is_palindrome(\"level\") = %d, (\"levels\") = %d\n",
           is_palindrome("level"), is_palindrome("levels"));
    printf("my_strlen(\"Thales\") = %zu\n", my_strlen("Thales"));
    { char buf[16] = "abcdefgh";
      my_memmove(buf + 2, buf, 6);        /* overlapping, forward */
      printf("memmove overlap -> %s (expect ababcdef)\n", buf); }

    puts("\n=== 8. sizeof vs strlen trap ===");
    { char arr[10] = "hi";
      const char *ptr = "hi";
      printf("char arr[10]=\"hi\": sizeof=%zu strlen=%zu\n", sizeof arr, strlen(arr));
      printf("const char *ptr  : sizeof=%zu strlen=%zu  <-- sizeof is the POINTER\n",
             sizeof ptr, strlen(ptr)); }

    puts("\nAll sections executed.");
    return 0;
}
