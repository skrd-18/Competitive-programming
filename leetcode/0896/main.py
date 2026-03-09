class Solution:
    def isMonotonic(self, nums: List[int]):
        # O(n) Solution
        # Check whether if its a increasing or decreasing gradient

        # Edge case: [1]
        if len(nums) < 2:
            return True
        else:
            count1 = 0
            count2 = 0
            for i in range(len(nums) - 1):
                sign = nums[i] - nums[i + 1]
                if sign > 0:
                    count1 += 1
                elif sign < 0:
                    count2 += 1
                elif sign == 0:  # Ignore
                    pass
                # I need either of the counts to be 0
                if (count1 and count2) != 0:
                    return False
            return True


sol = Solution()
nums = [1, 2, 2, 3]
nums1 = [3, 4, 2, 3]
print(sol.isMonotonic(nums))
