class Solution:
    def strStr(self, haystack: str, needle: str) -> int:
        loop_boundary = len(haystack) - len(needle) + 1  # to account for python range
        for c in range(loop_boundary):
            if haystack[c : c + len(needle)] == needle:
                return c

        return -1


haystack = "leetcode"
needle = "leeto"
sol = Solution()
print(sol.strStr(haystack=haystack, needle=needle))
