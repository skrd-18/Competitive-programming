import typing
import sys
import pdb

# It's good practice to increase the recursion limit for deep recursion problems.
sys.setrecursionlimit(20000)


def read_file(filename: str) -> typing.List[int]:
    _ = list()
    with open(filename, "r") as file:
        for line in file:
            content = int(line.strip())
            _.append(content)
    return _


# Global variable to store the total count
comparison_count = 0


def partitionMiddle(ar: typing.List[int], left: int, right: int) -> int:
    """
    Partitions the subarray ar[left...right] using the first element as the pivot.
    Returns the final position of the pivot.
    """

    # Compute the first element
    first = ar[left]
    # Compute the final element
    final = ar[right]
    # Compute the middle
    n = right - left + 1
    middle_index = left + (n - 1) // 2
    middle = ar[middle_index]

    # Find the median of the three
    median_index = sorted(
        [(left, first), (middle_index, middle), (right, final)], key=lambda x: x[1]
    )[1][0]

    ar[median_index], ar[left] = (
        ar[left],
        ar[median_index],
    )  # Swap the median with the first element

    pivot = ar[left]

    i = left + 1  # The boundary between elements < pivot and elements >= pivot

    for j in range(left + 1, right + 1):
        if ar[j] < pivot:
            ar[j], ar[i] = ar[i], ar[j]  # Swap
            i += 1

    ar[left], ar[i - 1] = ar[i - 1], ar[left]  # Place pivot in its final position
    return i - 1  # Return the pivot's new index


def partitionLeft(ar: typing.List[int], left: int, right: int) -> int:
    """
    Partitions the subarray ar[left...right] using the first element as the pivot.
    Returns the final position of the pivot.
    """
    pivot = ar[left]  # Choosing the first element as the pivot

    i = left + 1  # The boundary between elements < pivot and elements >= pivot

    for j in range(left + 1, right + 1):
        if ar[j] < pivot:
            ar[j], ar[i] = ar[i], ar[j]  # Swap
            i += 1

    ar[left], ar[i - 1] = ar[i - 1], ar[left]  # Place pivot in its final position
    return i - 1  # Return the pivot's new index


def partitionRight(ar: typing.List[int], left: int, right: int) -> int:
    """
    Partitions the subarray ar[left...right] using the first element as the pivot.
    Returns the final position of the pivot.
    """
    ar[left], ar[right] = ar[right], ar[left]  # Swap the first and last elements
    pivot = ar[left]  # Choosing the first element as the pivot

    i = left + 1  # The boundary between elements < pivot and elements >= pivot

    for j in range(left + 1, right + 1):
        if ar[j] < pivot:
            ar[j], ar[i] = ar[i], ar[j]  # Swap
            i += 1

    ar[left], ar[i - 1] = ar[i - 1], ar[left]  # Place pivot in its final position
    return i - 1  # Return the pivot's new index


def quickSortLeft(ar: typing.List[int], left: int, right: int):
    """
    Sorts the subarray ar[left...right] in-place using Quicksort.
    """
    global comparison_count

    # Base Case: If the array has 0 or 1 elements, it's already sorted.
    if left >= right:
        return

    # --- The Counting Step ---
    # The length of the current subarray is (right - left + 1).
    # The number of comparisons is length - 1, which is (right - left).
    comparison_count += (
        right - left
    )  #: Add the number of comparisons to comparison_count

    # Partition the array and get the pivot's final index; the pivot's final index is already sorted and in the correct position.
    pivot_index = partitionMiddle(ar, left, right)

    # --- Recursive Calls ---
    # Recursively sort the part of the array to the left of the pivot
    # Make the recursive call for the left partition
    quickSortLeft(ar, left, pivot_index - 1)

    # Recursively sort the part of the array to the right of the pivot
    ## YOUR CODE HERE ##: Make the recursive call for the right partition
    quickSortLeft(ar, pivot_index + 1, right)


if __name__ == "__main__":
    content = read_file(
        "/home/shiva/Projects/Competitive-programming/edx/Stanford/data/Programming-Assignment-2.txt"
    )
    # content = [3, 23, 12, 65, 1, 54]
    # content = [3, 8, 2, 5]
    quickSortLeft(content, 0, len(content) - 1)
    print(content)
    print(f"Comparison Count = {comparison_count}")
