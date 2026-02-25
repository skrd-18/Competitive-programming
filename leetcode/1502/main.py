class Solution:
    def canMakeArithmeticProgression(self, arr: list[int]) -> bool:
        # Quicksort
        arr.sort()
        diff = arr[1] - arr[0]
        for _ in range(0, len(arr)):
            print(_)
            if _ + 1 >= len(arr):
                if arr[-1] - arr[-2] != diff:
                    return False
            elif arr[_ + 1] - arr[_] != diff:
                return False
        return True


sol = Solution()
arr = [1, 4, 4, 7]
print(sol.canMakeArithmeticProgression(arr))
