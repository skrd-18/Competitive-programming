import sys

numbers = []
i = 0

while i < 4:
    numbers.append(list(map(int, sys.stdin.readline().strip().split())))
    i += 1

new_numbers = []
direction = sys.stdin.readline().strip()


def move_right(numbers):
    # new_list = move_left(numbers)
    # if 0 in new_list:
    #     return new_list[::-1]
    # return new_list
    numbers.reverse()
    n = []
    new_numbers = []
    for number in numbers:
        if number != 0:
            n.append(number)
    i = 0
    while i < len(n):
        if i < len(n)-1 and n[i] == n[i+1]:
            new_numbers.append(n[i]*2)
            i += 2
        else:
            new_numbers.append(n[i])
            i += 1
    while len(new_numbers) != 4:
        new_numbers.append(0)
    new_numbers.reverse()
    return new_numbers


def move_left(numbers):
    n = []
    new_numbers = []

    # Filter out the non-zeros
    for number in numbers:
        if number != 0:
            n.append(number)
    i = 0
    while (i < len(n)):
        # (i < len(n)-1) used to prevent out of the bound error
        if (i < len(n)-1) and (n[i] == n[i+1]):
            new_numbers.append(n[i]*2)
            i += 2
        else:
            new_numbers.append(n[i])
            i += 1
    while len(new_numbers) != 4:
        new_numbers.append(0)
    return new_numbers


def transpose(numbers) -> list[list[int]]:
    arr = [[0 for i in range(4)] for j in range(4)]
    for row in range(len(numbers[0])):
        for col in range(len(numbers[0])):
            arr[col][row] = numbers[row][col]
    return arr


def shift(numbers):
    new_numbers = [[], [], [], []]
    i = len(numbers[0]) - 1
    k = 0
    while i != -1:
        j = 0
        while j < len(numbers):
            new_numbers[k].append(numbers[j][i])
            j += 1
        k += 1
        i -= 1
    return new_numbers


def shift_right(numbers):
    new_numbers = [[], [], [], []]
    k = 0
    j = 0
    while j < len(numbers):
        i = len(numbers[0]) - 1  # 3
        while i != -1:  # 0 < len(numbers) = 4
            new_numbers[k].append(numbers[i][j])
            i -= 1  # Move to next row
        k += 1  # Add in second row
        j += 1
    return new_numbers


if direction == "0":  # left
    for line in numbers:
        new_numbers.append(move_left(line))
elif direction == "2":  # right
    for line in numbers:
        new_numbers.append(move_right(line))
elif direction == "1":  # up
    numbers = shift(numbers)
    for line in numbers:
        new_numbers.append(move_left(line))
    # new_numbers = shift(new_numbers)
    # new_numbers = shift(new_numbers)
    # new_numbers = shift(new_numbers)
    new_numbers = shift_right(new_numbers)
else:  # 3 - down
    numbers = shift(numbers)
    for line in numbers:
        new_numbers.append(move_right(line))
    # new_numbers = shift(new_numbers)
    # new_numbers = shift(new_numbers)
    # new_numbers = shift(new_numbers)
    new_numbers = shift_right(new_numbers)

for line in new_numbers:
    line = list(map(str, line))
    print(" ".join(line))

'''
2 0 0 2
4 16 8 2
2 64 32 4
1024 1024 64 0
0

2 0 0 2
4 16 8 2
2 64 32 4
1024 1024 64 0
1

2 0 0 2
4 16 8 2
2 64 32 4
1024 1024 64 0
2

2 0 0 2
4 16 8 2
2 64 32 4
1024 1024 64 0
3
'''
