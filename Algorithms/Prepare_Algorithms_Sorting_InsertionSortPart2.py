"""
In Insertion Sort Part 1, you inserted one element into an array at its correct 
sorted position. Using the same approach repeatedly, can you sort an entire array?
Guideline: You already can place an element into a sorted array. How can you use 
that code to build up a sorted array, one element at a time? Note that in the 
first step, when you consider an array with just the first element, it is already 
sorted since there's nothing to compare it to.
In this challenge, print the array after each iteration of the insertion sort, 
i.e., whenever the next element has been inserted at its correct position. Since 
the array composed of just the first element is already sorted, begin printing 
after placing the second element.
Example.
    n=7
    arr=[3,4,7,5,6,2,1]
    Working from left to right, we get the following output:
        3 4 7 5 6 2 1
        3 4 7 5 6 2 1
        3 4 5 7 6 2 1
        3 4 5 6 7 2 1
        2 3 4 5 6 7 1
        1 2 3 4 5 6 7
Function Description
    Complete the insertionSort2 function in the editor below.
    insertionSort2 has the following parameter(s):
        int n: the length of 
        int arr[n]: an array of integers
Prints
    At each iteration, print the array as space-separated integers on its own line.
Input Format
    The first line contains an integer, n, the size of arr.
    The next line contains n space-separated integers arr[i].
Constraints
    1<=n<=1000
    -10000<=arr[i]<=10000, 0<=i<n
Output Format
    Print the entire array on a new line at every iteration.
Sample Input
    STDIN           Function
    -----           --------
    6               n = 6
    1 4 3 5 6 2     arr = [1, 4, 3, 5, 6, 2]
Sample Output
    1 4 3 5 6 2 
    1 3 4 5 6 2 
    1 3 4 5 6 2 
    1 3 4 5 6 2 
    1 2 3 4 5 6 
Explanation
    Skip testing 1 against itself at position 0. It is sorted.
    Test position 1 against position 0: 4>1, no more to check, no change.
    Print arr
    Test position 2 against positions 1 and 0:
        3<4, new position may be 1. Keep checking.
        3>1, so insert 3 at position 1 and move others to the right.
    Print arr
    Test position 3 against positions 2,1,0 (as necessary): no change.
    Print arr
    Test position 4 against positions 3,2,1,0: no change.
    Print arr
    Test position 5 against positions 4,3,2,1,0, insert 2 at position  and move others to the right.
    Print arr
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'insertionSort2' function below.
#
# The function accepts following parameters:
#  1. INTEGER n
#  2. INTEGER_ARRAY arr
#

def insertionSort2(n, arr):
    # Write your code here
    """
    i = len(arr) - 1
    for i in range(i, 0,-1):
        print(i)
        while(arr[i] < arr[i-1] ):
            print(*arr)
            temp = arr[i]
            arr[i] = arr[i-1]
            arr[i-1] = temp
            i -= 1
            if(i == 0):
                break
    print(*arr)#*arr will print in plain text
    """
    for i in range(1, n):
        position = 0
        for j in range(0, i+1):
            if arr[i] > arr[j]:
                position += 1
            else:
                break
        arr.insert(position, arr.pop(i))
        print(* arr)
            
if __name__ == '__main__':
    n = int(input().strip())

    arr = list(map(int, input().rstrip().split()))

    insertionSort2(n, arr)