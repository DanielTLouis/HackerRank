"""
Manasa is out on a hike with friends. She finds a trail of stones
with numbers on them. She starts following the trail and notices
that any two consecutive stones' numbers differ by one of two
values. Legend has it that there is a treasure trove at the end of
the trail. If Manasa can guess the value of the last stone, the
treasure will be hers.
Example
    n=2
    a=2
    b3
    She finds 2 stones and their differences are a=2 or b=3. We know
    she starts with a 0 stone not included in her count. The
    permutations of differences for the two stones are
    [2,2],[2,3],[3,2], or [3,3]. Looking at each scenario, stones
    might have [2,4],[2,5],[3,5], or [3,6] on them. The last stone
    might have any of  4,5, or 6 on its face.
    Compute all possible numbers that might occur on the last stone
    given a starting stone with a 0 on it, a number of additional
    stones found, and the possible differences between consecutive
    stones. Order the list ascending.
Function Description
    Complete the stones function in the editor below.
    stones has the following parameter(s):
        int n: the number of non-zero stones
        int a: one possible integer difference
        int b: another possible integer difference
Returns
    int[]: all possible values of the last stone, sorted ascending
Input Format
    The first line contains an integer T, the number of test cases.
    Each test case contains 3 lines:
        - The first line contains n, the number of non-zero stones
        found.
        - The second line contains a, one possible difference
        - The third line contains b, the other possible difference.
Constraints
    1<=T<=10
    1<=n,a,b<=10^3
Sample Input
    STDIN   Function
    -----   --------
    2       T = 2 (test cases)
    3       n = 3 (test case 1)
    1       a = 1
    2       b = 2
    4       n = 4 (test case 2)
    10      a = 10
    100     b = 100
Sample Output
    2 3 4
    30 120 210 300
Explanation
    With differences 1 and 2, all possible series for the first test
    case are given below:
        1. 0,1,2
        2. 0,1,3
        3. 0,2,3
        4. 0,2,4
    Hence the answer 2 3 4.
    With differences 10 and 100, all possible series for the second
    test case are the following:
        1. 0, 10, 20, 30
        2. 0, 10, 20, 120
        3. 0, 10, 110, 120
        4. 0, 10, 110, 210
        5. 0, 100, 110, 120
        6. 0, 100, 110, 210
        7. 0, 100, 200, 210
        8. 0, 100, 200, 300
    Hence the answer 30 120 210 300.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'stones' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER n
#  2. INTEGER a
#  3. INTEGER b
#

def stones(n, a, b):
    # Write your code here
    """
    You don't need to get all the combinations to solve this problem, see the examples
    you will find a pattern there,Math.abs(a-b) is going to help you keep adding this to
    a you will get your result.
    Note* I am assuming a is always less than or equal to b
    """
    if abs(a-b) == 0: return [a*(n-1)]
    limits = sorted([a*(n-1), b*(n-1)])
    return list(range(limits[0], limits[1], abs(a-b))) + [limits[1]]

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    T = int(input().strip())

    for T_itr in range(T):
        n = int(input().strip())

        a = int(input().strip())

        b = int(input().strip())

        result = stones(n, a, b)

        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')

    fptr.close()
