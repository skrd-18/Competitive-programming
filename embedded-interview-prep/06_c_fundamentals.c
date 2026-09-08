/* =====================================================================
 * 06_c_fundamentals.c  --  The exact things that went wrong in round 1.
 *
 * Build:  gcc -Wall -Wextra -Wpedantic -std=c11 -O2 -o 06_c 06_c_fundamentals.c
 * Run:    ./06_c
 *
 * You told me three things went badly:
 *    1. a switch/case question
 *    2. an MSB (most significant bit) question
 *    3. "reverse an integer" -- you offered the string round-trip
 *    4. a fill-in-the-blanks flowchart
 *
 * That is a very specific and very fixable profile. It is NOT "I'm bad at
 * algorithms". It is elementary C and bit-level thinking -- four days is
 * more than enough.
 *
 * SECTIONS 1-3 ARE THE HIGHEST-PRIORITY THING IN YOUR ENTIRE PREP.
 * Do them until you can write each one cold, in under two minutes, with
 * the edge cases stated out loud before you type.
 * ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

/* =====================================================================
 * 1. REVERSE AN INTEGER   <-- you botched this one. Fix it first.
 *
 * WHY THE STRING ANSWER LOSES THE POINT:
 * "Convert to string, reverse, convert back" is not wrong, it works. But
 * in an EMBEDDED interview it is the wrong instinct, and the interviewer
 * hears three problems:
 *   - it allocates a buffer (how big? did you size it right? malloc?)
 *   - it drags in sprintf/atoi -- on a Cortex-M, printf-family code can
 *     cost several KB of flash, which is a real budget on a secure element
 *   - it dodges the actual question, which is about arithmetic and overflow
 *
 * THE ANSWER THEY WANT: peel digits with % and /, build up the reverse,
 * and handle overflow. Say the overflow point BEFORE you write the loop --
 * that alone recovers most of the mark.
 * ------------------------------------------------------------------- */

/* The core idea in three lines -- burn this in:
 *      digit = x % 10;        peel the last digit
 *      x     = x / 10;        drop it
 *      rev   = rev * 10 + digit;   push it onto the reverse
 */

int reverse_int_simple(int x)
{
    int rev = 0;
    while (x != 0)
    {
        int digit = x % 10;     /* C99+: truncates toward zero, so    */
        x /= 10;                /* -123 % 10 == -3. Negatives just work. */
        rev = rev * 10 + digit; /* <-- CAN OVERFLOW. See the real version. */
    }
    return rev;
}

/* The version to actually write in an interview.
 *
 * SAY THIS OUT LOUD BEFORE CODING:
 *   "Reversing can overflow -- 1534236469 reverses to something larger than
 *    INT_MAX. And signed overflow is undefined behaviour in C, so I can't
 *    just do the multiply and check afterwards; I have to check BEFORE.
 *    I'll return 0 on overflow -- tell me if you'd rather I saturate or
 *    use a wider type."
 *
 * INT_MAX =  2147483647  -> last digit 7
 * INT_MIN = -2147483648  -> last digit -8
 */
int reverse_int(int x)
{
    int rev = 0;
    while (x != 0)
    {
        int digit = x % 10;
        x /= 10;

        /* check BEFORE multiplying -- signed overflow is UB, not wraparound */
        if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && digit > 7))
            return 0; /* positive overflow */
        if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && digit < -8))
            return 0; /* negative overflow */

        rev = rev * 10 + digit;
    }
    return rev;
}

/* If they ask "what if you can't return a sentinel?" -- use a wider type
 * and an out-parameter. This is the embedded-friendly shape: return a
 * status, write the result through a pointer. */
bool reverse_int_checked(int x, int *out)
{
    int64_t rev = 0;
    while (x != 0)
    {
        rev = rev * 10 + (x % 10);
        x /= 10;
        if (rev > INT_MAX || rev < INT_MIN)
            return false;
    }
    *out = (int)rev;
    return true;
}

