"""
Madison is a little girl who is fond of toys. Her friend Mason works in
a toy manufacturing factory . Mason has a 2D board A of size H X W with
H rows and W columns. The board is divided into cells of size 1 X 1
with each cell indicated by its coordinate (i,j). The cell (i,j) has an
integer A[i][j] written on it. To create the toy Mason stacks  A[i][j]
number of cubes of size 1X1X1 on the cell (i,j).
Given the description of the board showing the values of A[j][i] and
that the price of the toy is equal to the 3d surface area find the
price of the toy.
Input Format
    The first line contains two space-separated integers  and  the height and the width of the board respectively.
    The next   lines contains  space separated integers. The  integer in  line denotes .
Constraints
    1<=H,W<=100
    1<=A[i][j]<=100
Output Format
    Print the required answer, i.e the price of the toy, in one line.
Sample Input 0
    1 1
    1
Sample Output 0
    6
Explanation 0
        image
    The surface area of 1 X 1 X 1 cube is 6.
Sample Input 1
    3 3
    1 3 4
    2 2 3
    1 2 4
Sample Output 1
    60
Explanation 1
        image
    The object is rotated so the front row matches column 1 of the
    input, heights 1, 2, and 1.
        -The front face is 1 + 2 + 1 = 4 units in area.
        -The top is 3 units.
        -The sides are 4 units.
        -None of the rear faces are exposed.
        -The underside is 3 units.
    The front row contributes 4 + 3 + 4 + 3 = 14 units to the surface
    area.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'surfaceArea' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY A as parameter.
#

def surfaceArea(A):
    # Write your code here
    AT = list(zip(*A))
    n = 0
    for i in range(H):
        for j in range(1, W):
            n += abs(A[i][j] - A[i][j-1])
    for i in range(W):
        for j in range(1, H):
            n += abs(AT[i][j] - AT[i][j-1])
    return 2 * H * W + sum(A[0]) + sum(A[H-1]) + sum(AT[0]) + sum(AT[W-1]) + n

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    H = int(first_multiple_input[0])

    W = int(first_multiple_input[1])

    A = []

    for _ in range(H):
        A.append(list(map(int, input().rstrip().split())))

    result = surfaceArea(A)

    fptr.write(str(result) + '\n')

    fptr.close()
