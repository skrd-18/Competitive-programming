#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'powerSum' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER X
#  2. INTEGER N

# 3 key steps for recursion
# 1. Must have at least ONE base case
# 2. Must have a recursive case
# 3. Make sure the recursive case can be eventually reduced to base case


def powerSum(x: int, n: int) -> None:
    dp = [1] + [0] * x
    for i in range(1, int(pow(x, 1 / n)) + 1):
        u = i ** n
        for j in range(x, u - 1, -1):
            dp[j] += dp[j - u]
    print(dp[-1])


powerSum(10, 2)
