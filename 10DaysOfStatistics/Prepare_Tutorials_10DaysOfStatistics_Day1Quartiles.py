"""
Objective
    In this challenge, we practice calculating quartiles. Check out the Tutorial tab
    for learning materials and an instructional video!
Task
    Given an array, , of  integers, calculate the respective first quartile (Q1),
    second quartile (Q2), and third quartile (Q3). It is guaranteed that Q1, Q2, and
    Q3 are integers.
Example
    arr=[9,5,7,1,3]
    The sorted array is [1,3,5,7,9] which has an odd number of elements. The lower
    half consists of [1,3], and its median is (1+3)/2=2. The middle element is 5 and
    represents the second quartile. The upper half is [5,7] and its median is
    (5+7)/2=8. Return [2,5,8].
    _______________________________________________________________________________
    arr=[1,3,5,7]
    The array is already sorted. The lower half is [1,3] with a median = (1+3)/2=2.
    The median of the entire array is (3+5)/2=4, and of the upper half is (5+7)/2=6.
    Return [2,4,6].
Function Description
    Complete the quartiles function in the editor below.
    quartiles has the following parameters:
        -int arr[n]: the values to segregate
Returns
    int[3]: the medians of the left half of ,  in total, and the right half of arr.
Input Format
    The first line contains an integer, , the number of elements in arr.
    The second line contains  space-separated integers, each an arr[i].
Constraints
    5<=n<=50
    0<arr[i]<=100, where arr[i] is the ith element of the array.
Sample Input
    STDIN                   Function
    -----                   --------
    9                       arr[] size n = 9
    3 7 8 5 12 14 21 13 18  arr = [3, 7, 8, 5, 12, 14, 21, 13,18]
Sample Output
    6
    12
    16
Explanation
    arr_sorted=[3,5,7,8,12,13,14,18,21]. There is an odd number of elements, and the
    middle element, the median, is 12.
    As there are an odd number of data points, we do not include the median (the
    central value in the ordered list) in either half:
        Lower half (L): 3, 5, 7, 8
        Upper half (U): 13, 14, 18, 21
    Now find the quartiles:
        -Q1 is the median(L). So, Q1=(5+7)/2=6.
        -Q2 is the median(X). So, Q2=12.
        -Q3 is the median(U). So, Q3=(14+18)/2=16.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'quartiles' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts INTEGER_ARRAY arr as parameter.
#

def median(arr):
    if(len(arr)%2==0):
        return (arr[len(arr)//2] + arr[len(arr)//2 -1]) // 2
    else:
        return arr[len(arr)//2]

def quartiles(arr):
    arr.sort()
    if(len(arr)%2==0):
        Q1 = arr[:len(arr)//2]
        Q2 = [arr[len(arr)//2-1],arr[len(arr)//2]]
        Q3 = arr[len(arr)//2:]
    else:
        Q1 = arr[:len(arr)//2]
        Q2 = arr[len(arr)//2]
        Q3 = arr[len(arr)//2+1:]
    print(arr)
    print(Q1, Q2, Q3)
    Q1 = median(Q1)
    if(len(arr)%2==0):
        Q2 = median(Q2)
    Q3 = median(Q3)

    return [Q1, Q2, Q3]

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    data = list(map(int, input().rstrip().split()))

    res = quartiles(data)

    fptr.write('\n'.join(map(str, res)))
    fptr.write('\n')

    fptr.close()
