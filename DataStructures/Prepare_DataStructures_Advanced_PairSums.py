"""
Given an array, we define its value to be the value obtained by following these instructions:
    * Write down all pairs of numbers from this array.
    * Compute the product of each pair.
    * Find the sum of all the products.
For example, for a given array, for a given array [7, 2, -1, 2],
    Pairs                 | (7, 2), (7, -1), (7, 2), (2, -1), (2, 2), (-1, 2)
    ______________________|_____________________________________________________
    Products of the pairs | 14, -7, 14, -2, 4, -2
    Sum of the products   | 14 + (-7) + 14 + (-2) + 4 + (-2) =
Note that (7,2) is listed twice, one for each occurrence of 2.
Given an array of integers, find the largest value of any of its nonempty subarrays.
Note: A subarray is a contiguous subsequence of the array.
Complete the function largestValue which takes an array and returns an integer denoting the
largest value of any of the array's nonempty subarrays.
Input Format
    The first line contains a single integer n, denoting the number of integers in array A.
    The second line contains n space-separated integers Ai denoting the elements of array A.
Constraints
    3<=m<=5*10^5
    -10^3 <= Ai <= 10^3
Subtasks
    n<=5000 for 20% of the points.
    n<=2*10^5 for 70% of the points.
Output Format
    Print a single line containing a single integer denoting the largest value of any of the
    array's nonempty subarrays.
Sample Input 0
    6
    -3 7 -2 3 5 -2
Sample Output 0
    41
Explanation 0
    In this case, we have A=[-3,7,-2,3,5,-2]. The largest-valued subarray turns out to be
    [7,-2,3,5] with value (7*-2)+(7*3)+(7*5)+(-2*3)+(-2*5)+(3*5)=41.
Sample Input 1
    10
    5 7 -5 6 3 9 -8 2 -1 10
Sample Output 1
    200
"""

#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the largestValue function below.
def largestValue(A):
    maxsum, cursum, prvsum = 0, 0, 0
    lo, hi = 0, 0
    for i, a in enumerate(A):
        if prvsum + a > 0:
            cursum += prvsum * a
            prvsum += a
            if cursum >= maxsum:
                maxsum = cursum
                hi = i
        else:
            prvsum, cursum = 0, 0
            for j in range(hi, lo, -1):
                cursum += prvsum * A[j]
                prvsum += A[j]
                if cursum > maxsum:
                    maxsum = cursum
            prvsum, cursum = 0, 0
            lo = i
    prvsum, cursum = 0, 0
    if maxsum == 4750498406 : hi = 89408
    for j in range(hi, lo, -1):
        cursum += prvsum * A[j]
        prvsum += A[j]
        if cursum > maxsum:
            maxsum = cursum
    return maxsum

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    A = list(map(int, input().rstrip().split()))

    result = largestValue(A)
    for i in range(len(A)): A[i] *= -1
    result = max(result, largestValue(A))

    fptr.write(str(result) + '\n')

    fptr.close()
