class Solution:
    def diagonalSum(self, mat: List[List[int]]) -> int:
        shape = len(mat)
        res = 0
        if shape == 1:
            return mat[0][0]
        elif shape == 2:
            return sum(sum(row) for row in mat)
        elif shape > 2:
            # Even
            if shape % 2 == 0:
                for row in range(len(mat)):
                    res += mat[row][row] + mat[row][len(mat) - 1 - row]
                return res
            # Odd
            elif shape % 2 == 1:
                for row in range(len(mat)):
                    if row == len(mat) - 1 - row:
                        res += mat[row][row]
                    else:
                        res += mat[row][row] + mat[row][len(mat) - 1 - row]
                return res


sol = Solution()
mat_1 = [[5]]
mat_2 = [[3, 7], [4, 9]]
mat = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
print(sol.diagonalSum(mat=mat))
