class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        row = len(matrix)
        column = len(matrix[0])
        result = []

        top_wall = 0  # the first row
        bottom_wall = row - 1
        left_wall = 0  # the first column
        right_wall = column - 1

        while (left_wall <= right_wall) and (top_wall <= bottom_wall):
            for i in range(left_wall, right_wall + 1):
                result.append(matrix[top_wall][i])
            top_wall += 1

            for i in range(top_wall, bottom_wall + 1):
                result.append(matrix[i][right_wall])
            right_wall -= 1

            if top_wall <= bottom_wall:
                for i in range(right_wall, left_wall - 1, -1):
                    result.append(matrix[bottom_wall][i])
                bottom_wall -= 1

            if left_wall <= right_wall:
                for i in range(bottom_wall, top_wall - 1, -1):
                    result.append(matrix[i][left_wall])
                left_wall += 1

        return result


sol = Solution()
matrix = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]
matrix = [[1, 2, 3]]
print(sol.spiralOrder(matrix=matrix))
