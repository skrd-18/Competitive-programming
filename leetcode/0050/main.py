from functools import lru_cache


@lru_cache
class Solution:
    def myPow(self, x: float, n: int) -> float:
        # Base Case
        if n == 0:
            return 1
        # Negative case
        if n < 0:
            n = abs(n)
            half_power = self.myPow(x, n // 2)
            if n % 2 == 0:
                return 1 / (half_power * half_power)
            elif n % 2 != 0:
                return 1 / (half_power * half_power * x)
        half_power = self.myPow(x, n // 2)
        if n % 2 == 0:
            return half_power * half_power
        elif n % 2 != 0:
            return half_power * half_power * x


sol = Solution()
x = 343
y = 576421
print(sol.myPow(x, y))
