# Binary Search Template I

# def binarySearch(nums, target):
#     """
#     :type nums: List[int]
#     :type target: int
#     :rtype: int

#     Distinguishing Syntax:

#     Initial Condition: left = 0, right = length-1
#     Termination: left > right
#     Searching Left: right = mid-1
#     Searching Right: left = mid+1
#     """
#     if len(nums) == 0:
#         return -1

#     left, right = 0, len(nums) - 1
#     while left <= right:
#         mid = (left + right) // 2
#         if nums[mid] == target:
#             return mid
#         elif nums[mid] < target:
#             left = mid + 1
#         else:
#             right = mid - 1

#     # End Condition: left > right
#     return -1

# # First Exercise


# def mySqrt(self, x: int) -> int:
#     if x >= 2:
#         left = 1
#         right = x // 2
#         ans = 0

#         while (left <= right):
#             mid = (left + right) // 2

#             if (mid ** 2) == x:
#                 return mid
#             elif (mid ** 2) < x:
#                 ans = mid
#                 left = mid + 1
#             else:
#                 right = mid - 1
#         return ans  # return the previous result
#     else:
#         return x

# # Second Exercise


# def guess():
#     pass


# def guessNumber(self, n: int) -> int:
# low = 1
# high = n

# while low <= high:
#      mid = (low + high) // 2
#       temp = guess(mid)

#        if temp == 0:
#             return mid
#         elif temp < 0:
#             high = mid - 1
#         else:
#             low = mid + 1


'''Third Exercise
# Python Program to search an element in a sorted and pivoted array
# Searches an element key in a pivoted sorted array arrp[] of size n'''


def pivotedBinarySearch(arr: list[int], n: int, key: int):

    pivot = findPivot(arr, 0, n-1)  # arr, low, high

    # If we didn't find a pivot, then array is not rotated at all
    if pivot == -1:
        return binarySearch(arr, 0, n-1, key)

    # If we found a pivot, then first compare with pivot and then
    # search in two subarrays around pivot
    if arr[pivot] == key:
        return pivot
    if arr[0] <= key:
        # search on lhs
        return binarySearch(arr, 0, pivot-1, key)
    # search rhs
    return binarySearch(arr, pivot + 1, n-1, key)


# Function to get pivot. For array, 3, 4, 5, 6, 1, 2 it returns 3 (index of 6)
def findPivot(arr, low: int, high: int):

    # base cases
    if high < low:
        return -1
    if high == low:
        return low

    # low + (high - low)/2;
    mid = int((low + high)/2)

    # boundary conditions
    if mid < high and arr[mid] > arr[mid + 1]:
        return mid
    if mid > low and arr[mid] < arr[mid - 1]:
        return (mid-1)
    if arr[low] >= arr[mid]:
        return findPivot(arr, low, mid-1)
    return findPivot(arr, mid + 1, high)


def binarySearch(arr, low, high, key):
    # Standard Binary Search function
    # Understood
    if high < low:
        return -1

    # low + (high - low)/2;
    mid = int((low + high)/2)

    if key == arr[mid]:
        return mid
    if key > arr[mid]:
        return binarySearch(arr, (mid + 1), high,
                            key)
    return binarySearch(arr, low, (mid - 1), key)


# Driver program to check above functions */
# Let us search 3 in below array
arr1 = [5, 6, 7, 8, 9, 10, 1, 2, 3]
n = len(arr1)
key = 3
print("Index of the element is : ", pivotedBinarySearch(arr1, n, key))


# def classic_search(nums, target):
#     low = 0
#     high = len(nums) - 1

#     while (low <= high):
#         mid = (high + low) // 2
#         if (nums[mid] == target):
#             return mid
#         elif nums[mid] < target:
#             low = mid + 1
#         else:
#             high = mid - 1
#     return -1
