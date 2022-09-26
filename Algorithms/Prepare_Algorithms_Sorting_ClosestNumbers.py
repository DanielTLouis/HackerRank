"""
Sorting is useful as the first step in many different tasks. The most common 
task is to make finding things easier, but there are other uses as well. In this 
case, it will make it easier to determine which pair or pairs of elements have 
the smallest absolute difference between them.
Example
    arr=[5,2,3,4,2]
    Sorted, arr'=[1,2,3,4,5]. Several pairs have the minimum difference of 1: 
    [(1,2),(2,3),(3,4),(4,5)]. Return the array [1,2,2,3,3,4,4,5].
    Note
        As shown in the example, pairs may overlap.
        Given a list of unsorted integers, arr, find the pair of elements that 
        have the smallest absolute difference between them. If there are 
        multiple pairs, find them all.
Function Description
    Complete the closestNumbers function in the editor below.
    closestNumbers has the following parameter(s):
        int arr[n]: an array of integers
Returns
    - int[]: an array of integers as described  
Input Format
    The first line contains a single integer n, the length of arr.
    The second line contains n space-separated integers, arr[i].
Constraints
    2<=n<=200000
    -10^7<=arr[i]<=10^7
    All a[i] are unique in arr.
Output Format
Sample Input 0
    10
    -20 -3916237 -357920 -3620601 7374819 -7330761 30 6246457 -6461594 266854 
Sample Output 0
    -20 30
Explanation 0
    (30) - (-20) = 50, which is the smallest difference.
Sample Input 1
    12
    -20 -3916237 -357920 -3620601 7374819 -7330761 30 6246457
    -6461594 266854 -520 -470 
Sample Output 1
    -520 -470 -20 30
Explanation 1
    (-470) - (-520) = 30 - (-20) = 50, which is the smallest difference.
Sample Input 2
    4
    5 4 3 2
Sample Output 2
    2 3 3 4 4 5
Explanation 2
    Here, the minimum difference is 1. Valid pairs are (2, 3), (3, 4), and 
    (4, 5).
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'closestNumbers' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts INTEGER_ARRAY arr as parameter.
#

def closestNumbers(arr):
    # Write your code here
    arr.sort()
    shortest = 9999999999999999999
    ans = []
    for i in range(0,len(arr)-1):
        if(abs(arr[i]-arr[i+1])<shortest):
            shortest = abs(arr[i]-arr[i+1])
    for i in range(0, len(arr)-1):
        if(abs(arr[i]-arr[i+1])==shortest):
            ans.append(arr[i])
            ans.append(arr[i+1])
    print(ans)
    return(ans)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    arr = list(map(int, input().rstrip().split()))

    result = closestNumbers(arr)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()