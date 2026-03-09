class Solution:
    def myPow(self, x: float, n: int) -> float:
        # Base Case
        if n < 0:
            n = abs(n)
        if n == 0:
            return 1
        half_power = self.myPow(x, n // 2)
        if n % 2 == 0:
            return half_power * half_power
        elif n % 2 != 0:
            return half_power * half_power * x


sol = Solution()
x = 2.10000
y = 3
print(sol.myPow(x, y))