/* Close cousins they may pivot to -- know all three, they're the same trick */

int count_digits(int n)
{
    if (n == 0) // edge case
        return 1;
    int c = 0;
    while (n != 0)
    {
        n /= 10;
        c++;
    }
    return c;
}

int sum_digits(int n)
{
    int s = 0;
    if (n < 0) // edge case
        n = -n;
    while (n != 0)
    {
        s += n % 10; // peel the last digit
        n /= 10;
    }
    return s;
}

bool is_numeric_palindrome(int n)
{
    if (n < 0)
        return false; /* -121 reversed is 121- : not one */
    long long rev = 0, tmp = n;
    while (tmp != 0)
    {
        rev = rev * 10 + tmp % 10;
        tmp /= 10;
    }
    return rev == n;
}

/* =====================================================================
 * 2. MSB AND BIT EXTRACTION   <-- the other one you botched.
 *
 * "MSB" can mean three different questions. ASK WHICH ONE. Asking is a
 * mark, not a weakness:
 *    (a) what is the VALUE of the most significant bit position (bit 31)?
 *    (b) what is the POSITION of the highest SET bit?
 *    (c) extract the most significant BYTE?
 * ------------------------------------------------------------------- */

/* (a) The value of bit 31 -- i.e. the sign bit in two's complement.
 *
 * TRAP: for a SIGNED int, `x >> 31` is implementation-defined for negative
 * values (in practice arithmetic shift, giving -1, not 1). Always cast to
 * unsigned first, or mask. Saying this out loud is the whole point. */
int msb_value(uint32_t x) { return (int)(x >> 31); }
int msb_value_mask(uint32_t x) { return (x & 0x80000000u) ? 1 : 0; }

/* the safe way to do it on a signed int */
int sign_bit(int x) { return (int)(((uint32_t)x) >> 31); }

/* (b) Position of the highest set bit. 0-indexed; returns -1 for x == 0.
 * Loop version first -- always be able to write the loop before reaching
 * for a builtin. */
int msb_position(uint32_t x)
{
    if (x == 0)
        return -1;
    int pos = 0;
    while (x >>= 1)
        pos++; /* shift until nothing left */
    return pos;
}

/* the fast version -- name it, but write the loop unless asked */
int msb_position_builtin(uint32_t x)
{
    return x ? 31 - __builtin_clz(x) : -1; /* clz = count leading zeros */
}

/* (c) The most significant BYTE of a 32-bit word */
uint8_t msb_byte(uint32_t x) { return (uint8_t)(x >> 24); }
uint8_t lsb_byte(uint32_t x) { return (uint8_t)(x & 0xFF); }

/* LSB -- the mirror questions */
int lsb_value(uint32_t x) { return (int)(x & 1u); }
int lowest_set_bit_pos(uint32_t x)
{
    if (x == 0)
        return -1;
    int pos = 0;
    while (!(x & 1u))
    {
        x >>= 1;
        pos++;
    }
    return pos;
}

// the below is just 2s complement.
uint32_t isolate_lowest_set_bit(uint32_t x) { return x & (~x + 1u); } /* == x & -x */

/* The full bit toolkit -- these must be automatic */
#define BIT(n) (1UL << (n))
#define SET_BIT(r, n) ((r) |= BIT(n))
#define CLEAR_BIT(r, n) ((r) &= ~BIT(n))
#define TOGGLE_BIT(r, n) ((r) ^= BIT(n))
#define TEST_BIT(r, n) (((r) >> (n)) & 1UL)

int popcount(uint32_t v)
{
    int c = 0;
    while (v)
    {
        v &= v - 1; // clears the lowest set bit of v
        c++;
    }
    return c;
}

// clear the lowest bit and see if anything's left" (power-of-2 test), guarded by v&& to make sure v isn't zero
bool is_pow2(uint32_t v) { return v && !(v & (v - 1)); }

