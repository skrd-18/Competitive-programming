# You must write an algorithm with O(log n) runtime complexity.
# mid = L + (R-L) // 2

class Solution:
    def search(self, nums: list[int], target: int) -> int:
        if nums == []:
            return -1
        mid = len(nums) // 2  # or mid = lo + (high - lo) // 2
        if target == nums[mid]:
            return mid
        elif target < nums[mid]:
            return self.search(nums[:mid], target)
        else:
            return self.search(nums[mid+1:], target)


def binary_search_2(key, seq):
    def helper(low: int, high: int):
        if low > high:
            return False
        mid = (low + high) // 2
        if key == seq[mid]:
            return True
        elif key < seq[mid]:
            return helper(low, mid-1)
        else:
            return helper(mid+1, high)
    return helper(0, len(seq) - 1)


seq = [-1, 0, 3]
key = 3

# s = Solution()
# print(s.search(seq, key))

# pyrefly: ignore  # unknown-name
print(classic_search(seq, key))
