from pprint import pprint


class BFS():
    def __init__(self, matrix) -> None:
        self.matrix = matrix
        self.neighbours = []
        self.matrix_value = 0

    def find(self) -> int | tuple[int, int]:
        queue = []
        queue.append(((0, 0), 0))

        visited = [(0, 0)]

        while (queue):
            coordinates, cost = queue.pop(0)

            if coordinates == (len(self.matrix)-1, len(self.matrix[0])-1):
                return cost

            matrix_value = self.matrix[coordinates[0]][coordinates[1]]
            self.neighbours = [(coordinates[0] + matrix_value, coordinates[1]), (coordinates[0] - matrix_value, coordinates[1]), (
                coordinates[0], coordinates[1] + matrix_value), (coordinates[0], coordinates[1] - matrix_value)]

            # check if they are in boundary
            for cord in self.neighbours:
                if (0 <= cord[0] < len(self.matrix)) and (0 <= cord[1] < len(self.matrix[0])) and (cord not in visited):
                    queue.append((cord, cost + 1))
                    visited.append(cord)

        return -1


def create_zero_matrix(r: int, c: int):
    matrix = []
    row = []
    for i in range(r):
        row = []
        for j in range(c):
            row.append(0)
        matrix.append(row)
    return matrix


def main() -> None:
    ##    rows, space, columns = input()
    ##    rows = int(rows)
    ##    columns = int(columns)

    # Test Data
    rows = 2
    columns = 2


##    matrix = []
# for _ in range(rows):
# matrix.append(input())

    # Test Data
    matrix = ['11', '11']

    final_matrix = create_zero_matrix(rows, columns)

    for i in range(len(matrix)):  # step in through rows
        for j in range(len(matrix[0])):
            final_matrix[i][j] = int(matrix[i][j])
    bfs = BFS(final_matrix)
    print(bfs.find())


if __name__ == "__main__":
    main()
