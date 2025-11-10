n = [3, 5, 2, 67, 34, 11]


def merge_sort(arr: list[int]) -> list[int]:
    # Check the length of array is more than 1
    if len(arr) > 1:
        mid = len(arr) // 2  # Find the middle point
        left_half = arr[:mid]  # Divide the array elements into 2 halves
        right_half = arr[mid:]  # Divide the array elements into 2 halves

        merge_sort(left_half)  # Sort the first half
        merge_sort(right_half)

        # Merge the sorted halves

        # this is the base case, where it would be trivial or take a constant time to sort the array.
        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        # Copy any remaining elements from either half
        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

    return arr


print(merge_sort(n))
