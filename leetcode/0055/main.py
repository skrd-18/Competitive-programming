# Runtime O(n), O(1) space
def canJump(nums) -> bool:
    m = 0
    for i, n in enumerate(nums):
        print(f'i = {i}\n')
        if i > m:
            return False
        m = max(m, i+n)
        print(f'm = {max(m, i+n)}, m = {m}, i+n = {i+n} \n')
    return True

# print(canJump([3,2,1,0,4])

def canJumpBackwards(nums: list[int]) -> bool:
    last_position = len(nums)-1
        
    for i in range(len(nums)-2,-1,-1): # Iterate backwards from second to last item until the first item
        print(f'i = {i} \n')
        if (i + nums[i]) >= last_position: # If this index has jump count which can reach to or beyond the last position
            last_position = i # Since we just need to reach to this new index
        print(f'last_position = {last_position} \n')
    return last_position == 0

print(canJumpBackwards([2, 3, 1, 0, 4]))
