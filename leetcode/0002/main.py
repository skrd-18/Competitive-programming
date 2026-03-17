# https: // stackoverflow.com/questions/56515975/python-logic-of-listnode-in-leetcode

import types
from typing import List, Optional


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __repr__(self) -> str:
        return "ListNode(val=" + str(self.val) + ", next={" + str(self.next) + "})"


class Solution:
    def addTwoNumbers(
        self, l1: Optional[ListNode], l2: Optional[ListNode]
    ) -> Optional[ListNode]:
        dummy = ListNode(0)
        cur = dummy

        carry = 0
        while l1 or l2 or carry:
            # Step 1: Safe Extraction
            v1 = l1.val if l1 else 0
            v2 = l2.val if l2 else 0
            # Step 2: Match
            total = v1 + v2 + carry
            digit = total % 10
            carry = total // 10
            # Build the new node
            cur.next = ListNode(digit)
            cur = cur.next
            l1 = l1.next if l1 else None
            l2 = l2.next if l2 else None
        return dummy.next


def build_linked_list(arr):
    dummy = ListNode(0)
    cur = dummy
    for i in arr:
        cur.next = ListNode(i)
        cur = cur.next
    return dummy.next


def print_linked_list(head):
    """Prints a Linked List as a standard Python list"""
    result = []
    while head:
        result.append(head.val)
        head = head.next
    print(result)


if __name__ == "__main__":
    # 1. Create the raw data
    arr1 = [1, 2, 4]
    arr2 = [1, 3, 4]

    # 2. Build the linked lists using our helper
    l1 = build_linked_list(arr1)
    l2 = build_linked_list(arr2)

    # 3. Run your algorithm
    sol = Solution()
    merged_head = sol.addTwoNumbers(l1, l2)

    # 4. Print the result
    print("Merged List Output:")
    print_linked_list(merged_head)
