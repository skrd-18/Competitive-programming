import sys

def check_columns(image_array) -> bool:
    value_list = []
    value = 0
    for i in range(0, len(image_array)):
        value = 0
        for j in range(1, len(image_array[i])):
            value += int(image_array[i][j])
        value_list.append(value)
    s = set(value_list)
    if len(s) != 1:
        return True
    else:
        return False


def run_length_decoding(rows: int, image_array) -> None:
    error_flag = 0
    current_symbol = ""
    total_columns = 0
    check_total_columns = 0

    for i in range(0, len(image_array)):
        temp = ''
        for j in range(0, len(image_array[i])):
            if image_array[i][j] == "#":
                current_symbol = "#"
                continue
            if image_array[i][j] == ".":
                current_symbol = "."
                continue
            total_columns += int(image_array[i][j])

            # Wishful thinking
            if check_columns(image_array):
                error_flag = 1
            temp += current_symbol*int(image_array[i][j])
# print(current_symbol*int(image_array[i][j]))

            # Swap the current symbol
            if current_symbol == "#":
                current_symbol = "."
            else:
                current_symbol = "#"
        print(temp)
    if error_flag:
        print("Error decoding image")


def main() -> None:
    first = True  # we have not printed anything yet, so skip the first \n
    while True:
        i = int(input())
        if i == 0:
            # if at end break
            break
        if first:
            first = not first
        else:
            sys.stdout.write('\n')
            
        image_array = []
        rows = i
        for i in range(rows):
            image_array.append(input().split(' '))
        run_length_decoding(rows, image_array)

main()
