class Solution:
    def multiply(self, num1: str, num2: str) -> str:
        product = [0] * (len(num1) + len(num2))
        pos = len(product) - 1

        for n1 in reversed(num1):
            tempPos = pos
            for n2 in reversed(num2):
                product[tempPos] += int(n1) * int(n2)
                product[tempPos - 1] += product[tempPos] // 10
                product[tempPos] %= 10
                tempPos -= 1
            pos -= 1

        pt = 0
        while pt < len(product) - 1 and product[pt] == 0:
            pt += 1

        return "".join(map(str, product[pt:]))


"""
1. Prove to me why the array size in Phase 1 is correct using a quick math example.

2. Explain the difference between pos and tempPos in your own words (Phase 2).

3. Identify the bug in Phase 3 and tell me the exact Python operator you must use to fix it.

"""

sol = Solution()
num1 = "12"
num2 = "34"
print(sol.multiply(num1, num2))
