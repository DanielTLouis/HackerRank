"""
There are a number of plants in a garden. Each of the plants has been treated with some
amount of pesticide. After each day, if any plant has more pesticide than the plant on
its left, being weaker than the left one, it dies.
You are given the initial values of the pesticide in each of the plants. Determine the
number of days after which no plant dies, i.e. the time after which there is no plant
with more pesticide content than the plant to its left.
Example
    p=[3,6,2,7,5] // pesticide levels
    Use a 1-indexed array. On day 1, plants 2 and 4 die leaving p'=[3,2,5]. On day 2,
    plant 3 in p' dies leaving p''=[3,2]. There is no plant with a higher concentration
    of pesticide than the one to its left, so plants stop dying after day 2.
Function Description
    Complete the function poisonousPlants in the editor below.
    poisonousPlants has the following parameter(s):
        * int p[n]: the pesticide levels in each plant
Returns
    - int: the number of days until plants no longer die from pesticide
Input Format
    The first line contains an integer n, the size of the array p.
    The next line contains n space-separated integers p[i].
Constraints
    1<=n<=10^5
    0<=p[i]<=10^9
Sample Input
    7
    6 5 8 4 7 10 9
Sample Output
    2
Explanation
    Initially all plants are alive.
    Plants = {(6,1), (5,2), (8,3), (4,4), (7,5), (10,6), (9,7)}
    Plants[k] = (i,j) => jth plant has pesticide amount = i.
    After the 1st day, 4 plants remain as plants 3, 5, and 6 die.
    Plants = {(6,1), (5,2), (4,4), (9,7)}
    After the 2nd day, 3 plants survive as plant 7 dies.
    Plants = {(6,1), (5,2), (4,4)}
    Plants stop dying after the 2nd day.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'poisonousPlants' function below.
#
# The function is expected to return an INTEGER.
# The function accepts INTEGER_ARRAY p as parameter.
#

def poisonousPlants(p):
    # Write your code here
    stack = []
    max_days = 0
    for i in range(len(p)-1, -1, -1):
        kills = 0
        while (len(stack) > 0) and stack[-1][0] > p[i]:
            kills = max(kills + 1, stack.pop()[1])
        max_days = max(max_days, kills)
        stack.append((p[i], kills))
    return max_days

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    p = list(map(int, input().rstrip().split()))

    result = poisonousPlants(p)

    fptr.write(str(result) + '\n')

    fptr.close()
