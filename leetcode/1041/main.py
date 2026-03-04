class Solution:
    def isRobotBounded(self, instructions: str) -> bool:
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        x = 0
        y = 0
        direction_index = 0  # North

        for _ in instructions:
            if _ == "G":
                dx, dy = directions[direction_index]
                x += dx
                y += dy
            elif _ == "L":
                direction_index = (direction_index - 1) % 4
            elif _ == "R":
                direction_index = (direction_index + 1) % 4
        if (x, y) == (0, 0) or direction_index != 0:
            return True
        else:
            return False


sol = Solution()
instructions = "GGLLGG"
instructions_1 = "GG"
instructions_2 = "GL"
print(sol.isRobotBounded(instructions_1))
