class Solution:
    def repeatedSubstringPattern(self, s: str) -> bool:
        """
        The Rotation Test
        A pattern cannot be longer than half the string if it repeats at least twice
        """
        doubled = s + s
        trimmed = doubled[1:-1]
        return True if s in trimmed else False

    def naive_solution(self, s: str) -> bool:
        """
        You are building and comparing strings of length N inside a loop that runs N/2 times.
        Total runtime complexity is O(N^2)
        """
        N = len(s)
        # round down
        for l in range(1, N // 2 + 1):
            pattern = s[:l]  # O(l) time
            candidate = pattern * (N // l)  # O(N) time
            if candidate == s:
                return True
        return False


sol = Solution()


# print(sol.repeatedSubstringPattern("abcabcabc"))

print(sol.naive_solution("abcabcabc"))
