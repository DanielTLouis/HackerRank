"""
Given an array of strings of digits, try to find the occurrence of a given pattern of
digits. In the grid and pattern arrays, each string represents a row in the grid. For
example, consider the following grid:
    1234567890
    0987654321
    1111111111
    1111111111
    2222222222
The pattern array is:
    876543
    111111
    111111
The pattern begins at the second row and the third column of the grid and continues in
the following two rows. The pattern is said to be present in the grid. The return value
should be YES or NO, depending on whether the pattern is found. In this case, return YES.
Function Description
    Complete the gridSearch function in the editor below. It should return YES if the
    pattern exists in the grid, or NO otherwise.
    gridSearch has the following parameter(s):
        string G[R]: the grid to search
        string P[r]: the pattern to search for
Input Format
    The first line contains an integer t, the number of test cases.
    Each of the t test cases is represented as follows:
    The first line contains two space-separated integers R and C, the number of rows in
    the search grid G and the length of each row string.
    This is followed by R lines, each with a string of C digits that represent the grid
    G.
    The following line contains two space-separated integers, r and c, the number of
    rows in the pattern grid P and the length of each pattern row string.
    This is followed by r lines, each with a string of c digits that represent the
    pattern grid P.
Returns
    string: either YES or NO
Constraints
    1<=t<=5
    1<=R,r,C,c<=1000
    1<=r<=R
    1<=c<=C
Sample Input
    2
    10 10
    7283455864
    6731158619
    8988242643
    3830589324
    2229505813
    5633845374
    6473530293
    7053106601
    0834282956
    4607924137
    3 4
    9505
    3845
    3530
    15 15
    400453592126560
    114213133098692
    474386082879648
    522356951189169
    887109450487496
    252802633388782
    502771484966748
    075975207693780
    511799789562806
    404007454272504
    549043809916080
    962410809534811
    445893523733475
    768705303214174
    650629270887160
    2 2
    99
    99
Sample Output
    YES
    NO
Explanation
    The first test in the input file is:
        10 10
        7283455864
        6731158619
        8988242643
        3830589324
        2229505813
        5633845374
        6473530293
        7053106601
        0834282956
        4607924137
        3 4
        9505
        3845
        3530
    The pattern is present in the larger grid as marked in bold below.
        7283455864
        6731158619
        8988242643
        3830589324
        2229505813
        5633845374
        6473530293
        7053106601
        0834282956
        4607924137
    The second test in the input file is:
        15 15
        400453592126560
        114213133098692
        474386082879648
        522356951189169
        887109450487496
        252802633388782
        502771484966748
        075975207693780
        511799789562806
        404007454272504
        549043809916080
        962410809534811
        445893523733475
        768705303214174
        650629270887160
        2 2
        99
        99
    The search pattern is:
        99
        99
    This pattern is not found in the larger grid.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'gridSearch' function below.
#
# The function is expected to return a STRING.
# The function accepts following parameters:
#  1. STRING_ARRAY G
#  2. STRING_ARRAY P
#

def gridSearch(G, P):
    # Write your code here
    for i in range(len(G)-len(P)+1):
        for j in range(len(G[0])-len(P[0])+1):
            column = G[i].find(P[0], j)
            if (column == -1):
                break;
            matched_lines=1
            for k in range(1, len(P)):
                if G[i+k].find(P[k],j) == column:
                    matched_lines+=1
                else:
                    break
            if matched_lines == len(P):
                return "YES"
    return "NO"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        first_multiple_input = input().rstrip().split()

        R = int(first_multiple_input[0])

        C = int(first_multiple_input[1])

        G = []

        for _ in range(R):
            G_item = input()
            G.append(G_item)

        second_multiple_input = input().rstrip().split()

        r = int(second_multiple_input[0])

        c = int(second_multiple_input[1])

        P = []

        for _ in range(r):
            P_item = input()
            P.append(P_item)

        result = gridSearch(G, P)

        fptr.write(result + '\n')

    fptr.close()
