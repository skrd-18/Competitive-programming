from functools import cache


def print_grid(grid) -> None:
    for row in grid:
        print("".join(row))
    print('---')


def numIslands(grid: list[list[str]]) -> int:
    if not grid:
        return 0
    print('Original Grid')
    print_grid(grid)
    count = 0
    for i in range(len(grid)):  # row = len(grid)
        for j in range(len(grid[0])):  # column = len(grid[0])
            if grid[i][j] == '1':
                dfs(grid, i, j)
                count += 1
    return count

# Iterate through each of the cell and if it is an island, do dfs to mark all adjacent islands, then increase the counter by 1.


def dfs(grid, i: int, j: int) -> None:
    # check the boundaries and ensure it is a '1'
    if i < 0 or j < 0 or i >= len(grid) or j >= len(grid[0]) or grid[i][j] != '1':
        return
    grid[i][j] = '#'
    print_grid(grid)
    dfs(grid, i+1, j)  # check on its neighbours
    dfs(grid, i-1, j)
    dfs(grid, i, j+1)
    dfs(grid, i, j-1)


grid = [
    ["1", "1", "1", "1", "0"],
    ["1", "1", "0", "1", "0"],
    ["1", "1", "0", "0", "0"],
    ["0", "0", "0", "0", "0"]
]

print(numIslands(grid))
