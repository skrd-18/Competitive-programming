import math
import os
import random
import re
import sys

#
# Complete the 'timeConversion' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#


def timeConversion(s: str):
    # Write your code here
    if (s[8:]) == "PM":  # PM
        if int(s[0:2]) == 12:  # if it's 12 PM
            return s[0:8]
        else:
            return str(int(s[0:2]) + 12) + s[2:]
    else:  # AM
        if int(s[0:2]) == 12:  # if it's 12 AM
            return "00" + s[2:8]
        else:
            return s[0:8]


if __name__ == '__main__':
    s = input()

    result = timeConversion(s)
    print(result)
