"""
Johnny is playing with a large binary number, B. The number is so large that it
needs to be compressed into an array of integers, A, where the values in even
indices (0,2,4,...) represent some number of consecutive 1 bits and the values in
odd indices (1,3,5,...) represent some number of consecutive 0 bits in alternating
substrings of B.
For example, suppose we have array A={4,1,3,2,4}.A0  represents "1111", A1
represents "0", A2 represents "111", A3 represents "00:, and A4 represents "1111".
The number of consecutive binary characters in the ith substring of B corresponds
to integer Ai, as shown in this diagram:
    whats.png
When we assemble the sequential alternating sequences of 1's and 0's, we get
B="11110111001111".
We define setCount(B) to be the number of 1's in a binary number, B. Johnny wants
to find a binary number, D, that is the smallest binary number >B where setCount(B)
 = setCount(D). He then wants to compress D into an array of integers, C (in the
same way that integer array A contains the compressed form of binary string B).
Johnny isn't sure how to solve the problem. Given array A, find integer array C
and print its length on a new line. Then print the elements of array C as a single
line of space-separated integers.
Input Format
    The first line contains a single positive integer, T, denoting the number of
    test cases. Each of the 2T subsequent lines describes a test case over 2 lines:
        1.The first line contains a single positive integer, n, denoting the
        length of array A.
        2.The second line contains n positive space-separated integers describing
        the respective elements in integer array A (i.e., A0,A1,...,A(n-1)).
Constraints
    1<=T<=100
    1<=n<=10
Subtasks
    For a 50% score, 1<=Ai<=10^4.
    For a 100% score, 1<=Ai<=10^18.
Output Format
    For each test case, print the following 2 lines:
        1.Print the length of integer array C (the array representing the
        compressed form of binary integer D) on a new line.
        2.Print each element of C as a single line of space-separated integers.
    It is guaranteed that a solution exists.
Sample Input 0
    1
    5
    4 1 3 2 4
Sample Output 0
    7
    4 1 3 1 1 1 3
Explanation 0
    A={4,1,3,2,4}, which expands to B=11110111001111. We then find setCount(B)=11.
    The smallest binary number >B which also has eleven 1's is D=11110111010111.
    This can be reduced to the integer array C={4,1,3,1,1,1,3}. This is
    demonstrated by the following figure:
        whats-2.png
    Having found C, we print its length (7) as our first line of output, followed
    by the space-separated elements in C as our second line of output.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'whatsNext' function below.
#
# The function accepts INTEGER_ARRAY arr as parameter.
#
"""
11111 -> 101111
5 -> 1 1 4

1 -> 10
1 -> 1 1
1110000 -> 10000011
3 4 -> 1 5 2

11000 -> 100001
2 3 -> 1 4 1

1000 -> 10000
1 3 -> 1 4
__________
1110011 -> 1110101
3 2 2 -> 3 1 1 1 1

1110111 -> 1111011
3 1 3 -> 4 1 2

11100011 -> 11100101
3 3 2 -> 3 2 1 1 1

1001 -> 1010
1 2 1 -> 1 1 1 1
____

10100 -> 11000
1 1 1 2 -> 2 3

1110010100 -> 1110011000
3 2 1 1 1 2 -> 3 2 2 3

110011100 -> 110100011
2 2 3 2 -> 2 1 1 3 2

11011100 -> 11100011
2 1 3 2 -> 3 3 2

10010 -> 10100
1 2 1 1 -> 1 1 1 2

11100100 -> 11101000
3 2 1 2 -> 3 1 1 3

1111001000111000 -> 1111001001000011
4 2 1 3 3 3 -> 4 2 1 2 1 4 2
"""
def whatsNext(arr):
    l=len(arr)
    if l==1:
        num_of_one=arr[-1]
        arr=[1,1,num_of_one-1] if num_of_one >1 else [1,1]
    elif l==2:
        num_of_one=arr[-2]
        arr=[1,arr[-1]+1,num_of_one-1] if num_of_one>1 else [1,arr[-1]+1]
    elif l%2==1:
        num_of_zero=arr[-2]
        num_of_one=arr[-1]
        n=2
        if num_of_zero>1:
            last=[num_of_zero-1,1,1,num_of_one-1]
        else:
            last=[arr[-3]+1,1,num_of_one-1]
            n=3
        arr=arr[:l-n]+last

        if num_of_one==1:
            del arr[-1]
    else:
        num_of_zero=arr[-3]
        num_of_one=arr[-2]
        n=3
        if num_of_one==1:
            if num_of_zero>1:
                last=[num_of_zero-1,1,arr[-1]+1]
            else:
                n=4
                last=[arr[-4]+1,arr[-1]+1]
        else:
            if num_of_zero>1:
                last=[num_of_zero-1,1,arr[-1]+1,num_of_one-1]
            else:
                n=4
                last=[arr[-4]+1,arr[-1]+1,num_of_one-1]

        arr=arr[:l-n]+last

    #return [len(arr),arr]
    print(len(arr))
    for i in range(0, len(arr)):
        print(arr[i], end=" ")
    print()

if __name__ == '__main__':
    t = int(input().strip())

    for t_itr in range(t):
        arr_count = int(input().strip())

        arr = list(map(int, input().rstrip().split()))

        whatsNext(arr)
