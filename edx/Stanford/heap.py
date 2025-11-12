# Implement the heap data structure
from typing import Any

# Heap Property
# - At every node x, key[x] <= all keys of x's children


class MinHeap:
    def __init__(self, a) -> None:
        self.a: list[int] = []

    def _parent(self, i) -> int:
        if i == 0:
            return -1  # there exists no parent node for the root
        return (i - 1) // 2

    def _left(self, i) -> int:
        return (2 * i) + 1

    def _right(self, i) -> int:
        return (2 * i) + 2

    def _swap(self, i, j) -> None:
        self.a[j], self.a[i] = self.a[i], self.a[j]

    def sift_up(self, i):
        while (i > 0) and (self.a[i] < self.a[self._parent(i)]):
            parent_idx = (i - 1) // 2  # created a variable for clarity
            self._swap(i, parent_idx)
            i = self._parent(i)

    def push(self, x) -> None:
        self.a.append(x)  # Stick k at end of last level
        last_index = len(self.a) - 1
        print(f"last_index = {last_index}")
        self.sift_up(last_index)

    def __repr__(self):
        return f"{self.a}"

    def __len__(self):
        return len(self.a)


# h = MinHeap([])  # Passed in an empty array
# h.push(5)
# print(repr(h))
# print(len(h))
# h.push(3)
# # ---
a = [4, 4, 8, 9, 4, 12, 9, 11, 13]
h = MinHeap(a)
print(f"index is {h._left(1)}, and the value is {a[h._left(1)]}")
