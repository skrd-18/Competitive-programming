#!/usr/bin/env python3
"""
05_algorithms.py -- Fast-recall algorithm reference.

Run:  python3 05_algorithms.py          (every function is self-tested)

=============================================================================
READ THIS BEFORE YOU USE IT
=============================================================================
Friday's interview is in C. Thales asks for "Proficient in C/Java" and this is
an embedded role -- if you answer a live-coding question in Python without
being invited to, you have answered the wrong question.

So why this file exists: Python is the fastest medium for burning the LOGIC
into memory. You can write insertion sort in Python in 30 seconds and in C in
three minutes. Use Python to get the algorithm right in your head, then
immediately write the same thing in C. Logic in Python, muscle memory in C.

Each function carries a "IN C:" note -- the thing that changes when you
translate it. Those notes are the actual interview content.

If they DO offer you a choice of language: pick C. It is the language of the
job, your resume says C is your primary, and choosing Python would undercut
that. Only pick Python if they explicitly ask for it.
=============================================================================
"""

from collections import deque, Counter, defaultdict
import heapq

# =============================================================================
# 1. SORTING
# =============================================================================

def insertion_sort(a):
    """O(n^2), O(n) on sorted input, O(1) space, STABLE.
    IN C: identical structure. The Python `a[j] > key` shift loop becomes the
    same while loop -- watch the `j >= 0` guard, that's the off-by-one they
    look for."""
    for i in range(1, len(a)):
        key, j = a[i], i - 1
        while j >= 0 and a[j] > key:      # '>' not '>=' keeps it stable
            a[j + 1] = a[j]
            j -= 1
        a[j + 1] = key
    return a


def selection_sort(a):
    """O(n^2) always, but at most n-1 WRITES.
    IN C: this is the one you pick when writes hit EEPROM/flash endurance."""
    n = len(a)
    for i in range(n - 1):
        m = min(range(i, n), key=lambda k: a[k])
        if m != i:
            a[i], a[m] = a[m], a[i]
    return a


def bubble_sort(a):
    """O(n^2), early-exit makes it O(n) on sorted input. Never actually use it."""
    n = len(a)
    for i in range(n - 1):
        swapped = False
        for j in range(n - 1 - i):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                swapped = True
        if not swapped:
            break
    return a


def merge_sort(a):
    """O(n log n) guaranteed, STABLE, O(n) space.
    IN C: allocate the scratch buffer ONCE at the top level, not inside
    merge(). A malloc per merge call is slow and a fragmentation risk."""
    if len(a) < 2:
        return a
    mid = len(a) // 2
    left, right = merge_sort(a[:mid]), merge_sort(a[mid:])
    out, i, j = [], 0, 0
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:          # '<=' keeps it stable
            out.append(left[i]); i += 1
        else:
            out.append(right[j]); j += 1
    out.extend(left[i:]); out.extend(right[j:])
    return out


def quick_sort(a, lo=0, hi=None):
    """Average O(n log n), WORST O(n^2) on sorted input with a bad pivot.
    IN C: median-of-three pivot, and recurse on the SMALLER partition while
    looping on the larger -- that bounds stack depth at O(log n), which is the
    detail that matters on an MCU."""
    if hi is None:
        hi = len(a) - 1
    while lo < hi:
        # median-of-three, parked at hi
        mid = lo + (hi - lo) // 2
        if a[mid] < a[lo]:  a[mid], a[lo] = a[lo], a[mid]
        if a[hi] < a[lo]:   a[hi], a[lo]  = a[lo], a[hi]
        if a[hi] < a[mid]:  a[hi], a[mid] = a[mid], a[hi]
        a[mid], a[hi] = a[hi], a[mid]

        pivot, i = a[hi], lo - 1
        for j in range(lo, hi):
            if a[j] <= pivot:
                i += 1
                a[i], a[j] = a[j], a[i]
        a[i + 1], a[hi] = a[hi], a[i + 1]
        p = i + 1

        if p - lo < hi - p:              # recurse smaller, loop larger
            quick_sort(a, lo, p - 1); lo = p + 1
        else:
            quick_sort(a, p + 1, hi); hi = p - 1
    return a


