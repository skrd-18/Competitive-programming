class Solution:
    def plusOne(self, digits: List[int]) -> List[int]:
        num = "".join(map(str, digits))
        num = int(num) + 1
        return list(map(int, list(str(num))))


sol = Solution()
print(sol.plusOne(digits=[4, 9, 9, 9]))
