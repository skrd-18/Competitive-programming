/* =====================================================================
 * 03_data_structures.c  --  The CS2040C core, in C, on one page each.
 *
 * Build:  gcc -Wall -Wextra -O2 -o 03_data_structures 03_data_structures.c
 * Run:    ./03_data_structures
 *
 * Priority order for Friday, highest first:
 *   1. Linked list (reverse, cycle detect, middle)  <- most asked
 *   2. Stack / queue                                <- you already have
 *                                                      the ring buffer
 *   3. Hash table with chaining                     <- "how would you
 *                                                      store N keys fast"
 *   4. BST                                          <- recursion fluency
 *   5. Binary heap / priority queue                 <- ties to heapsort
 * ===================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

/* =====================================================================
 * 1. SINGLY LINKED LIST
 *
 * SAY: "Versus an array: O(1) insert and delete once you hold the node,
 *       but O(n) to find it, and no cache locality -- every hop is a
 *       potential cache miss. On an MCU I usually prefer a static array
 *       or a pool allocator over malloc'd nodes anyway, because heap
 *       fragmentation on a device that runs for months is a real failure
 *       mode."
 * ------------------------------------------------------------------- */
typedef struct node {
    int data;
    struct node *next;
} node_t;

static node_t *list_push_front(node_t *head, int v)
{
    node_t *n = malloc(sizeof *n);
    if (!n) return head;                  /* check every malloc */
    n->data = v;
    n->next = head;
    return n;
}

static void list_print(const char *label, const node_t *h)
{
    printf("%-20s", label);
    for (const node_t *p = h; p; p = p->next) printf("%d -> ", p->data);
    puts("NULL");
}

static void list_free(node_t *h)
{
    while (h) { node_t *nx = h->next; free(h); h = nx; }
}

/* --- REVERSE: the single most asked linked-list question ------------
 * Three pointers. Draw it before you type it -- interviewers explicitly
 * like seeing you draw prev/curr/next before writing the loop. */
static node_t *list_reverse(node_t *head)
{
    node_t *prev = NULL, *curr = head;
    while (curr) {
        node_t *next = curr->next;        /* save before we clobber it */
        curr->next   = prev;              /* flip the arrow */
        prev = curr;                      /* advance */
        curr = next;
    }
    return prev;                          /* prev is the new head */
}

/* --- CYCLE DETECTION: Floyd's tortoise and hare ---------------------
 * SAY: "O(n) time, O(1) space. The slow pointer moves one, the fast
 *       moves two; if there is a cycle the gap closes by one each step so
 *       they must meet. The alternative -- a hash set of visited nodes --
 *       is also O(n) time but O(n) space, which I can't afford on a
 *       microcontroller." */
