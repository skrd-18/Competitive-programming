from typing import Optional


class ListNode:
    def __init__(self, val: int = 0, next=None) -> None:
        self.val = val
        self.next = next


class Solution:
    def mergeTwoLists(
        self, list1: Optional[ListNode], list2: Optional[ListNode]
    ) -> Optional[ListNode]:
        cur = dummy_node = ListNode()
        while list1 and list2:  # loop as long as both lists are non empty
            if list1.val < list2.val:
                cur.next = list1  # Plug cur's wire to list1
                cur = list1  # Move cur forward to that new house
                list1 = list1.next  # Move list1 forwward to its next house so it is ready for the next round of the loop
            else:
                cur.next = list2
                cur = list2
                list2 = list2.next

        if list1 or list2:
            cur.next = list1 if list1 else list2
        return dummy_node.next


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
    # 1. Create the raw data
    arr1 = [1, 2, 4]
    arr2 = [1, 3, 4]

    # 2. Build the linked lists using our helper
    l1 = build_linked_list(arr1)
    l2 = build_linked_list(arr2)

    # 3. Run your algorithm
    sol = Solution()
    merged_head = sol.mergeTwoLists(l1, l2)

    # 4. Print the result
    print("Merged List Output:")
    print_linked_list(merged_head)