uint32_t reverse_bits(uint32_t v) /* reverse the BIT order (not digits!) */
{
    uint32_t r = 0;
    for (int i = 0; i < 32; i++)
    {
        r = (r << 1) | (v & 1u);
        v >>= 1;
    }
    return r;
}

/* extract an n-bit field starting at bit `pos` -- register programming bread
 * and butter, and very likely at a smart-card company */
uint32_t extract_field(uint32_t reg, int pos, int width)
{
    // reg >> pos: slide the field you want down to the bottom.
    // This is a new trick worth understanding on its own: (1u << width) - 1u builds a mask of exactly width ones.
    /**
     * pos — where the field starts (which bits to look at)
     * width — how wide the field is (how many bits to keep once you're aligned)
     */
    return (reg >> pos) & ((1u << width) - 1u);
}

uint32_t insert_field(uint32_t reg, int pos, int width, uint32_t val)
{
    /**
     * Full trace:
    reg  = 1010 1011
    mask = 1111 0000
    ~mask= 0000 1111

    reg & ~mask   = 1010 1011 & 0000 1111 = 0000 1011   (old field erased, rest kept)

    val         = 0000 0011
    val << pos  = 0011 0000
    & mask      = 0011 0000 & 1111 0000 = 0011 0000    (new field value, aligned & clipped)

    result = (reg & ~mask) | ((val<<pos) & mask)
        = 0000 1011 | 0011 0000
        = 0011 1011  = 0x3B  ✓
    That matches the test. So the whole function is the classic embedded "read-modify-write" pattern: erase the old field bits, then OR in the new value shifted and clipped to fit exactly where the field lives — leaving every other bit in reg untouched.
     */
    uint32_t mask = ((1u << width) - 1u) << pos;
    return (reg & ~mask) | ((val << pos) & mask); /* read-modify-write */
}

/* =====================================================================
 * 3. SWITCH / CASE   <-- the third one you botched.
 *
 * THE RULES, complete. Most people miss 3, 5 and 7.
 *
 *  1. The controlling expression must be an INTEGER type -- int, char,
 *     short, long, enum, bool. NOT float, NOT double, NOT a string,
 *     NOT a struct. `switch (a_float)` will not compile.
 *
 *  2. Case labels must be COMPILE-TIME CONSTANT integer expressions.
 *     `case x:` where x is a variable does not compile. `case 2+3:` does.
 *     `case 'A':` does (char promotes to int).
 *
 *  3. Case labels must be UNIQUE within the switch. Duplicates = error.
 *
 *  4. WITHOUT `break`, execution FALLS THROUGH into the next case. This is
 *     the number-one switch bug and the number-one switch interview
 *     question. Deliberate fall-through should carry a comment.
 *
 *  5. `default` can appear ANYWHERE, not only last -- and if no case
 *     matches and there is no default, the whole switch does nothing.
 *
 *  6. Cases can be stacked to share a body: `case 1: case 2: case 3: ...`
 *     -- that is just fall-through used on purpose.
 *
 *  7. You cannot declare a variable with an initialiser directly after a
 *     case label without a block:
 *          case 1: int y = 5;        <-- error in C
 *          case 1: { int y = 5; ... } <-- fine
 *     Reason: the label jumps past the initialisation.
 *
 *  8. C has NO range cases (`case 1...5:` is a GCC extension, not standard C)
 *     and NO string switching. Use if/else or a lookup table.
 *
 *  9. Why use switch at all? On a dense set of values the compiler can emit
 *     a JUMP TABLE -- O(1) dispatch instead of an if/else chain's O(n)
 *     comparisons. On a sparse set it degenerates to comparisons anyway.
 *     THIS IS THE ANSWER TO "switch vs if-else". Say "jump table".
 *
 * 10. In embedded code the classic switch is an APDU/command dispatcher and
 *     a state machine -- which is exactly what a smart-card OS is built from.
 *     Mentioning that connects the question to their domain.
 * ------------------------------------------------------------------- */

