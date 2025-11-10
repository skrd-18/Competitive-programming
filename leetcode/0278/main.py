# The isBadVersion API is already defined for you.
# def isBadVersion(version: int) -> bool:

class Solution:
    def firstBadVersion(self, n: int) -> int:
        left = 1
        right = n

        while (left <= right):
            mid = (left + right) // 2
            # pyrefly: ignore  # bad-argument-count
            if (self.isBadVersion(mid)):
                # move to left side, look for source
                right = mid - 1
            else:
                # move to right side
                left = mid + 1
        return left

    def isBadVersion(mid: int) -> None:
        pass


# Comments

# prove by induction: http://www.cs.cornell.edu/courses/cs211/2006sp/Lectures/L06-Induction/binary_search.html

# How about the terminating condition? We could guess that leftleft and rightright eventually both meet and it must be the first bad version, but how could you tell for sure?

# The formal way is to prove by induction, which you can read up yourself if you are interested. Here is a helpful tip to quickly prove the correctness of your binary search algorithm during an interview. We just need to test an input of size 2. Check if it reduces the search space to a single element (which must be the answer) for both of the scenarios above. If not, your algorithm will never terminate.
