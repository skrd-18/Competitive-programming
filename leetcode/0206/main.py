from typing import Optional


# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        prev = None
        curr = head

        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
        return prev

    def recursiveReverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # recrusive: Time: O(n) and Space is O(n)
        if not head:
            return None
        newHead = head
        if head.next:
            newHead = self.recursiveReverseList(head.next)
            head.next.next = head  # The "head.next.next = head" is the most confusing part --- It is literally doing the reversing (from A -> B to B -> A) (B is equal to A.next, so A.next.next is equal to B.next = A). But once you understand it, everything makes much more sense.
        head.next = None
        return newHead

    def recursiveReverseList2(self, head: Optional[ListNode]) -> Optional[ListNode]:
        # recrusive: Time: O(n) and Space is O(n)
        def recurse(cur, prev):
            if cur is None:
                return prev
            else:
                next = cur.next
                cur.next = prev
                return recurse(next, cur)

        return recurse(head, None)


def build_linked_list(arr):
    """Converts a standard Python list into a Linked List"""
    dummy = ListNode()
    cur = dummy
    for val in arr:
        cur.next = ListNode(val)
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
    arr1 = [1, 2, 4]

    l1 = build_linked_list(arr1)

    sol = Solution()
    merged_head = sol.recursiveReverseList(l1)

    # 4. Print the result
    print("Output:")
    print_linked_list(merged_head)