/* the fall-through demo -- run it and watch */
const char *switch_falls_through(int n)
{
    static char buf[64];
    buf[0] = '\0';
    switch (n)
    {
    /* No break -> falls through. The attribute below tells the compiler
     * "I meant this", which silences -Wimplicit-fallthrough. Knowing that
     * marker exists is itself a good answer: production code must make
     * intentional fall-through explicit, because the reviewer cannot tell
     * a deliberate one from a forgotten break. C23 spells it
     * [[fallthrough]]; GCC/Clang accept __attribute__((fallthrough)).
     * A bare "fall through" comment also works with GCC. */
    case 1:
        strcat(buf, "one ");
        __attribute__((fallthrough));
    case 2:
        strcat(buf, "two ");
        __attribute__((fallthrough));
    case 3:
        strcat(buf, "three ");
        break; /* stops here */
    case 4:
        strcat(buf, "four ");
        break;
    default:
        strcat(buf, "other ");
        break;
    }
    return buf;
}

/* stacked cases -- deliberate, idiomatic fall-through */
bool is_vowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return true;
    default:
        return false;
    }
}

/* the embedded idiom they'd recognise: an APDU command dispatcher.
 * A smart-card OS is a big switch on INS. Say that if switch comes up. */
typedef enum
{
    SW_OK = 0x9000,
    SW_WRONG_LENGTH = 0x6700,
    SW_SECURITY = 0x6982,
    SW_NOT_FOUND = 0x6A82,
    SW_INS_NOT_SUPPORTED = 0x6D00
} sw_t;

