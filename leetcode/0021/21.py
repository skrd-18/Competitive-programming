from typing import Optional


class ListNode:
    def __init__(self, val: int=0, next=None) -> None:
        self.val = val
        self.next = next


class Solution:
    def mergeTwoLists(
        self, list1: Optional[ListNode], list2: Optional[ListNode]
    ) -> Optional[ListNode]:
        pass


s = Solution()


print(s.mergeTwoLists(None, None))  # Expected output: None
