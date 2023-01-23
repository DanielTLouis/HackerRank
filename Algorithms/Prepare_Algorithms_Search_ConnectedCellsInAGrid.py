"""
Consider a matrix where each cell contains either a 0 or a 1.
Any cell containing a 1 is called a filled cell. Two cells are
said to be connected if they are adjacent to each other
horizontally, vertically, or diagonally. In the following grid,
all cells marked X are connected to the cell marked Y.
    XXX
    XYX
    XXX
If one or more filled cells are also connected, they form a
region. Note that each cell in a region is connected to zero or
more cells in the region but is not necessarily directly
connected to all the other cells in the region.
Given an nXm matrix, find and print the number of cells in the
largest region in the matrix. Note that there may be more than
one region in the matrix.
For example, there are two regions in the following 3X3 matrix.
The larger region at the top left contains 3 cells. The smaller
one at the bottom right contains 1.
    110
    100
    001
Function Description
    Complete the connectedCell function in the editor below.
    connectedCell has the following parameter(s):
    - int matrix[n][m]: matrix[i] represents the ith row of the matrix
Returns
    - int: the area of the largest region
Input Format
    The first line contains an integer n, the number of rows in
    the matrix.
    The second line contains an integer m, the number of columns
    in the matrix.
    Each of the next n lines contains m space-separated integers
    matrix[i][j].
Constraints
    0<n,m<10
Sample Input
    STDIN       Function
    -----       --------
    4           n = 4
    4           m = 4
    1 1 0 0     grid = [[1, 1, 1, 0], [0, 1, 1, 0], [0, 0, 1, 0], [1, 0, 0, 0]]
    0 1 1 0
    0 0 1 0
    1 0 0 0
Sample Output
    5
Explanation
    The diagram below depicts two regions of the matrix.
    Connected regions are filled with X or Y. Zeros are replaced
    with dots for clarity.
        X X . .
        . X X .
        . . X .
        Y . . .
    The larger region has 5 cells, marked X.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'connectedCell' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY matrix as parameter.
#

def connectedCell(matrix):
    # Write your code here
    I,J  = len(matrix), len(matrix[0])
    dirs = (0,-1), (-1,-1), (-1,0), (-1,1)
    reg = [None]
    size = [0]
    def top(r):
        while reg[r] != r: r=reg[r]
        return r

    for i, line in enumerate(matrix):
        for j,v in enumerate(line):
            if v:
                see = set(top(matrix[i+di][j+dj])
                        for di,dj in dirs
                        if 0<=i+di<I and 0<=j+dj<J
                          and matrix[i+di][j+dj] > 0
                    )
                if see:
                   rno = max(see)
                   matrix[i][j] = rno
                   size[rno] += 1
                   for sno in see:
                       if sno != rno:
                           reg[sno] = rno
                           size[rno] += size[sno]
                else:
                    rno = len(reg)
                    reg.append(rno)
                    size.append(1)
                    matrix[i][j] = rno
    return max(size)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    m = int(input().strip())

    matrix = []

    for _ in range(n):
        matrix.append(list(map(int, input().rstrip().split())))

    result = connectedCell(matrix)

    fptr.write(str(result) + '\n')

    fptr.close()
