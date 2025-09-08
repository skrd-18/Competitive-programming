from typing import List


def minimumArea(grid: List[List[int]]) -> int:
    return 0


grid = [[0,1,0],[1,0,1]]
print(f"Minimum Area = {minimumArea(grid)}")


def FastPower(a,b) :
    if b == 1:
        return a
    c = a*a

    ans = FastPower(c,[b/2])

    if b % 2 == 1:
        return a*ans
    else:
        return ans
