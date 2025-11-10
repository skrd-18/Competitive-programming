def findNextCellToFill(grid, i, j) -> tuple[int, int]:
    for x in range(i, 9):
        for y in range(j, 9):
            if grid[x][y] == 0:
                return x, y
    for x in range(0, 9):
        for y in range(0, 9):
            if grid[x][y] == 0:
                return x, y
    return -1, -1  # no cell is found


def isValid(grid, i: int, j: int, e: int) -> bool:
    rowOk = all([e != grid[i][x] for x in range(9)])
    if rowOk:  # if True
        columnOk = all([e != grid[x][j] for x in range(9)])
        if columnOk:
            # finding the top left x,y co-ordinates of the section containing the i,j cell
            # floored quotient should be used here.
            secTopX, secTopY = 3 * (i//3), 3 * (j//3)
            for x in range(secTopX, secTopX+3):
                for y in range(secTopY, secTopY+3):
                    if grid[x][y] == e:
                        return False
            return True
    return False


def solveSudoku(grid, i: int=0, j: int=0) -> bool:  # starting positions i=0, j=0
    i, j = findNextCellToFill(grid, i, j)
    if i == -1:
        return True
    for e in range(1, 10):  # 1 - 9
        if isValid(grid, i, j, e):
            grid[i][j] = e
            if solveSudoku(grid, i, j):  # recursion starts here!
                return True
            # Undo the current cell for backtracking
            grid[i][j] = 0
    return False


if __name__ == "__main__":
    with open(r"zigzag_medium_sample_input.txt") as reader:
        crabs = [int(i) for i in reader.readline().split(",")]
    solveSudoku([])
