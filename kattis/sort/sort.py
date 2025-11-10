# from collections import defaultdict

def merge_sort(left_subarray_index: int, right_subarray_index: int, array) -> None:
    if left_subarray_index < right_subarray_index:
        middle = (left_subarray_index + right_subarray_index) // 2
        merge_sort(left_subarray_index, middle, array)
        merge_sort(middle + 1, right_subarray_index, array)
        merge(left_subarray_index, middle, right_subarray_index, array)


def merge(left, middle, reight, array):
  # Instead of thinking of elements as individual values, think of them as tuples of key-value pairs
  # i.e. (1, 3), (2, 2) -> (value, frequency) pairs
    sorted_array = []
    left_subarray_index = left
    right_subarray_index = middle + 1

    while left_subarray_index <= middle and right_subarray_index <= reight:
      # Just change the < to a >=
      # Does > work?
        if array[left_subarray_index][1] >= array[right_subarray_index][1]:
            sorted_array.append(array[left_subarray_index])
            left_subarray_index += 1
        else:
            sorted_array.append(array[right_subarray_index])
            right_subarray_index += 1

    while left_subarray_index <= middle:
        sorted_array.append(array[left_subarray_index])
        left_subarray_index += 1

    while right_subarray_index <= reight:
        sorted_array.append(array[right_subarray_index])
        right_subarray_index += 1

    for i in range(left, reight + 1):
        array[i] = sorted_array[i - left]


n, k = map(int, str(input()).split(' '))
# print(n, k, n * k)

arr = list(map(int, str(input()).split(' ')))
# print(arr)
frequency_dict = {}
# frequency_dict = defaultdict(lambda: 0)   # Just a trick to default any element not in dict to 0
for num in arr:
    if num not in frequency_dict:             # -> removes the need for this
        frequency_dict[num] = 0
    frequency_dict[num] += 1


arr = list(frequency_dict.items())
# print(arr)
merge_sort(0, len(arr) - 1, arr)
# print(arr)
final_arr = []
for (k, v) in arr:
    final_arr.extend([k] * v)
print(final_arr)
