# https: // stackoverflow.com/questions/56515975/python-logic-of-listnode-in-leetcode

import types
from typing import List


class ListNode:
    def __init__(self, val: int=0, next=None) -> None:
        self.val = val
        self.next = next

    def __repr__(self) -> str:
        return "ListNode(val=" + str(self.val) + ", next={" + str(self.next) + "})"


def list_to_LL(arr) -> ListNode | None:
    if len(arr) < 1:
        return None

    if len(arr) == 1:
        return ListNode(arr[0])
    return ListNode(arr[0], next=list_to_LL(arr[1:]))


def reverseList(head: ListNode) -> ListNode:
    prev = None
    while head:
        next_node = head.next
        head.next = prev
        prev = head
        # pyrefly: ignore  # bad-assignment
        head = next_node

    # pyrefly: ignore  # bad-return
    return prev


def addTwoNumbers(l1: ListNode, l2: ListNode) -> ListNode:
    dummy = ListNode(0)
    cur = dummy

    carry = 0
    while l1 or l2 or carry:
        if l1:
            carry += l1.val
            # pyrefly: ignore  # bad-assignment
            l1 = l1.next
        if l2:
            carry += l2.val
            # pyrefly: ignore  # bad-assignment
            l2 = l2.next
        cur.next = ListNode(carry % 10)
        cur = cur.next
        carry //= 10
    # pyrefly: ignore  # bad-return
    return dummy.next


# test cases
# ListNode(val=1, next={ListNode(val=2, next={ListNode(val=3, next={ListNode(val=4, next={ListNode(val=5, next={None})})})})})
t1 = list_to_LL([1, 2, 3, 4, 5])
t2 = list_to_LL([1, 2])  # ListNode(val=1, next={ListNode(val=2, next={None})})
t3 = list_to_LL([])

# answers
# print(reverseList(t1))
# print(reverseList(t2))
# print(reverseList(t3))

one = list_to_LL([2, 4, 3])
two = list_to_LL([5, 6, 4])
# pyrefly: ignore  # bad-argument-type
print(addTwoNumbers(one, two))
