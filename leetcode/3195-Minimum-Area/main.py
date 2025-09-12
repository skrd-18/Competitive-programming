from typing import List


def minimumArea(grid: List[List[int]]) -> int:
    # Step 1: Shrinking the grid: Check if the top row, bottom row, left column and the right column are full of zeroes, if so remove them
    while 1 not in grid[0]:
        del grid[0]
    while 1 not in grid[-1]:
        del grid[-1]

    # Transpose the grid, rows turn into columns and columns turn into rows
    # create new transposed grid
    grid_transposed = [
        [grid[j][i] for j in range(len(grid))] for i in range(len(grid[0]))
    ]

    while 1 not in grid_transposed[0]:
        del grid_transposed[0]
    while 1 not in grid_transposed[-1]:
        del grid_transposed[-1]

    print(f"grid_transposed = {grid_transposed}")

    return len(grid_transposed) * len(grid_transposed[0])


# grid = [[0, 0, 0, 0], [0, 0, 1, 0], [0, 1, 0, 1], [1, 0, 0, 0], [0, 0, 0, 0]]
grid = [[1, 0], [0, 0]]
print(f"Minimum Area = {minimumArea(grid)}")


# Editorial solution for revision and understanding
# class Solution:
#     def minimumArea(self, grid: List[List[int]]) -> int:
#         n, m = len(grid), len(grid[0])
#         min_i, max_i = n, 0
#         min_j, max_j = m, 0

#         for i in range(n):
#             for j in range(m):
#                 if grid[i][j] == 1:
#                     min_i = min(min_i, i) # Only captures the topmost row
#                     max_i = max(max_i, i) # Calture the bottommost row
#                     min_j = min(min_j, j)
#                     max_j = max(max_j, j)

#         return (max_i - min_i + 1) * (max_j - min_j + 1)
