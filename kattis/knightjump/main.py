
# BFS with minimum number of steps

"""
1 2 3 4
2 3 4 5

ith row => either 1 2 3 4 or 2 3 4 5

jth col =>  1 2 3 4
            2 3 4 5
"""

# Create the matrix for the chess board NxN matrix


class BFS():
    def __init__(self, matrix, knight, dimension) -> None:
        self.matrix = matrix
        self.knight = knight
        self.dimension = dimension
        self.possible_neighbours = [
            (2, 1), (2, -1), (-2, 1), (-2, -1), (1, 2), (1, -2), (-1, 2), (-1, -2)]

    def find(self):
        queue = []
        queue.append((self.knight, 0))

        visited = {self.knight}

        while queue:
            coordinates, cost = queue.pop(0)

            if coordinates == (0, 0):
                return cost

            for n in self.possible_neighbours:
                new_row = coordinates[0] + n[0]
                new_column = coordinates[1] + n[1]

                if 0 <= new_row < self.dimension and 0 <= new_column < self.dimension and ((new_row, new_column) not in visited) and (self.matrix[new_row][new_column] != "#"):
                    queue.append(((new_row, new_column), cost + 1))
                    visited.add((new_row, new_column))
        return -1


def main() -> None:
    # dimension = int(input())
    dimension = 4
    matrix = []
# for _ in range(dimension):
# matrix.append(input())
    matrix = ['....', '....', '....', '...K']

    # Find the knight's x,y coordinates
    for x in range(len(matrix)):
        for y in range(len(matrix[0])):
            if matrix[x][y] == "K":
                knight = (x, y)

    # Initialise BFS object
    bfs = BFS(matrix, knight, dimension)
    print(bfs.find())


if __name__ == "__main__":
    main()
