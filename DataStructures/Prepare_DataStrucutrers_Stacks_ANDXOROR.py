"""
Given an array A[] of N distinct elements. Let M1 and M2 be the smallest and the next
smallest element in the interval [L,R] where 1<=L<R<=N. Si=(((M1^M2)⊕(M1VM2))^(M1⊕M2)).
where ^,V,⊕ are the bitwise operators AND, OR and XOR respectively.
Your task is to find the maximum possible value of Si.
Input Format
    First line contains integer N.
    Second line contains N integers, representing elements of the array A[].
Constraints
    1<N<=10^6
    1<=Ai<=10^9
Output Format
    Print the value of maximum possible value of .
Sample Input
    5
    9 6 3 5 2
Sample Output
    15
Explanation
    Consider the interval [1,2] the result will be maximum.
    (((9^6)⊕(9V9))^(9⊕6))=15
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'andXorOr' function below.
#
# The function is expected to return an INTEGER.
# The function accepts INTEGER_ARRAY a as parameter.
#

def andXorOr(a):
    # Write your code here
    #pA -the result of pairing a[-1] and popped
    #pStack-the result of pairing stack[-1] and popped
    stack=[a.pop()]
    popped=a.pop()
    maxRes=pStack=pA= -1
    while True: #
        #pairing and getting the result of the pairs:
        if stack:
            pStack=stack[-1]^popped
        if a:
            pA=a[-1]^popped
        maxRes=max(maxRes,pA,pStack) #getting the max result so far
        if stack and stack[-1]>popped:
            stack.pop() #
            continue
        elif not a:
            return maxRes
        elif not stack or stack[-1]<popped<a[-1]:
            stack.append(popped)
        elif stack[-1]<popped>a[-1]:
            pass
        popped=a.pop()

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a_count = int(input().strip())

    a = list(map(int, input().rstrip().split()))

    result = andXorOr(a)

    fptr.write(str(result) + '\n')

    fptr.close()
