class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        # To modify an array in-place, we use the Two Pointers (Fast/Slow) pattern.
        # We sacrifice the ease of just building a new array to achieve $O(1)$ space complexity,
        # which is mandatory for systems programming and large-scale data manipulation (like in C/C++ environments).
        slow = 0
        for _ in range(len(nums)):
            if nums[_] == 0:
                continue
            elif nums[_] != 0:
                nums[_], nums[slow] = nums[slow], nums[_]
                slow += 1  # Increment the slow pointer
        print(nums)


sol = Solution()
sol.moveZeroes(nums=[0, 1, 0, 3, 12])
