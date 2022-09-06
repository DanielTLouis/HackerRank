"""
A driver is driving on the freeway. The check engine light of his vehicle is on, and
the driver wants to get service immediately. Luckily, a service lane runs parallel to
the highway. It varies in width along its length.
    Paradise Highway
You will be given an array of widths at points along the road (indices), then a list
of the indices of entry and exit points. Considering each entry and exit point pair,
calculate the maximum size vehicle that can travel that segment of the service lane
safely.
Example
    n=4
    width=[2,3,2,1]
    cases=[[1,2],[2,4]]
    If the entry index, i=1 and the exit, j=2, there are two segment widths of 2 and 3
    respectively. The widest vehicle that can fit through both is 2. If i=2 and j=4,
    the widths are [3,2,1] which limits vehicle width to 1.
Function Description
    Complete the serviceLane function in the editor below.
    serviceLane has the following parameter(s):
        -int n: the size of the  array
        -int cases[t][2]: each element contains the starting and ending indices for a
        segment to consider, inclusive
Returns
    int[t]: the maximum width vehicle that can pass through each segment of the
    service lane described
Input Format
    The first line of input contains two integers, n and t, where n denotes the number
    of width measurements and , the number of test cases. The next line has
    space-separated integers which represent the array width.
    The next t lines contain two integers, i and j, where j is the start index and j
    is the end index of the segment to check.
Constraints
    2<=n<=100000
    1<=t<=1000
    0<=i<j<n
    2<-j-i+1<=min(n,1000)
    1<=width[k]<=3, where 0<=k<n
Sample Input
    STDIN               Function
    -----               --------
    8 5                 n = 8, t = 5
    2 3 1 2 3 2 3 3     width = [2, 3, 1, 2, 3, 2, 3, 3]
    0 3                 cases = [[0, 3], [4, 6], [6, 7], [3, 5], [0, 7]]
    4 6
    6 7
    3 5
    0 7
Sample Output
    1
    2
    3
    2
    1
Explanation
    Below is the representation of the lane:
            |HIGHWAY|Lane|    ->    Width

        0: |       |--|            2
        1: |       |---|           3
        2: |       |-|             1
        3: |       |--|            2
        4: |       |---|           3
        5: |       |--|            2
        6: |       |---|           3
        7: |       |---|           3
    1.(0,3): From index 0 through 3 we have widths 2,3,1, and 2. Nothing wider than 1
    can pass all segments.
    2.(4,6): From index 4 through 6 we have widht 3,2, and 3. Nothing wider than 2 can
    pass all segments.
    3.(6,7): 3,3->3 .
    4.(3,5):2,3,2->2
    5.(0,7): 2,3,1,2,3,2,3,3->1.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'serviceLane' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER n
#  2. 2D_INTEGER_ARRAY cases
#

def serviceLane(n, cases, width):#needed to add argument of width
    # Write your code here
    minLength = 100000
    ans = []
    for i in cases:
        minLength = 1000000
        for j in range(i[0],i[1]+1):#it is inclusive so need to add 1 so its inclusive
            if(minLength > width[j]):
                minLength = width[j]
        ans.append(minLength)
    return ans

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    t = int(first_multiple_input[1])

    width = list(map(int, input().rstrip().split()))

    cases = []

    for _ in range(t):
        cases.append(list(map(int, input().rstrip().split())))

    #need to also pass width or the question is not possible to know the widths
    ##between two points
    result = serviceLane(n, cases, width)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