def heap_sort(a):
    """O(n log n) guaranteed AND O(1) space -- the only sort with both.
    THE answer for a memory-constrained target needing a hard bound.
    IN C: same index arithmetic. parent (i-1)//2, children 2i+1 / 2i+2."""
    n = len(a)

    def sift_down(root, end):
        while 2 * root + 1 <= end:
            child = 2 * root + 1
            if child + 1 <= end and a[child] < a[child + 1]:
                child += 1
            if a[root] >= a[child]:
                return
            a[root], a[child] = a[child], a[root]
            root = child

    for start in range(n // 2 - 1, -1, -1):   # build heap is O(n), not O(n log n)
        sift_down(start, n - 1)
    for end in range(n - 1, 0, -1):
        a[0], a[end] = a[end], a[0]
        sift_down(0, end - 1)
    return a


def counting_sort(a, max_val):
    """O(n + k). Beats the n log n lower bound because it INDEXES, never compares.
    IN C: a fixed 256-entry table for 8-bit sensor samples -- your thesis domain."""
    count = [0] * (max_val + 1)
    for v in a:
        count[v] += 1
    out = []
    for v, c in enumerate(count):
        out.extend([v] * c)
    return out


def radix_sort(a):
    """O(d*n) -- 4 passes for 32-bit keys in base 256.
    IN C: the counting pass must iterate BACKWARDS to stay stable. That's the
    bug everyone writes forwards and then can't explain."""
    if len(a) < 2:
        return a
    out = a[:]
    for shift in (0, 8, 16, 24):
        count = [0] * 256
        for v in out:
            count[(v >> shift) & 0xFF] += 1
        for i in range(1, 256):
            count[i] += count[i - 1]
        buf = [0] * len(out)
        for v in reversed(out):                 # BACKWARDS = stable
            b = (v >> shift) & 0xFF
            count[b] -= 1
            buf[count[b]] = v
        out = buf
    return out


# =============================================================================
# 2. SEARCH
# =============================================================================

def binary_search(a, target):
    """IN C: mid = lo + (hi-lo)//2, NEVER (lo+hi)//2 -- overflows in C.
    Python ints don't overflow, which is exactly why you must remember this
    consciously rather than relying on the Python version feeling fine."""
    lo, hi = 0, len(a) - 1
    while lo <= hi:
        mid = lo + (hi - lo) // 2
        if a[mid] == target:
            return mid
        if a[mid] < target:
            lo = mid + 1
        else:
            hi = mid - 1
    return -1


def lower_bound(a, target):
    """First index with a[i] >= target, else len(a). Half-open [lo, hi)."""
    lo, hi = 0, len(a)
    while lo < hi:
        mid = lo + (hi - lo) // 2
        if a[mid] < target:
            lo = mid + 1
        else:
            hi = mid
    return lo


# =============================================================================
# 3. TWO POINTERS  -- the reported Thales question style
# =============================================================================

def dedup_sorted(a):
    """In-place on sorted input. O(n) time, O(1) space. Returns new length.
    ASK FIRST: is it sorted? must order be preserved?"""
    if len(a) <= 1:
        return len(a)
    w = 1
    for r in range(1, len(a)):
        if a[r] != a[w - 1]:
            a[w] = a[r]
            w += 1
    return w


def dedup_unsorted_stable(a):
    """Order-preserving, O(n) time WITH a set (O(n) space).
    IN C: no set available -- you write the O(n^2) scan, or sort first and
    lose the order. Say that trade-off out loud."""
    seen, out = set(), []
    for v in a:
        if v not in seen:
            seen.add(v)
            out.append(v)
    return out


def reverse_in_place(a):
    i, j = 0, len(a) - 1
    while i < j:
        a[i], a[j] = a[j], a[i]
        i += 1
        j -= 1
    return a


def is_palindrome(s):
    i, j = 0, len(s) - 1
    while i < j:
        if s[i] != s[j]:
            return False
        i += 1
        j -= 1
    return True


def two_sum_sorted(a, target):
    """O(n), O(1) space -- only works because the input is sorted."""
    i, j = 0, len(a) - 1
    while i < j:
        s = a[i] + a[j]
        if s == target:
            return (i, j)
        if s < target:
            i += 1
        else:
            j -= 1
    return None


def two_sum_hash(a, target):
    """O(n) time, O(n) space -- works on UNSORTED input."""
    seen = {}
    for i, v in enumerate(a):
        if target - v in seen:
            return (seen[target - v], i)
        seen[v] = i
    return None


def move_zeros_to_end(a):
    """Stable partition, in place. Classic warm-up."""
    w = 0
    for r in range(len(a)):
        if a[r] != 0:
            a[w], a[r] = a[r], a[w]
            w += 1
    return a


# =============================================================================
# 4. SLIDING WINDOW
# =============================================================================

def max_sum_window(a, k):
    """Fixed window. O(n) instead of the O(n*k) brute force."""
    if len(a) < k:
        return None
    s = sum(a[:k])
    best = s
    for i in range(k, len(a)):
        s += a[i] - a[i - k]         # add the new, drop the old
        best = max(best, s)
    return best


def longest_unique_substring(s):
    """Variable window. O(n)."""
    last, start, best = {}, 0, 0
    for i, c in enumerate(s):
        if c in last and last[c] >= start:
            start = last[c] + 1
        last[c] = i
        best = max(best, i - start + 1)
    return best


def kadane(a):
    """Max subarray sum. O(n). The classic DP-in-one-line."""
    best = cur = a[0]
    for v in a[1:]:
        cur = max(v, cur + v)
        best = max(best, cur)
    return best


def prefix_sums(a):
    """p[i] = sum of a[:i]. Range sum a[i:j] = p[j] - p[i], O(1) per query."""
    p = [0]
    for v in a:
        p.append(p[-1] + v)
    return p


# =============================================================================
# 5. LINKED LIST
# =============================================================================

class Node:
    __slots__ = ('val', 'next')
    def __init__(self, val, nxt=None):
        self.val, self.next = val, nxt


def build_list(vals):
    head = None
    for v in reversed(vals):
        head = Node(v, head)
    return head


def to_list(head):
    out = []
    while head:
        out.append(head.val)
        head = head.next
    return out


def reverse_list(head):
    """THE most-asked pointer question. Draw prev/curr/next before you type.
    IN C: identical. node_t *prev = NULL, *curr = head, *next;"""
    prev, curr = None, head
    while curr:
        nxt = curr.next        # save before clobbering
        curr.next = prev       # flip the arrow
        prev, curr = curr, nxt
    return prev


def has_cycle(head):
    """Floyd. O(n) time, O(1) space -- a visited-set is O(n) space, which you
    can't afford on an MCU. Slow +1, fast +2; the gap closes by 1 each step."""
    slow = fast = head
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next
        if slow is fast:
            return True
    return False


def middle_node(head):
    """Same two-pointer trick, no equality test. Upper middle on even length."""
    slow = fast = head
    while fast and fast.next:
        slow, fast = slow.next, fast.next.next
    return slow


def merge_two_sorted(a, b):
    """Merge two sorted lists. Dummy head removes the special case."""
    dummy = tail = Node(0)
    while a and b:
        if a.val <= b.val:
            tail.next, a = a, a.next
        else:
            tail.next, b = b, b.next
        tail = tail.next
    tail.next = a or b
    return dummy.next


# =============================================================================
# 6. STACK & QUEUE
# =============================================================================

def brackets_balanced(s):
    pairs = {')': '(', ']': '[', '}': '{'}
    stack = []
    for c in s:
        if c in '([{':
            stack.append(c)
        elif c in pairs:
            if not stack or stack.pop() != pairs[c]:
                return False
    return not stack


class MinStack:
    """push/pop/min all O(1). Trick: a parallel stack of running minima."""
    def __init__(self):
        self._s, self._m = [], []
    def push(self, v):
        self._s.append(v)
        self._m.append(v if not self._m else min(v, self._m[-1]))
    def pop(self):
        self._m.pop()
        return self._s.pop()
    def min(self):
        return self._m[-1]


class RingBuffer:
    """Circular queue == the embedded ring buffer. Say that out loud.
    IN C: power-of-two capacity so the wrap is a MASK not a modulo (no
    division on Cortex-M0); one slot left empty so full != empty without a
    separate count; head/tail volatile; single producer + single consumer
    means NO lock is needed."""
    def __init__(self, size=8):
        assert size & (size - 1) == 0, "capacity must be a power of two"
        self.buf = [None] * size
        self.mask = size - 1
        self.head = self.tail = 0
    def is_empty(self):
        return self.head == self.tail
    def is_full(self):
        return ((self.head + 1) & self.mask) == self.tail
    def push(self, v):
        if self.is_full():
            return False                       # drop, never block
        self.buf[self.head] = v
        self.head = (self.head + 1) & self.mask  # publish index LAST
        return True
    def pop(self):
        if self.is_empty():
            return None
        v = self.buf[self.tail]
        self.tail = (self.tail + 1) & self.mask
        return v


# =============================================================================
# 7. HASHING
# =============================================================================

def group_anagrams(words):
    """Sort each word to make the key. O(n * k log k)."""
    groups = defaultdict(list)
    for w in words:
        groups[''.join(sorted(w))].append(w)
    return list(groups.values())


def first_non_repeating(s):
    counts = Counter(s)
    for c in s:
        if counts[c] == 1:
            return c
    return None


def fnv1a(s):
    """The hash to NAME when asked. Tiny, no tables, good distribution.
    IN C: the & 0xFFFFFFFF is free -- uint32_t wraps for you."""
    h = 2166136261                      # FNV offset basis
    for ch in s.encode():
        h = ((h ^ ch) * 16777619) & 0xFFFFFFFF   # FNV prime
    return h


# =============================================================================
# 8. HEAP / PRIORITY QUEUE
# =============================================================================

def k_largest(a, k):
    """O(n log k) with a size-k min-heap -- beats sorting when k << n."""
    return heapq.nlargest(k, a)


def merge_k_sorted(lists):
    """O(N log k). heapq.merge does it lazily."""
    return list(heapq.merge(*lists))


def running_median_demo(stream):
    """Two heaps: max-heap of the low half, min-heap of the high half.
    A classic follow-up. IN C you'd hand-roll both heaps."""
    low, high, out = [], [], []          # low is negated for max-heap behaviour
    for v in stream:
        heapq.heappush(low, -v)
        heapq.heappush(high, -heapq.heappop(low))
        if len(high) > len(low):
            heapq.heappush(low, -heapq.heappop(high))
        out.append(-low[0] if len(low) > len(high) else (-low[0] + high[0]) / 2)
    return out


# =============================================================================
# 9. BST
# =============================================================================

class BST:
    class _N:
        __slots__ = ('k', 'l', 'r')
        def __init__(self, k):
            self.k, self.l, self.r = k, None, None

    def __init__(self):
        self.root = None

    def insert(self, k):
        def go(n, k):
            if n is None:
                return BST._N(k)
            if k < n.k:
                n.l = go(n.l, k)
            elif k > n.k:
                n.r = go(n.r, k)
            return n
        self.root = go(self.root, k)

    def search(self, k):
        n = self.root
        while n:                       # iterative -> no stack growth
            if k == n.k:
                return True
            n = n.l if k < n.k else n.r
        return False

    def inorder(self):
        out = []
        def go(n):
            if n:
                go(n.l); out.append(n.k); go(n.r)
        go(self.root)
        return out                     # sorted -- that's the whole point

    def height(self):
        def go(n):
            return 0 if n is None else 1 + max(go(n.l), go(n.r))
        return go(self.root)


# =============================================================================
# 10. GRAPHS  (low priority for Friday, cheap to know)
# =============================================================================

def bfs(graph, start):
    """Shortest path in EDGES on an unweighted graph. Queue."""
    seen, order, q = {start}, [], deque([start])
    while q:
        node = q.popleft()
        order.append(node)
        for nxt in graph.get(node, ()):
            if nxt not in seen:
                seen.add(nxt)
                q.append(nxt)
    return order


def dfs(graph, start):
    """Stack (or recursion). Note: iterative version to avoid stack depth."""
    seen, order, stack = set(), [], [start]
    while stack:
        node = stack.pop()
        if node in seen:
            continue
        seen.add(node)
        order.append(node)
        stack.extend(reversed(graph.get(node, ())))
    return order


# =============================================================================
# 11. BIT MANIPULATION
# =============================================================================

def set_bit(v, n):    return v | (1 << n)
def clear_bit(v, n):  return v & ~(1 << n)
def toggle_bit(v, n): return v ^ (1 << n)
def test_bit(v, n):   return (v >> n) & 1

def popcount(v):
    """Kernighan: one iteration per SET bit, not per bit."""
    c = 0
    while v:
        v &= v - 1                     # clears the lowest set bit
        c += 1
    return c

def is_power_of_two(v):
    return v > 0 and (v & (v - 1)) == 0

def swap32(v):
    """Endian swap. IN C: mask each byte with 0xFF after shifting."""
    return (((v >> 24) & 0xFF) | ((v >> 8) & 0xFF00) |
            ((v << 8) & 0xFF0000) | ((v << 24) & 0xFF000000)) & 0xFFFFFFFF

def store_be32(v):
    """Serialise big-endian. NEVER cast a struct over a byte stream."""
    return bytes([(v >> 24) & 0xFF, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF])

def load_be32(b):
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3]


