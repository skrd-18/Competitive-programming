class Solution:
    def tictactoe(self, moves: List[List[int]]) -> str:

        # Player A
        A = moves[::2]
        print(A)
        # Check for same row
        for _ in range(3):
            if ([_, 0] in A) and ([_, 1] in A) and ([_, 2] in A):
                return "A"
        # Check for same column
        for _ in range(3):
            if ([0, _] in A) and ([1, _] in A) and ([2, _] in A):
                return "A"
        # Check for diagonal
        if ([0, 0] in A and [1, 1] in A and [2, 2] in A) or (
            [0, 2] in A and [1, 1] in A and [2, 0] in A
        ):
            return "A"

        # Player B
        B = moves[1::2]
        # Check for same row
        for _ in range(3):
            if ([_, 0] in B) and ([_, 1] in B) and ([_, 2] in B):
                return "B"
        # Check for same column
        for _ in range(3):
            if ([0, _] in B) and ([1, _] in B) and ([2, _] in B):
                return "B"
        # Check for diagonal
        if ([0, 0] in B and [1, 1] in B and [2, 2] in B) or (
            [0, 2] in B and [1, 1] in B and [2, 0] in B
        ):
            return "B"

        if len(moves) == 9:
            return "Draw"
        if len(moves) < 10:
            return "Pending"


sol = Solution()
moves = [[0, 0], [2, 0], [1, 1], [2, 1], [2, 2]]
moves_1 = [[0, 0], [2, 0], [0, 1], [2, 1], [0, 2]]
moves_2 = [[0, 0], [1, 1], [2, 0], [1, 0], [1, 2], [2, 1], [0, 1], [0, 2], [2, 2]]
print(sol.tictactoe(moves_2))
