class Solution:
    def findTheDifference(self, s: str, t: str) -> str:
        # Brute force approach
        # Find the string with the shorter length and the string with the longer length
        if len(t) > len(s):
            big_t = list(t)
            small_t = list(s)
        else:
            big_t = list(s)
            small_t = list(t)
        for _ in small_t:
            if _ in big_t:
                big_t.remove(_)
        return big_t[0]

    def pythonnic(self, s: str, t: str) -> str:
        # Sum of ASCII values of t minus Sum of ASCII values of s
        diff = sum(map(ord, t)) - sum(map(ord, s))
        return chr(diff)

    def better_solution(self, s: str, t: str) -> str:
        t_codes = [ord(c) for c in t]

        for i in range(len(s)):
            # Pass diff (t[i] - s[i]) to t[i+1]
            t_codes[i + 1] += t_codes[i] - ord(s[i])

        return chr(t_codes[-1])

    def XOR_solution(self, s: str, t: str) -> str:
        # 1. Initialize result to 0 (Neutral Element)
        # 0 ^ x = x
        result = 0

        # 2. Iterate through EVERY character in both strings
        # We can just concatenate them to treat them as one big soup
        for char in s + t:
            # 3. Apply XOR
            # The order doesn't matter. Pairs will kill each other.
            result ^= ord(char)

        # 4. Convert the surviving ASCII code back to a letter
        return chr(result)


s = "abc"
t = "dbac"

sol = Solution()
print(sol.XOR_solution(s, t))