sw_t dispatch_apdu(uint8_t ins, uint8_t lc)
{
    switch (ins)
    {
    case 0xA4: /* SELECT */
        return (lc == 0) ? SW_WRONG_LENGTH : SW_OK;
    case 0xB0: /* READ BINARY */
    case 0xB2: /* READ RECORD -- shares the body */
        return SW_OK;
    case 0x20: /* VERIFY */
        return SW_SECURITY;
    case 0xE2: /* STORE DATA */
        return SW_OK;
    default:
        return SW_INS_NOT_SUPPORTED; /* always have a default */
    }
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

/* =====================================================================
 * 4. THE FLOWCHART QUESTION
 *
 * They gave you a flowchart with blanks. That is a European engineering
 * assessment staple and it tests one thing: can you read a process and
 * express it precisely?
 *
 * THE SYMBOLS:
 *    Oval / stadium ......  Start / End (terminator)
 *    Rectangle ...........  Process -- an action, an assignment
 *    Parallelogram .......  Input / Output
 *    Diamond .............  Decision -- exactly one condition, two exits
 *                           labelled Yes/No (or True/False)
 *    Arrow ...............  Flow of control
 *    Circle ..............  Connector (jump to a matching circle)
 *
 * HOW TO FILL BLANKS, in order:
 *   1. Find Start and End first. Anchor both.
 *   2. Identify the LOOP: an arrow going backwards is a loop. What is the
 *      loop variable, and where is it initialised, tested, updated?
 *   3. Every diamond needs a condition that is TRUE or FALSE -- never a
 *      statement. If a blank is in a diamond, it is a comparison.
 *   4. Every blank in a rectangle is an ASSIGNMENT or an operation.
 *   5. TRACE IT with a small concrete input. Write a table of variable
 *      values row by row. This catches almost every mistake.
 *   6. Check the termination condition -- off-by-one lives here.
 *
 * As a flowchart, reverse-an-integer is:
 *      (Start) -> [rev = 0] -> <x != 0 ?> --No--> (Output rev) -> (End)
 *                                  |Yes
 *                                  v
 *                          [digit = x % 10]
 *                          [x = x / 10]
 *                          [rev = rev*10 + digit]
 *                                  |
 *                                  +--> back to the diamond
 *
 * If a blank sat in the diamond, the answer is `x != 0` (or `x > 0`).
 * If a blank sat in the loop body, it is one of those three assignments.
 *
 * PRACTICE: take each function in this file and draw it as a flowchart on
 * paper, then cover the code and rebuild the code from the flowchart.
 * Twenty minutes of that and this question type stops being scary.
 * ------------------------------------------------------------------- */

/* =====================================================================
 * 5. THE ELEMENTARY C THAT CLUSTERS AROUND THOSE QUESTIONS
 * ------------------------------------------------------------------- */

/* integer division and modulo -- know the negatives */
void integer_arithmetic_notes(void)
{
    /*  7 /  2 ==  3      7 %  2 ==  1
     * -7 /  2 == -3     -7 %  2 == -1     (C99: truncation toward zero)
     *  7 / -2 == -3      7 % -2 ==  1
     * The sign of % follows the DIVIDEND (left operand) in C.
     * Python differs! -7 % 2 == 1 in Python. Do not carry the habit over. */
}

/* operator precedence traps that bite in bit code */
void precedence_notes(void)
{
    /* == binds TIGHTER than &, so:
     *     if (x & 1 == 0)     parses as   x & (1 == 0)   -> x & 0 -> 0. BUG.
     *     if ((x & 1) == 0)   is what you meant.
     * Shifts bind LOOSER than + -, so:
     *     x << 1 + 2   is   x << 3,  not  (x<<1)+2
     * PARENTHESISE bit expressions. Always. */
}

/* pre vs post increment */
void increment_notes(void)
{
    /* int i = 5; int j = i++;   -> j == 5, i == 6  (use then increment)
     * int i = 5; int j = ++i;   -> j == 6, i == 6  (increment then use)
     * NEVER write i = i++ or a[i] = i++ -- unsequenced, undefined. */
}

/* char signedness -- a genuine portability trap */
void char_notes(void)
{
    /* Plain `char` may be signed OR unsigned -- implementation defined.
     * On x86 it's signed; on ARM it's UNSIGNED by default.
     * So `char c = 0x80; if (c < 0)` behaves differently across targets.
     * For byte data ALWAYS use uint8_t (or explicitly unsigned char). */
}

/* ternary, compound assignment, comma -- small but they appear in quizzes */
int max3(int a, int b, int c)
{
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

/* swap without a temp -- know it, and know why not to use it */
void swap_xor(int *a, int *b)
{
    /**
     *a ^= *b;   // a = a ^ b
     *b ^= *a;   // b = b ^ (a ^ b) = a        (b^b cancels to 0, leaving a)
     *a ^= *b;   // a = (a ^ b) ^ a = b        (a^a cancels to 0, leaving b)
     */

    if (a == b) // if a and b are the same memory location
        return; /* ALIASING: without this, zeroes both */
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

/* string <-> integer by hand (they may ask you to implement atoi) */
int my_atoi(const char *s)
{
    int i = 0, sign = 1;
    long long r = 0;
    while (s[i] == ' ' || s[i] == '\t')
        i++; /* skip whitespace */
    if (s[i] == '+' || s[i] == '-')
        sign = (s[i++] == '-') ? -1 : 1;
    while (s[i] >= '0' && s[i] <= '9')
    {
        r = r * 10 + (s[i++] - '0'); /* '7'-'0' == 7 */
        if (sign * r > INT_MAX)
            return INT_MAX; /* saturate, like real atoi */
        if (sign * r < INT_MIN)
            return INT_MIN;
    }
    return (int)(sign * r);
}

/* the reverse direction, without sprintf */
void my_itoa(int n, char *buf, size_t cap)
{
    char tmp[12];
    int i = 0;
    bool neg = (n < 0);
    unsigned int u = neg ? (unsigned int)(-(long long)n) : (unsigned int)n;

    if (u == 0)
        tmp[i++] = '0';

    while (u)
    {
        tmp[i++] = (char)('0' + u % 10);
        u /= 10;
    }

    if (neg)
        tmp[i++] = '-';

    size_t j = 0;
    while (i > 0 && j + 1 < cap)
        buf[j++] = tmp[--i]; /* reverse into buf */
    buf[j] = '\0';
}

/* =====================================================================
 * SELF-TEST
 * ------------------------------------------------------------------- */
static int fails = 0;
#define CHECK(label, got, want)                                           \
    do                                                                    \
    {                                                                     \
        long long g = (long long)(got), w = (long long)(want);            \
        if (g == w)                                                       \
            printf("  PASS  %-34s = %lld\n", label, g);                   \
        else                                                              \
        {                                                                 \
            printf("  **FAIL** %-32s = %lld (want %lld)\n", label, g, w); \
            fails++;                                                      \
        }                                                                 \
    } while (0)

int main(void)
{
    printf("INT_MAX % 10 = %d \n", INT_MAX % 10);
    printf("INT_MAX = %d \n", INT_MAX);
    puts("1. REVERSE AN INTEGER");
    CHECK("reverse_int(123)", reverse_int(123), 321);
    CHECK("reverse_int(-123)", reverse_int(-123), -321);
    CHECK("reverse_int(120)", reverse_int(120), 21);
    CHECK("reverse_int(0)", reverse_int(0), 0);
    CHECK("reverse_int(7)", reverse_int(7), 7);
    CHECK("reverse_int(1534236469)", reverse_int(1534236469), 0); /* overflow */
    CHECK("reverse_int(-2147483648)", reverse_int(INT_MIN), 0);   /* overflow */
    CHECK("reverse_int(1463847412)", reverse_int(1463847412), 2147483641);
    {
        int out = 0;
        CHECK("checked(123) ok", reverse_int_checked(123, &out), 1);
        CHECK("checked(123) val", out, 321);
        CHECK("checked(overflow)", reverse_int_checked(1534236469, &out), 0);
    }
    CHECK("count_digits(90210)", count_digits(90210), 5);
    CHECK("count_digits(0)", count_digits(0), 1);
    CHECK("sum_digits(-1234)", sum_digits(-1234), 10);
    CHECK("palindrome(12321)", is_numeric_palindrome(12321), 1);
    CHECK("palindrome(-121)", is_numeric_palindrome(-121), 0);

    puts("\n2. MSB / BIT EXTRACTION");
    CHECK("msb_value(0x80000000)", msb_value(0x80000000u), 1);
    CHECK("msb_value(0x7FFFFFFF)", msb_value(0x7FFFFFFFu), 0);
    CHECK("msb_value_mask(0xF0..)", msb_value_mask(0xF0000000u), 1);
    CHECK("sign_bit(-1)", sign_bit(-1), 1);
    CHECK("sign_bit(1)", sign_bit(1), 0);
    CHECK("msb_position(1)", msb_position(1), 0);
    CHECK("msb_position(0xFF)", msb_position(0xFF), 7);
    CHECK("msb_position(0x80000000)", msb_position(0x80000000u), 31);
    CHECK("msb_position(0)", msb_position(0), -1);
    CHECK("msb_pos == builtin", msb_position(0x00FF00FFu) == msb_position_builtin(0x00FF00FFu), 1);
    CHECK("msb_byte(0xDEADBEEF)", msb_byte(0xDEADBEEFu), 0xDE);
    CHECK("lsb_byte(0xDEADBEEF)", lsb_byte(0xDEADBEEFu), 0xEF);
    CHECK("lsb_value(0xF0)", lsb_value(0xF0), 0);
    CHECK("lowest_set_bit(0x28)", lowest_set_bit_pos(0x28), 3);
    CHECK("isolate_lowest(0x28)", isolate_lowest_set_bit(0x28), 0x08);
    CHECK("popcount(0xF0F0F0F0)", popcount(0xF0F0F0F0u), 16);
    CHECK("is_pow2(1024)", is_pow2(1024), 1);
    CHECK("is_pow2(1000)", is_pow2(1000), 0);
    CHECK("reverse_bits(1)", reverse_bits(1), 0x80000000u);
    CHECK("extract_field(0xAB,4,4)", extract_field(0xAB, 4, 4), 0xA);
    CHECK("insert_field", insert_field(0xAB, 4, 4, 0x3), 0x3B);
    {
        uint32_t r = 0;
        SET_BIT(r, 5);
        TOGGLE_BIT(r, 5);
        SET_BIT(r, 2);
        CHECK("macros set/toggle/set", r, 4);
    }

    puts("\n3. SWITCH / CASE");
    printf("  fall-through(1) -> \"%s\"  (expect \"one two three \")\n", switch_falls_through(1));
    printf("  fall-through(2) -> \"%s\"  (expect \"two three \")\n", switch_falls_through(2));
    printf("  fall-through(4) -> \"%s\"  (expect \"four \")\n", switch_falls_through(4));
    printf("  fall-through(9) -> \"%s\"  (expect \"other \")\n", switch_falls_through(9));
    CHECK("is_vowel('E')", is_vowel('E'), 1);
    CHECK("is_vowel('z')", is_vowel('z'), 0);
    CHECK("SELECT lc=0", dispatch_apdu(0xA4, 0), SW_WRONG_LENGTH);
    CHECK("SELECT lc=5", dispatch_apdu(0xA4, 5), SW_OK);
    CHECK("READ RECORD", dispatch_apdu(0xB2, 1), SW_OK);
    CHECK("unknown INS", dispatch_apdu(0x99, 1), SW_INS_NOT_SUPPORTED);
    CHECK("state IDLE+s", next_state(ST_IDLE, 's'), ST_SELECTED);
    CHECK("state SELECTED+a", next_state(ST_SELECTED, 'a'), ST_AUTHENTICATED);
    CHECK("state SELECTED+x", next_state(ST_SELECTED, 'x'), ST_LOCKED);
    CHECK("state LOCKED sticky", next_state(ST_LOCKED, 'a'), ST_LOCKED);

    puts("\n5. ELEMENTARY C");
    CHECK("-7 / 2", -7 / 2, -3);
    CHECK("-7 % 2", -7 % 2, -1); /* sign follows the dividend */
    CHECK("7 % -2", 7 % -2, 1);
    CHECK("x & 1 == 0 trap", (2 & 1) == 0, 1);
    CHECK("max3", max3(3, 9, 5), 9);
    {
        int a = 3, b = 8;
        swap_xor(&a, &b);
        CHECK("swap_xor a", a, 8);
        CHECK("swap_xor b", b, 3);
    }
    {
        int a = 5;
        swap_xor(&a, &a);
        CHECK("swap_xor aliased", a, 5);
    }
    CHECK("my_atoi(\"  -42\")", my_atoi("  -42"), -42);
    CHECK("my_atoi(\"4193x\")", my_atoi("4193x"), 4193);
    CHECK("my_atoi(\"\")", my_atoi(""), 0);
    CHECK("my_atoi overflow", my_atoi("99999999999"), INT_MAX);
    {
        char b[16];
        my_itoa(-3021, b, sizeof b);
        printf("  %s  my_itoa(-3021) = \"%s\"\n", strcmp(b, "-3021") ? "**FAIL**" : "PASS ", b);
        if (strcmp(b, "-3021"))
            fails++;
    }
    {
        char b[16];
        my_itoa(0, b, sizeof b);
        printf("  %s  my_itoa(0) = \"%s\"\n", strcmp(b, "0") ? "**FAIL**" : "PASS ", b);
        if (strcmp(b, "0"))
            fails++;
    }

    printf("\n%s  (%d failures)\n", fails ? "SOME TESTS FAILED" : "ALL TESTS PASSED", fails);
    return fails ? 1 : 0;
}
