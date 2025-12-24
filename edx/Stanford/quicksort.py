def parition(array):
    A = array[:]  # Perform a shallow copy
    pivot = A[0]
    i = 1
    for j in range(1, len(A)):  # j is from 1 to len(A) - 1
        if A[j] < pivot:
            # swap the jth element with ith element
            A[j], A[i] = A[i], A[j]
            i += 1  # Update the boundary of the parition
    # At the end, swap the pivot with the index i element
    A[i], A[0] = A[0], A[i]

    return A


print(parition(array=[3, 8, 2, 5, 1, 4, 7, 6]))
