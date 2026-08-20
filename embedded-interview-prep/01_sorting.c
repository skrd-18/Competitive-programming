/* =====================================================================
 * 01_sorting.c  --  Every sort you need for Friday, in plain C.
 *
 * Build:  gcc -Wall -Wextra -O2 -o 01_sorting 01_sorting.c
 * Run:    ./01_sorting
 *
 * HOW TO USE THIS FILE (this matters more than reading it):
 *   Do NOT read this file to "learn" the sorts. Read a function once,
 *   close the file, and retype it from memory into a blank file until it
 *   compiles and passes on the first try. That is the only practice that
 *   transfers to a live-coding screen share.
 *
 * The comment above each function is the ANSWER YOU SAY OUT LOUD when
 * the interviewer asks "why this one?". Memorise those lines, not the code.
 * ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/* ---------------------------------------------------------------------
 * Helpers
 * ------------------------------------------------------------------- */
static void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void print_arr(const char *label, const int *a, int n)
{
    printf("%-22s", label);
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

static bool is_sorted(const int *a, int n)
{
    for (int i = 1; i < n; i++) if (a[i - 1] > a[i]) return false;
    return true;
}

/* =====================================================================
 * 1. INSERTION SORT
 *
 * SAY: "O(n^2) worst and average, but O(n) on already-sorted input,
 *       in-place O(1) extra space, and stable. It has the smallest
 *       constant factor of any comparison sort, so on embedded I use it
 *       for n under roughly 16 -- and that's exactly why real qsort
 *       implementations cut over to insertion sort for small partitions."
 *
 * This is the single most likely sort to be asked of you, because it is
 * short enough to write on a whiteboard and it exposes off-by-one bugs.
 * ------------------------------------------------------------------- */
void insertion_sort(int *a, int n)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {   /* '>' not '>=' keeps it STABLE */
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

/* =====================================================================
 * 2. SELECTION SORT
 *
 * SAY: "Always O(n^2) comparisons regardless of input, but it performs at
 *       most n-1 swaps. That makes it the right choice when a write is
 *       far more expensive than a read -- writing to EEPROM or flash on a
 *       secure element, for example, where each write costs endurance."
 *
 * That last sentence is a Thales-flavoured answer. Use it.
 * NOTE: selection sort as written is NOT stable (the long-range swap can
 *       jump an equal element past its twin).
 * ------------------------------------------------------------------- */
void selection_sort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min_idx]) min_idx = j;
        if (min_idx != i) swap(&a[i], &a[min_idx]);
    }
}

/* =====================================================================
 * 3. BUBBLE SORT (with early-exit flag)
 *
 * SAY: "I'd only use it as a teaching example. The early-exit flag makes
 *       it O(n) on sorted input, but insertion sort dominates it on every
 *       other input, so there's no real case for it."
 *
 * Being willing to say "I would not use this" is a signal of judgement.
 * ------------------------------------------------------------------- */
void bubble_sort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) { swap(&a[j], &a[j + 1]); swapped = true; }
        }
        if (!swapped) break;             /* already sorted -> bail out */
    }
}

/* =====================================================================
 * 4. MERGE SORT
 *
 * SAY: "Guaranteed O(n log n) in every case, and stable. The cost is
 *       O(n) auxiliary memory, which on a device with 64 KB of RAM is
 *       often the deciding factor against it. I allocate the scratch
 *       buffer ONCE at the top rather than inside merge(), because a
 *       malloc per merge call is both slow and a fragmentation risk."
 *
 * Allocating the buffer once is the detail that separates a candidate who
 * has written embedded code from one who has only done coursework.
 * ------------------------------------------------------------------- */
static void merge(int *a, int lo, int mid, int hi, int *buf)
{
    int i = lo, j = mid + 1, k = lo;

    while (i <= mid && j <= hi)
        buf[k++] = (a[i] <= a[j]) ? a[i++] : a[j++];  /* '<=' keeps STABLE */

    while (i <= mid) buf[k++] = a[i++];
    while (j <= hi)  buf[k++] = a[j++];

    for (int t = lo; t <= hi; t++) a[t] = buf[t];
}

static void merge_sort_rec(int *a, int lo, int hi, int *buf)
{
    if (lo >= hi) return;
    int mid = lo + (hi - lo) / 2;        /* NOT (lo+hi)/2 -- overflow safe */
    merge_sort_rec(a, lo, mid, buf);
    merge_sort_rec(a, mid + 1, hi, buf);
    if (a[mid] <= a[mid + 1]) return;    /* cheap skip: halves already ordered */
    merge(a, lo, mid, hi, buf);
}

void merge_sort(int *a, int n)
{
    if (n < 2) return;
    int *buf = malloc((size_t)n * sizeof *buf);
    if (!buf) return;                    /* ALWAYS check malloc. They watch. */
    merge_sort_rec(a, 0, n - 1, buf);
    free(buf);
}

