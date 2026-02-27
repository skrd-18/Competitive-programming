class Solution:
    def judgeCircle(self, moves: str) -> bool:
        v = 0
        h = 0
        for m in moves:
            if m == "U":
                v += 1
            elif m == "D":
                v -= 1
            elif m == "L":
                h -= 1
            elif m == "R":
                h += 1
        if (v == 0) and h == 0:
            return True
        else:
            return False


sol = Solution()
moves = "LL"
print(sol.judgeCircle(moves=moves))