# =============================================================================
# 12. RECURSION / DP  (lowest priority -- Thales reportedly doesn't ask this)
# =============================================================================

def fib_memo(n, memo=None):
    if memo is None:
        memo = {}
    if n < 2:
        return n
    if n not in memo:
        memo[n] = fib_memo(n - 1, memo) + fib_memo(n - 2, memo)
    return memo[n]


def fib_iterative(n):
    """O(1) space. Prefer this -- and on an MCU, always prefer iteration."""
    a, b = 0, 1
    for _ in range(n):
        a, b = b, a + b
    return a


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


# =============================================================================
# 13. THE THALES-STYLE OUTPUT-FORMATTING QUESTIONS
# =============================================================================

def pyramid(rows, ch='*'):
    """Reported Thales question. The algorithm is trivial; the MARKS are in
    exact output. ASK: centred? trailing spaces? newline at the end?"""
    lines = []
    for i in range(1, rows + 1):
        lines.append(' ' * (rows - i) + ch * (2 * i - 1))
    return '\n'.join(lines)


def pyramid_letters(rows):
    """Row i uses letter i -- the 'char array' variant."""
    return '\n'.join(' ' * (rows - i) + chr(ord('A') + i - 1) * (2 * i - 1)
                     for i in range(1, rows + 1))