/* =====================================================================
 * 5. QUICKSORT -- Lomuto partition (the one to write on a whiteboard)
 *
 * SAY: "Average O(n log n) with the best cache behaviour of the
 *       comparison sorts, but worst case O(n^2) if the pivot is chosen
 *       badly -- and on already-sorted input with a last-element pivot,
 *       that worst case is the COMMON case. So I pick a random or
 *       median-of-three pivot. It's in-place apart from O(log n) stack."
 *
 * Volunteering the sorted-input worst case before they ask is a strong move.
 * ------------------------------------------------------------------- */
static int partition_lomuto(int *a, int lo, int hi)
{
    /* median-of-three pivot, parked at hi */
    int mid = lo + (hi - lo) / 2;
    if (a[mid] < a[lo])  swap(&a[mid], &a[lo]);
    if (a[hi]  < a[lo])  swap(&a[hi],  &a[lo]);
    if (a[hi]  < a[mid]) swap(&a[hi],  &a[mid]);
    swap(&a[mid], &a[hi]);

    int pivot = a[hi];
    int i = lo - 1;                      /* boundary of the "<= pivot" region */
    for (int j = lo; j < hi; j++) {
        if (a[j] <= pivot) { i++; swap(&a[i], &a[j]); }
    }
    swap(&a[i + 1], &a[hi]);
    return i + 1;
}

static void quick_sort_rec(int *a, int lo, int hi)
{
    while (lo < hi) {
        if (hi - lo + 1 < 16) {          /* small partition -> insertion sort */
            insertion_sort(a + lo, hi - lo + 1);
            return;
        }
        int p = partition_lomuto(a, lo, hi);
        /* Recurse on the SMALLER side, loop on the larger.
         * This bounds stack depth at O(log n) -- say this out loud, it is
         * exactly the kind of memory-discipline point Thales cares about. */
        if (p - lo < hi - p) {
            quick_sort_rec(a, lo, p - 1);
            lo = p + 1;
        } else {
            quick_sort_rec(a, p + 1, hi);
            hi = p - 1;
        }
    }
}

void quick_sort(int *a, int n) { if (n > 1) quick_sort_rec(a, 0, n - 1); }

/* =====================================================================
 * 6. HEAPSORT
 *
 * SAY: "The only comparison sort that is BOTH guaranteed O(n log n) AND
 *       true O(1) auxiliary space -- no recursion stack if you sift
 *       iteratively. That combination is why it's my default when I need
 *       a hard worst-case bound on a memory-constrained target. It loses
 *       to quicksort in practice on cache locality, and it isn't stable."
 *
 * If they ask "one sort for a safety-critical embedded system", this is
 * the answer, and the reason is the bounded worst case, not the speed.
 * ------------------------------------------------------------------- */
static void sift_down(int *a, int start, int end)
{
    int root = start;
    while (2 * root + 1 <= end) {
        int child = 2 * root + 1;
        if (child + 1 <= end && a[child] < a[child + 1]) child++;
        if (a[root] >= a[child]) return;
        swap(&a[root], &a[child]);
        root = child;
    }
}

void heap_sort(int *a, int n)
{
    /* build max-heap: start at last parent, sift down. This is O(n), not
     * O(n log n) -- a classic follow-up question. */
    for (int start = n / 2 - 1; start >= 0; start--)
        sift_down(a, start, n - 1);

    for (int end = n - 1; end > 0; end--) {
        swap(&a[0], &a[end]);            /* max to the back */
        sift_down(a, 0, end - 1);
    }
}

/* =====================================================================
 * 7. COUNTING SORT  -- non-comparison, O(n + k)
 *
 * SAY: "Beats the O(n log n) comparison lower bound because it never
 *       compares two elements -- it uses the key as an index. Only valid
 *       when the key range k is small and known. For 8-bit sensor samples
 *       k is 256, so it's O(n) with a fixed 1 KB table, which is a very
 *       good trade on an MCU."
 *
 * That example is drawn from YOUR OWN thesis domain. Use it.
 * ------------------------------------------------------------------- */
void counting_sort(int *a, int n, int max_val)
{
    int k = max_val + 1;
    int *count = calloc((size_t)k, sizeof *count);
    if (!count) return;

    for (int i = 0; i < n; i++) count[a[i]]++;

    int idx = 0;
    for (int v = 0; v < k; v++)
        while (count[v]-- > 0) a[idx++] = v;

    free(count);
}

/* =====================================================================
 * 8. RADIX SORT (LSD, base 256)
 *
 * SAY: "O(d * n) where d is the number of digit passes -- for 32-bit keys
 *       in base 256 that's 4 passes, so it's effectively linear. It needs
 *       a stable inner sort, which is why the counting pass is written
 *       backwards. Base 256 means one byte per pass and a 256-entry
 *       histogram, which is the natural fit for byte-oriented hardware."
 * ------------------------------------------------------------------- */
