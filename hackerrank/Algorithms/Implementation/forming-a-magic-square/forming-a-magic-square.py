import copy


def combinations(arr: range):
    # Base case
    if len(arr) == 0:
        return [[]]
    cs = []
    for c in combinations(arr[1:]):
        cs += [c, c+[arr[0]]]
    return cs


def mirror(matrix):
    matrix_copy = copy.deepcopy(matrix)
    new_matrix = []
    # new_matrix = [[0 for i in range(len(matrix))] for i in range(len(matrix[0]))]
    new_matrix.append(matrix_copy[2])
    new_matrix.append(matrix_copy[1])
    new_matrix.append(matrix_copy[0])

    return (new_matrix)


def flip_mirror(matrix):
    matrix_copy = copy.deepcopy(matrix)
    new_matrix = []
    # new_matrix = [[0 for i in range(len(matrix))] for i in range(len(matrix[0]))]
    new_matrix.append(matrix_copy[0][::-1])
    new_matrix.append(matrix_copy[1][::-1])
    new_matrix.append(matrix_copy[2][::-1])

    return (new_matrix)


def transpose(matrix) -> list[list[int]]:
    new_matrix = [[0 for i in range(len(matrix))]
                  for i in range(len(matrix[0]))]
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            new_matrix[j][i] = matrix[i][j]
    return new_matrix


def calculate_cost(possible_combinations, s):
    total_costs = []
    for possible_matrix in possible_combinations:
        cost = 0
        for i in range(len(possible_matrix)):
            for j in range(len(possible_matrix[0])):
                if possible_matrix[i][j] != s[i][j]:
                    cost += abs(s[i][j] - possible_matrix[i][j])
        total_costs.append(cost)
    return min(total_costs)


def formingMagicSquare(s: list[list[int]]):
    combs = []
    # Find all possible combinations of 3 numbers that add to 15
    #
    # The middle row and middle column number is 5
    # It appears 8 times
    for i in combinations(range(1, 10)):
        if sum(i) == 15 and len(i) == 3:
            combs.append(i)
    # The number that appears 4 times in the middle of the list is 5
    # Similarly, each of the corner pieces must form part of a row, a column and a diagonal.
    # So each corner cell must be a number that appears 3 times.
    # Those are the even numbers 2, 4, 6 and 8. That means the diagonals must be "2 5 8" and "4 5 6"
    #
    # That leaves the middle edge cells, each of which needs to appear in a row and a column.
    # These are the odd numbers 1, 3, 7 and 9. So the middle row and column must be "9 5 1" and "7 5 3".

    corner_dict = {}
    count = 0
    # Count the number of times a number appears 3 times in the 2d array.
    for i in range(1, 10):
        for j in range(len(combs)):
            for k in range(len(combs[0])):
                if combs[j][k] == i:
                    count += 1
        corner_dict[i] = count
        count = 0

    corner = list(filter(lambda key: corner_dict[key] == 3, corner_dict))

    new_matrix = [[corner[0], (15-corner[0]-corner[1]), corner[1]], [(15-corner[0]-corner[2]),
                                                                     5, (15-corner[1]-corner[3])], [corner[2], (15-corner[2]-corner[3]), corner[3]]]
    # print(new_matrix)

    possible_combinations = []

    possible_combinations.append(new_matrix)
    possible_combinations.append(mirror(new_matrix))
    possible_combinations.append(flip_mirror(new_matrix))
    possible_combinations.append(mirror(flip_mirror(new_matrix)))

    possible_combinations.append(transpose(new_matrix))
    possible_combinations.append(mirror(transpose(new_matrix)))
    possible_combinations.append(flip_mirror(transpose(new_matrix)))
    possible_combinations.append(mirror(flip_mirror(transpose(new_matrix))))

    return (calculate_cost(possible_combinations, s))


formingMagicSquare([[5, 3, 4], [1, 5, 8], [6, 4, 2]])
