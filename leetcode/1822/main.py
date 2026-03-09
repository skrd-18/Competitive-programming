class Solution:
    def arraySign(self, nums: List[int]) -> int:
        # Intuition: Watch out for 0 value, return 0 immediately
        # Count the number of -1, if count is even return 1 else -1
        count = 0
        for _ in nums:
            if _ == 0:
                return 0
            elif _ < 0:
                count += 1
        print(count)
        if count % 2 == 0:
            return 1
        else:
            return -1


sol = Solution()
nums = [-1, -2, -3, -4, 3, 2, 1]
print(sol.arraySign(nums))