void radix_sort(int *a, int n)
{
    if (n < 2) return;
    int *out = malloc((size_t)n * sizeof *out);
    if (!out) return;

    for (int shift = 0; shift < 32; shift += 8) {
        int count[256] = {0};

        for (int i = 0; i < n; i++)
            count[(a[i] >> shift) & 0xFF]++;

        /* prefix sums -> starting index of each bucket */
        for (int i = 1; i < 256; i++) count[i] += count[i - 1];

        /* iterate BACKWARDS to preserve stability -- this is the bug
         * everyone writes forwards and then can't explain. */
        for (int i = n - 1; i >= 0; i--)
            out[--count[(a[i] >> shift) & 0xFF]] = a[i];

        memcpy(a, out, (size_t)n * sizeof *a);
    }
    free(out);
}

/* =====================================================================
 * 9. BINARY SEARCH + lower_bound
 *
 * SAY: "mid = lo + (hi - lo) / 2 rather than (lo + hi) / 2, because the
 *       latter overflows once lo + hi exceeds INT_MAX. That's the bug
 *       that sat in the JDK's binarySearch for nine years."
 *
 * Say the overflow line. It is a five-second answer that reads as
 * 'this person has been bitten by real bugs'.
 * ------------------------------------------------------------------- */
int binary_search(const int *a, int n, int target)
{
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] <  target) lo = mid + 1;
        else                  hi = mid - 1;
    }
    return -1;
}

/* first index with a[i] >= target, else n */
int lower_bound(const int *a, int n, int target)
{
    int lo = 0, hi = n;                  /* note: half-open [lo, hi) */
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < target) lo = mid + 1;
        else                 hi = mid;
    }
    return lo;
}

/* =====================================================================
 * 10. qsort() -- the library one. Know the comparator trap.
 *
 * SAY: "The naive comparator 'return *x - *y' is a latent overflow bug:
 *       with INT_MIN and a positive value the subtraction wraps and the
 *       sign flips, so the sort silently produces wrong order. I always
 *       write it as explicit comparisons."
 * ------------------------------------------------------------------- */
int cmp_int(const void *pa, const void *pb)
{
    int x = *(const int *)pa, y = *(const int *)pb;
    return (x > y) - (x < y);            /* branchless, overflow-free */
}

/* =====================================================================
 * TEST HARNESS
 * ------------------------------------------------------------------- */
#define N 12
static const int SEED[N] = { 5, 2, 9, 1, 5, 6, 0, 11, 3, 8, 7, 4 };

static void run(const char *name, void (*fn)(int *, int))
{
    int a[N];
    memcpy(a, SEED, sizeof a);
    fn(a, N);
    print_arr(name, a, N);
    if (!is_sorted(a, N)) { printf("   *** FAILED: %s\n", name); exit(1); }
}

int main(void)
{
    printf("Input:                ");
    for (int i = 0; i < N; i++) printf("%d ", SEED[i]);
    printf("\n\n");

    run("insertion_sort",  insertion_sort);
    run("selection_sort",  selection_sort);
    run("bubble_sort",     bubble_sort);
    run("merge_sort",      merge_sort);
    run("quick_sort",      quick_sort);
    run("heap_sort",       heap_sort);
    run("radix_sort",      radix_sort);

    { /* counting sort needs the max */
        int a[N]; memcpy(a, SEED, sizeof a);
        counting_sort(a, N, 11);
        print_arr("counting_sort", a, N);
        if (!is_sorted(a, N)) { printf("   *** FAILED: counting\n"); return 1; }
    }

    { /* library qsort */
        int a[N]; memcpy(a, SEED, sizeof a);
        qsort(a, N, sizeof a[0], cmp_int);
        print_arr("qsort (libc)", a, N);
    }

    { /* searches on the sorted array */
        int a[N]; memcpy(a, SEED, sizeof a);
        merge_sort(a, N);
        printf("\nbinary_search(7)  -> index %d\n", binary_search(a, N, 7));
        printf("binary_search(99) -> index %d  (expect -1)\n", binary_search(a, N, 99));
        printf("lower_bound(5)    -> index %d  (first of the two 5s)\n", lower_bound(a, N, 5));
        printf("lower_bound(10)   -> index %d  (10 absent, points at 11)\n", lower_bound(a, N, 10));
    }

    /* edge cases -- run these, interviewers ask for them */
    { int e[1] = {42}; insertion_sort(e, 1); merge_sort(e, 1); quick_sort(e, 1); }
    { int *e = NULL;   merge_sort(e, 0);     quick_sort(e, 0);  }

    printf("\nAll sorts verified sorted. Edge cases (n=0, n=1) survived.\n");
    return 0;
}
