class Solution:
    def twoSum(self, nums: list[int], target: int):
        d = {}
        for i in range(len(nums)):
            j = target - nums[i]
            if j in d:
                return [d[j], i]
            else:
                d[nums[i]] = i


s = Solution()
print(s.twoSum(
    [3, 2, 4], 6))
