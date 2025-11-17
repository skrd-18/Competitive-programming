# Implement the heap data structure
from typing import Any

# Heap Property
# - At every node x, key[x] <= all keys of x's children


class MinHeap:
    def __init__(self, a=None) -> None:
        self.a = [] if a is None else list(a)

    def _parent(self, i) -> int:
        if i == 0:
            return -1  # there exists no parent node for the root
        return (i - 1) // 2

    def _left(self, i) -> int:
        return (2 * i) + 1

    def _right(self, i) -> int:
        return (2 * i) + 2

    def _swap(self, i, j) -> None:
        self.a[i], self.a[j] = self.a[j], self.a[i]

    def sift_up(self, i) -> None:  # Bubble up until key of k's parent is <= k
        while (i > 0) and (self.a[i] < self.a[self._parent(i)]):
            parent_idx = (i - 1) // 2  # created a variable for clarity
            self._swap(i, parent_idx)  # Swap the values with the child and the parent
            i = self._parent(i)

    def _sift_down(self, i) -> None:
        n = len(self.a)
        while True:
            l, r = self._left(i), self._right(i)
            smallest = i
            if l < n and self.a[l] < self.a[smallest]:
                smallest = l
            if r < n and self.a[r] < self.a[smallest]:
                smallest = r
            if smallest == i:
                break

            self._swap(i, smallest)
            i = smallest

    def pop(self) -> int:  # Extract Min
        if not self.a:
            raise IndexError("pop from empty heap")
        min_val = self.a[0]  # delete root (return it)
        last = self.a.pop()  # remove last leaf
        if self.a:  # move last leaf to be the root node
            self.a[0] = last
        self._sift_down(0)  # bubble down until heap is restored
        return min_val

    def push(self, x) -> None:
        self.a.append(x)  # Stick k at end of last level
        last_index = len(self.a) - 1
        self.sift_up(last_index)

    def __repr__(self) -> str:
        return f"{self.a}"

    def __len__(self) -> int:
        return len(self.a)

    def peek(self) -> int:
        return self.a[0]


h = MinHeap()
for x in [5, 3, 8, 1, 4]:
    h.push(x)
print("heap after pushes:", h.a)  # min at index 0
print("pop seq:", [h.pop() for _ in range(len(h))])  # expect [1,3,4,5,8]

print("\n")

h = MinHeap()
for x in [7, 2, 6]:
    h.push(x)
print("heap is ", h.a)
print("peek:", h.peek())  # 2
print("pop:", h.pop())  # 2
h.push(1)
h.push(9)
print("rest:", [h.pop() for _ in range(len(h))])  # expect [1,6,7,9]

# a = [4, 4, 8, 9, 4, 12, 9, 11, 13]
# h = MinHeap(a)
# print(h.a)
# print(h._left(1))
# print(h.a[h._left(1)])  # -> 9
# print(h.a[h._right(1)])  # -> 9
