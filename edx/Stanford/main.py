import random


def quicksort(A, lo=0, hi=None) -> None:
    if hi is None:
        hi = len(A) - 1
    while lo < hi:
        # choose random pivot and move to end
        p = random.randint(lo, hi)
        A[p], A[hi] = A[hi], A[p]

        # Lomuto partition
        pivot = A[hi]
        i = lo - 1
        for j in range(lo, hi):
            if A[j] < pivot:
                i += 1
                A[i], A[j] = A[j], A[i]
        i += 1
        A[i], A[hi] = A[hi], A[i]

        # Recurse on smaller side first (tail-call elimination)
        left_size = i - lo
        right_size = hi - i
        if left_size < right_size:
            quicksort(A, lo, i - 1)
            lo = i + 1  # loop to sort right side
        else:
            quicksort(A, i + 1, hi)
            hi = i - 1  # loop to sort left side
