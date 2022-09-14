"""
Given a sequence of integers a, a triplet (a[i]),a[j],a[k]) is
beautiful if:
    i<j<k
    a[j]-a[i]=a[k]-a[j]=d
Given an increasing sequenc of integers and the value of d,
count the number of beautiful triplets in the sequence.
Example
    arr=[2,2,3,4,5]
    d=1
    There are three beautiful triplets, by index:
    [i,j,k]=[0,2,3],[1,2,3],[2,3,4]. To test the first triplet,
    arr[j]-arr[i]=3-2=1 and arr[k]-arr[j]=4-3=1.
Function Description
    Complete the beautifulTriplets function in the editor
    below.
    beautifulTriplets has the following parameters:
        int d: the value to match
        int arr[n]: the sequence, sorted ascending
Returns
    int: the number of beautiful triplets
Input Format
    The first line contains 2 space-separated integers, n and
    d, the length of the sequence and the beautiful
    difference.
    The second line contains n space-separated integers arr[i].
Constraints
    1<=n<=10^4
    1<=d<=20
    0<=arr[i]<=2X10^4
    arr[i]>arr[i-1]
Sample Input
    STDIN           Function
    -----           --------
    7 3             arr[] size n = 7, d = 3
    1 2 4 5 7 8 10  arr = [1, 2, 4, 5, 7, 8, 10]
Sample Output
    3
Explanation
    There are many possible triplets (arr[i],arr[j],arr[k]),
    but our only beautiful triplets are  (1,4,7),(4,7,10), and
    (2,5,8) by value, not index. Please see the equations
    below:
        7-4=4-1=3=d
        10-7=7-4=3=d
        8-5=5-2=3=d
    Recall that a beautiful triplet satisfies the following
    equivalence relation: arr[j]-arr[i]=arr[k]-arr[j]=d where
    i<j<k.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'beautifulTriplets' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER d
#  2. INTEGER_ARRAY arr
#

def beautifulTriplets(d, arr):
    # Write your code here
    idx = 0
    triplets = 0
    while idx < len(arr)-1:
        if arr[idx]+d in arr and arr[idx]+2*d in arr:
            triplets += 1
        idx += 1
    return triplets
    """
    #Still to slow O(2n^2)=O(n^2)
    ijs = []
    beauts = 0
    for i in range(0, len(arr)-2):
        for j in range(i+1,len(arr)-1):
            if(arr[j] - arr[i] == d):
                ijs.append((i,j))
    for j in ijs:
        for k in range(j[1], len(arr)):
            if(arr[k] - arr[j[1]] == d):
                beauts += 1
    return beauts
    """
    """
    #to slow O(n^3)
    beauts = 0
    for i in range(0, len(arr)-2):
        for j in range(i, len(arr)-1):
            for k in range(j, len(arr)):
                if(arr[j] - arr[i] == d and arr[k] - arr[j] == d):
                    beauts += 1
    return beauts
    """

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    d = int(first_multiple_input[1])

    arr = list(map(int, input().rstrip().split()))

    result = beautifulTriplets(d, arr)

    fptr.write(str(result) + '\n')

    fptr.close()
