from collections import Counter
import time
from bisect import bisect_left, bisect_right

"""
OPTIONAL CHALLENGE: If this problem is too easy for you,
try implementing your own hash table for it.
For example, you could compare performance under the chaining
and open addressing approaches to resolving collisions.
"""

path = "/Users/shiva/Documents/Competitive-programming/edx/Stanford/data/algo1-programming_prob-2sum.txt"


def solve_2sum(filename):
    start_time = time.time()

    numbers = []
    try:
        with open(filename, "r") as f:
            for line in f:
                numbers.append(int(line.strip()))
    except FileNotFoundError:
        return 0

    # PHASE 2: Data Structure
    # This creates { value : count }, e.g., {5: 2, 8: 1}
    lookup = Counter(numbers)

    # Sort the unique keys to make optimization possible
    unique_nums = sorted(lookup.keys())

    valid_targets = 0  # Store targets we found (to avoid double counting)

    for t in range(-10000, 10001):
        # Check if any pair sums to t
        for x in unique_nums:
            y = t - x
            if y in lookup:
                if (x != y) or lookup[x] > 1:
                    # Critical Optimization;
                    # We found a pair for 't'. We don't care if there are others.
                    # Stop searching for 't' and move to the next target.
                    valid_targets += 1
                    break
        if t % 1000 == 0:
            print(f"Checked target {t}...")

    end_time = time.time()
    print(f"Finished in {end_time - start_time:.2f} seconds.")
    return valid_targets


def solve_2sum_sorting(filename):
    print(f"Loading data from {filename}...")
    start_time = time.time()

    # 1. Load and Sort
    #
    # We still need to handle duplicates for the distinctness case (x + x = t)
    # Strategy: Read all numbers, keep track of duplicates, but sort a UNIQUE list for searching.
    raw_numbers = []
    try:
        with open(filename, "r") as f:
            for line in f:
                raw_numbers.append(int(line.strip()))
    except FileNotFoundError:
        return 0

    # Create a set or dictionary for fast lookup of duplicates later.
    lookup = Counter(raw_numbers)
    # Or just use the sorted list?
    # NOTE: : A sorted list of UNIQUE numbers is best for the binary search.
    sorted_nums = sorted(list(set(raw_numbers)))

    print(f"Sorted {len(sorted_nums)} unique integers.")

    found_targets = set()

    # 2. The Main Loop
    # Iterate through every number 'x' in our sorted list
    for i, x in enumerate(sorted_nums):
        # Calculate the mathematical boundaries for y
        lower_bound_y = -10000 - x
        upper_bound_y = 10000 - x

        # 3. Binary Search
        # Find the slice of the array that contains numbers in [lower_bound_y, upper_bound_y]

        # 'left_index' is where 'lower_bound_y' would be
        left_index = bisect_left(sorted_nums, lower_bound_y)

        # 'right_index' is where 'upper_bound_y' would be
        right_index = bisect_right(sorted_nums, upper_bound_y)

        # 4. Iterate ONLY the valid candidates
        # sorted_nums[left_index : right_index] contains all valid y's
        for j in range(left_index, right_index):
            y = sorted_nums[j]

            # Distinctness Check:
            # If x and y are different (i != j), it's a valid pair.
            # If x and y are the same (i == j), we need to check if the original file had duplicates.

            # Implement the check and add (x + y) to found_targets
            if x != y:
                found_targets.add(x + y)
            if x == y:
                if lookup[x] > 1:
                    found_targets.add(x + x)

    print(f"Finished in {time.time() - start_time:.2f} seconds.")
    return len(found_targets)


# Run the function
result = solve_2sum_sorting(path)
print(f"Number of valid targets: {result}")