static bool list_has_cycle(const node_t *head)
{
    const node_t *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

/* --- MIDDLE NODE, one pass, same two-pointer idea ------------------- */
static const node_t *list_middle(const node_t *head)
{
    const node_t *slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow;                          /* upper middle when even length */
}

/* =====================================================================
 * 2. STACK (array-backed, fixed capacity -- the embedded way)
 *
 * SAY: "Fixed capacity, no malloc, so the memory cost is known at link
 *       time. On a constrained target I want every allocation visible in
 *       the map file, not decided at runtime."
 * ------------------------------------------------------------------- */
#define STACK_CAP 32
typedef struct { int buf[STACK_CAP]; int top; } stack_t;

static void stack_init(stack_t *s) { s->top = 0; }
static bool stack_push(stack_t *s, int v)
{
    if (s->top >= STACK_CAP) return false;      /* overflow guard */
    s->buf[s->top++] = v; return true;
}
static bool stack_pop(stack_t *s, int *out)
{
    if (s->top <= 0) return false;              /* underflow guard */
    *out = s->buf[--s->top]; return true;
}

/* Classic use: balanced-bracket check. Good warm-up answer. */
static bool brackets_balanced(const char *s)
{
    stack_t st; stack_init(&st);
    for (; *s; s++) {
        if (*s=='('||*s=='['||*s=='{') {
            if (!stack_push(&st, *s)) return false;
        } else if (*s==')'||*s==']'||*s=='}') {
            int o;
            if (!stack_pop(&st, &o)) return false;
            if ((*s==')'&&o!='(') || (*s==']'&&o!='[') || (*s=='}'&&o!='{'))
                return false;
        }
    }
    return st.top == 0;
}

/* =====================================================================
 * 3. HASH TABLE with separate chaining
 *
 * SAY: "Average O(1) lookup, worst case O(n) if everything collides.
 *       Separate chaining degrades gracefully and handles deletion
 *       cleanly; open addressing has better cache behaviour but deletion
 *       needs tombstones. I size the table to a power of two so the
 *       modulo is a mask, and I'd resize when the load factor passes
 *       about 0.75."
 *
 * The hash below is FNV-1a: tiny, no tables, good distribution. Naming a
 * specific hash rather than saying "some hash function" reads well.
 * ------------------------------------------------------------------- */
#define HT_BUCKETS 16                     /* power of two */
#define HT_MASK    (HT_BUCKETS - 1)

typedef struct ht_entry {
    char key[24];
    int  value;
    struct ht_entry *next;
} ht_entry_t;

typedef struct { ht_entry_t *bucket[HT_BUCKETS]; } hashtable_t;

static uint32_t fnv1a(const char *s)
{
    uint32_t h = 2166136261u;             /* FNV offset basis */
    while (*s) { h ^= (uint8_t)*s++; h *= 16777619u; }   /* FNV prime */
    return h;
}

static void ht_init(hashtable_t *t) { memset(t, 0, sizeof *t); }

static bool ht_put(hashtable_t *t, const char *key, int value)
{
    uint32_t b = fnv1a(key) & HT_MASK;
    for (ht_entry_t *e = t->bucket[b]; e; e = e->next)
        if (strcmp(e->key, key) == 0) { e->value = value; return true; } /* update */

    ht_entry_t *e = malloc(sizeof *e);
    if (!e) return false;
    snprintf(e->key, sizeof e->key, "%s", key);
    e->value = value;
    e->next  = t->bucket[b];              /* prepend: O(1) */
    t->bucket[b] = e;
    return true;
}

static bool ht_get(const hashtable_t *t, const char *key, int *out)
{
    uint32_t b = fnv1a(key) & HT_MASK;
    for (ht_entry_t *e = t->bucket[b]; e; e = e->next)
        if (strcmp(e->key, key) == 0) { *out = e->value; return true; }
    return false;
}

static void ht_free(hashtable_t *t)
{
    for (int i = 0; i < HT_BUCKETS; i++) {
        ht_entry_t *e = t->bucket[i];
        while (e) { ht_entry_t *nx = e->next; free(e); e = nx; }
        t->bucket[i] = NULL;
    }
}

/* =====================================================================
 * 4. BINARY SEARCH TREE
 *
 * SAY: "O(log n) average, but O(n) if the input arrives sorted -- the
 *       tree degenerates into a linked list. That's exactly why AVL and
 *       red-black trees exist: they rebalance on insert to keep the
 *       height logarithmic. In-order traversal yields sorted output, which
 *       is the property that makes a BST worth the pointers over a hash
 *       table."
 * ------------------------------------------------------------------- */
typedef struct bst_node {
    int key;
    struct bst_node *left, *right;
} bst_node_t;

static bst_node_t *bst_insert(bst_node_t *root, int key)
{
    if (!root) {
        bst_node_t *n = malloc(sizeof *n);
        if (!n) return NULL;
        n->key = key; n->left = n->right = NULL;
        return n;
    }
    if      (key < root->key) root->left  = bst_insert(root->left,  key);
    else if (key > root->key) root->right = bst_insert(root->right, key);
    /* equal -> ignore duplicates */
    return root;
}

static bool bst_search(const bst_node_t *root, int key)
{
    while (root) {
        if (key == root->key) return true;
        root = (key < root->key) ? root->left : root->right;
    }
    return false;                         /* iterative: no stack growth */
}

static void bst_inorder(const bst_node_t *root)
{
    if (!root) return;
    bst_inorder(root->left);
    printf("%d ", root->key);
    bst_inorder(root->right);
}

static int bst_height(const bst_node_t *root)
{
    if (!root) return 0;
    int l = bst_height(root->left), r = bst_height(root->right);
    return 1 + (l > r ? l : r);
}

static void bst_free(bst_node_t *root)
{
    if (!root) return;
    bst_free(root->left); bst_free(root->right); free(root);
}

/* =====================================================================
 * 5. BINARY MIN-HEAP / PRIORITY QUEUE (array-backed)
 *
 * SAY: "Stored as an array, so no pointers and no allocator: for index i,
 *       parent is (i-1)/2 and children are 2i+1 and 2i+2. Insert and
 *       extract are O(log n), peek is O(1). On embedded this is how I'd
 *       build a software timer queue -- next-expiry at the root."
 *
 * That timer-queue example is a strong, concrete embedded answer.
 * ------------------------------------------------------------------- */
#define HEAP_CAP 64
typedef struct { int a[HEAP_CAP]; int n; } minheap_t;

static void heap_init(minheap_t *h) { h->n = 0; }

static bool heap_push(minheap_t *h, int v)
{
    if (h->n >= HEAP_CAP) return false;
    int i = h->n++;
    h->a[i] = v;
    while (i > 0) {                       /* sift up */
        int p = (i - 1) / 2;
        if (h->a[p] <= h->a[i]) break;
        int t = h->a[p]; h->a[p] = h->a[i]; h->a[i] = t;
        i = p;
    }
    return true;
}

static bool heap_pop(minheap_t *h, int *out)
{
    if (h->n == 0) return false;
    *out = h->a[0];
    h->a[0] = h->a[--h->n];
    int i = 0;
    for (;;) {                            /* sift down */
        int l = 2*i + 1, r = 2*i + 2, m = i;
        if (l < h->n && h->a[l] < h->a[m]) m = l;
        if (r < h->n && h->a[r] < h->a[m]) m = r;
        if (m == i) break;
        int t = h->a[m]; h->a[m] = h->a[i]; h->a[i] = t;
        i = m;
    }
    return true;
}

/* =====================================================================
 * MAIN
 * ------------------------------------------------------------------- */
int main(void)
{
    puts("=== 1. Linked list ===");
    node_t *head = NULL;
    for (int i = 5; i >= 1; i--) head = list_push_front(head, i);
    list_print("original:", head);
    head = list_reverse(head);
    list_print("reversed:", head);
    printf("has cycle?  %s\n", list_has_cycle(head) ? "yes" : "no");
    printf("middle node: %d\n", list_middle(head)->data);

    /* deliberately build a cycle, detect it, then break it before free */
    { node_t *tail = head; while (tail->next) tail = tail->next;
      tail->next = head->next;            /* create loop */
      printf("after making a loop, has cycle? %s\n",
             list_has_cycle(head) ? "yes" : "no");
      tail->next = NULL; }                /* break it or free() loops forever */
    list_free(head);

    puts("\n=== 2. Stack / brackets ===");
    printf("\"{[()]}\"  -> %s\n", brackets_balanced("{[()]}")  ? "balanced" : "NOT balanced");
    printf("\"{[(])}\"  -> %s\n", brackets_balanced("{[(])}")  ? "balanced" : "NOT balanced");
    printf("\"(()\"     -> %s\n", brackets_balanced("(()")     ? "balanced" : "NOT balanced");

    puts("\n=== 3. Hash table ===");
    hashtable_t ht; ht_init(&ht);
    ht_put(&ht, "APDU",   0x9000);
    ht_put(&ht, "applet", 42);
    ht_put(&ht, "APDU",   0x6A82);        /* overwrite */
    /* NOTE -- I wrote this the "clever" way first:
     *     printf("%s 0x%04X\n", ht_get(&ht,"APDU",&v)?"found":"missing", v);
     * and it printed GARBAGE. The order in which a compiler evaluates
     * function arguments is UNSPECIFIED in C, so `v` was read before
     * ht_get() had written it. Never call a function and read its
     * out-parameter in the same argument list. Sequence points are a
     * favourite interview topic -- if you get handed buggy code to review,
     * this family of bug is a very likely plant. */
    { int v = 0;
      bool ok = ht_get(&ht, "APDU", &v);
      printf("get(\"APDU\")   -> %s 0x%04X\n", ok ? "found" : "missing", v);
      ok = ht_get(&ht, "applet", &v);
      printf("get(\"applet\") -> %s %d\n",     ok ? "found" : "missing", v);
      ok = ht_get(&ht, "nope", &v);
      printf("get(\"nope\")   -> %s\n",        ok ? "found" : "missing"); }
    ht_free(&ht);

    puts("\n=== 4. BST ===");
    bst_node_t *root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (unsigned i = 0; i < sizeof keys / sizeof *keys; i++)
        root = bst_insert(root, keys[i]);
    printf("in-order (sorted): "); bst_inorder(root); putchar('\n');
    printf("height = %d  (balanced-ish)\n", bst_height(root));
    printf("search(40) = %s, search(45) = %s\n",
           bst_search(root, 40) ? "found" : "missing",
           bst_search(root, 45) ? "found" : "missing");
    bst_free(root);

    /* degenerate case -- show you know it */
    root = NULL;
    for (int i = 1; i <= 7; i++) root = bst_insert(root, i);
    printf("sorted input -> height = %d  <-- degenerated to a linked list\n",
           bst_height(root));
    bst_free(root);

    puts("\n=== 5. Min-heap ===");
    minheap_t h; heap_init(&h);
    int vals[] = {9, 4, 7, 1, 8, 2};
    for (unsigned i = 0; i < sizeof vals / sizeof *vals; i++) heap_push(&h, vals[i]);
    printf("popped in order: ");
    { int v; while (heap_pop(&h, &v)) printf("%d ", v); }
    putchar('\n');

    puts("\nAll structures exercised.");
    return 0;
}
