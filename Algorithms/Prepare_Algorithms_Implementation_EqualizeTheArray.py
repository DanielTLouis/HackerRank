"""
Given an array of integers, determine the minimum number of elements 
to delete to leave only elements of equal value.
Example
    arr=[1,2,2,3]
    Delete the 2 elements 1 and 3 leaving arr=[2,2]. If both twos plus 
    either the 1 or the 3 are deleted, it takes 3 deletions to leave 
    either [3] or [1]. The minimum number of deletions is 2.
Function Description
    Complete the equalizeArray function in the editor below.
    equalizeArray has the following parameter(s):
        -int arr[n]: an array of integers
Returns
    int: the minimum number of deletions required
Input Format
    The first line contains an integer n, the number of elements in 
    arr.
    The next line contains n space-separated integers arr[i].
Constraints
    1<=n<=100
    1<=arr[i]<=100
Sample Input
    STDIN       Function
    -----       --------
    5           arr[] size n = 5
    3 3 2 1 3   arr = [3, 3, 2, 1, 3]
Sample Output
    2   
Explanation
    Delete arr[2]=2 and arr[3]=1 to leave arr'=[3,3,3]. This is 
    minimal. The only other options are to delete  elements to get an 
    array of either [1] or [2].
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'equalizeArray' function below.
#
# The function is expected to return an INTEGER.
# The function accepts INTEGER_ARRAY arr as parameter.
#

def equalizeArray(arr):
    # Write your code here
    bucket = [0]*101
    largest = 0
    total = 0
    for i in arr:
        bucket[i]+=1
    for i in bucket:
        total += i
        if(i > largest):
            largest = i
    return total - largest

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    arr = list(map(int, input().rstrip().split()))

    result = equalizeArray(arr)

    fptr.write(str(result) + '\n')

    fptr.close()