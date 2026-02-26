from collections import deque


class Solution:
    def calPoints(self, operations: List[str]) -> int:
        # Model as a stack
        myQueue = deque()
        for char in operations:
            if char.isnumeric():
                myQueue.append(int(char))
                continue
            if char.startswith("-"):
                myQueue.append(int(char[1:]) * -1)
                continue
            elif char == "+":
                x = myQueue.pop()
                y = myQueue.pop()
                myQueue.append(y)
                myQueue.append(x)
                myQueue.append(x + y)
                continue
            elif char == "C":
                myQueue.pop()
                continue
            elif char == "D":
                old = myQueue.pop()
                myQueue.append(old)
                myQueue.append(old * 2)
        print(sum(myQueue))


sol = Solution()
ops = ["5", "2", "C", "D", "+"]
ops_2 = ["5", "-2", "4", "C", "D", "9", "+", "+"]
ops_3 = ["1", "C"]
sol.calPoints(ops_3)