# =============================================================================
# SELF-TEST
# =============================================================================

def _main():
    S = [5, 2, 9, 1, 5, 6, 0, 11, 3, 8, 7, 4]
    E = sorted(S)
    ok = lambda name, got, want: print(f"  {'PASS' if got == want else '**FAIL**'}  {name}")

    print("1. SORTING")
    for fn in (insertion_sort, selection_sort, bubble_sort, quick_sort, heap_sort):
        ok(fn.__name__, fn(S[:]), E)
    ok("merge_sort", merge_sort(S[:]), E)
    ok("counting_sort", counting_sort(S[:], 11), E)
    ok("radix_sort", radix_sort(S[:]), E)
    ok("edge n=0", insertion_sort([]), [])
    ok("edge n=1", merge_sort([42]), [42])
    ok("all equal", quick_sort([7] * 20), [7] * 20)
    ok("reverse sorted", heap_sort(list(range(50, 0, -1))), list(range(1, 51)))

    print("\n2. SEARCH")
    ok("binary_search hit", binary_search(E, 7), E.index(7))
    ok("binary_search miss", binary_search(E, 99), -1)
    ok("lower_bound dup", lower_bound(E, 5), E.index(5))
    ok("lower_bound absent", lower_bound(E, 10), 11)

    print("\n3. TWO POINTERS")
    d = [1, 1, 2, 3, 3, 3, 4, 5, 5]
    n = dedup_sorted(d)
    ok("dedup_sorted", d[:n], [1, 2, 3, 4, 5])
    ok("dedup_unsorted", dedup_unsorted_stable([5, 1, 5, 2, 1, 9]), [5, 1, 2, 9])
    ok("reverse", reverse_in_place([1, 2, 3, 4]), [4, 3, 2, 1])
    ok("palindrome", (is_palindrome("level"), is_palindrome("levels")), (True, False))
    ok("two_sum_sorted", two_sum_sorted([1, 3, 5, 7, 9], 12), (1, 4))   # 3 + 9
    ok("two_sum_sorted none", two_sum_sorted([1, 2, 3], 99), None)
    ok("two_sum_hash", two_sum_hash([9, 3, 7, 1], 10), (1, 2))
    ok("move_zeros", move_zeros_to_end([0, 1, 0, 3, 12]), [1, 3, 12, 0, 0])

    print("\n4. WINDOWS")
    ok("max_sum_window", max_sum_window([2, 1, 5, 1, 3, 2], 3), 9)
    ok("longest_unique", longest_unique_substring("abcabcbb"), 3)
    ok("kadane", kadane([-2, 1, -3, 4, -1, 2, 1, -5, 4]), 6)
    ok("prefix_sums", prefix_sums([1, 2, 3]), [0, 1, 3, 6])

    print("\n5. LINKED LIST")
    h = build_list([1, 2, 3, 4, 5])
    ok("reverse_list", to_list(reverse_list(h)), [5, 4, 3, 2, 1])
    h = build_list([1, 2, 3, 4, 5])
    ok("middle_node", middle_node(h).val, 3)
    ok("no cycle", has_cycle(h), False)
    tail = h
    while tail.next:
        tail = tail.next
    tail.next = h.next                       # make a loop
    ok("has cycle", has_cycle(h), True)
    tail.next = None
    ok("merge_two_sorted",
       to_list(merge_two_sorted(build_list([1, 3, 5]), build_list([2, 4, 6]))),
       [1, 2, 3, 4, 5, 6])

    print("\n6. STACK & QUEUE")
    ok("brackets ok", brackets_balanced("{[()]}"), True)
    ok("brackets bad", brackets_balanced("{[(])}"), False)
    ok("brackets short", brackets_balanced("(()"), False)
    ms = MinStack()
    for v in (5, 2, 8, 1):
        ms.push(v)
    ok("MinStack.min", ms.min(), 1)
    ms.pop()
    ok("MinStack after pop", ms.min(), 2)
    rb = RingBuffer(8)
    pushed = sum(rb.push(i) for i in range(1, 11))
    ok("ring capacity", pushed, 7)               # one slot reserved
    ok("ring FIFO", [rb.pop() for _ in range(7)], [1, 2, 3, 4, 5, 6, 7])
    ok("ring empty", rb.pop(), None)
    rb.push(99); rb.push(100)
    ok("ring wrap", rb.pop(), 99)

    print("\n7. HASHING")
    ok("group_anagrams",
       sorted(sorted(g) for g in group_anagrams(["eat", "tea", "tan", "ate", "nat"])),
       sorted(sorted(g) for g in [["eat", "tea", "ate"], ["tan", "nat"]]))
    ok("first_non_repeating", first_non_repeating("swiss"), 'w')
    ok("fnv1a deterministic", fnv1a("APDU") == fnv1a("APDU"), True)
    ok("fnv1a 32-bit", fnv1a("Thales") < 2**32, True)

    print("\n8. HEAP")
    ok("k_largest", sorted(k_largest(S, 3)), [8, 9, 11])
    ok("merge_k_sorted", merge_k_sorted([[1, 4], [2, 5], [3, 6]]), [1, 2, 3, 4, 5, 6])
    ok("running_median", running_median_demo([1, 2, 3, 4]), [1, 1.5, 2, 2.5])

    print("\n9. BST")
    t = BST()
    for k in (50, 30, 70, 20, 40, 60, 80):
        t.insert(k)
    ok("inorder sorted", t.inorder(), [20, 30, 40, 50, 60, 70, 80])
    ok("search hit/miss", (t.search(40), t.search(45)), (True, False))
    ok("balanced height", t.height(), 3)
    deg = BST()
    for k in range(1, 8):
        deg.insert(k)
    ok("degenerate height", deg.height(), 7)      # sorted input -> linked list

    print("\n10. GRAPHS")
    g = {'A': ['B', 'C'], 'B': ['D'], 'C': ['D', 'E'], 'D': ['E'], 'E': []}
    ok("bfs", bfs(g, 'A'), ['A', 'B', 'C', 'D', 'E'])
    ok("dfs", dfs(g, 'A'), ['A', 'B', 'D', 'E', 'C'])

    print("\n11. BITS")
    ok("set/clear/toggle", (set_bit(0, 3), clear_bit(0xFF, 0), toggle_bit(0b1010, 1)),
       (8, 254, 0b1000))
    ok("test_bit", test_bit(0b100000, 5), 1)
    ok("popcount", popcount(0xF0F0F0F0), 16)
    ok("is_power_of_two", (is_power_of_two(1024), is_power_of_two(1000)), (True, False))
    ok("swap32", swap32(0x12345678), 0x78563412)
    ok("store/load be32", load_be32(store_be32(0xDEADBEEF)), 0xDEADBEEF)
    ok("store_be32 bytes", list(store_be32(0xDEADBEEF)), [0xDE, 0xAD, 0xBE, 0xEF])

    print("\n12. RECURSION")
    ok("fib_memo", fib_memo(30), 832040)
    ok("fib_iterative", fib_iterative(30), 832040)
    ok("gcd", gcd(48, 18), 6)

    print("\n13. OUTPUT FORMATTING")
    print(pyramid(4))
    ok("pyramid no trailing space", all(not l.endswith(' ') for l in pyramid(5).split('\n')), True)
    ok("pyramid widths", [len(l) for l in pyramid(4).split('\n')], [4, 5, 6, 7])
    print(pyramid_letters(3))

    print("\nAll self-tests executed.")


if __name__ == '__main__':
    _main()
