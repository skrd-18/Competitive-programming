# Recursion
# Base Case: n < 2, return lst
# Otherwise:
# Divide list into 2, Sort each of them, Merge!

def merge(left, right):
    # Compare first element
    # Take the smaller of the 2
    # Repeat until no more elements
    results = []
    while left and right:
        if left[0] < right[0]:
            results.append(left.pop(0))
        else:
            results.append(right.pop(0))
    results.extend(right)
    results.extend(left)
    return results


def merge_sort(lst: list[int]):
    if (len(lst) < 2):
        return lst
    mid = len(lst) // 2

    left = merge_sort(lst[:mid])  # sort left
    right = merge_sort(lst[mid:])  # sort right

    return merge(left, right)


print(merge_sort([2, 1, 99]))
