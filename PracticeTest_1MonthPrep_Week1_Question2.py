"""
Code Practice Flipping The matrix
Sean invented a game involving a 2n X 2n matrix where each cell of the matrix contains an integer. He can reverse any of its rows or columns any number of times. The goal of the game is to maximize the sum of the elements in the  submatrix located in the upper-left quadrant of the matrix.
Given the initial configurations for q matrices, help Sean reverse the rows and columns of each matrix in the best possible way so that the sum of the elements in the matrix's upper-left quadrant is maximal.
Example
  matrix=[[1,2],[3,4]]
  1 2
  3 4
  It is 2X2 and we want to maximize the top left quadrant, a  matrix. Reverse row :
    1 2
    4 3
  And now reverse column 0:
    4 2
    1 3
  The maximal sum is 4.
Function Description
  Complete the flippingMatrix function in the editor below.
  flippingMatrix has the following parameters:
    - int matrix[2n][2n]: a 2-dimensional array of integers

Returns
- int: the maximum sum possible.

Input Format

The first line contains an integer , the number of queries.

The next  sets of lines are in the following format:

The first line of each query contains an integer, .
Each of the next  lines contains  space-separated integers  in row  of the matrix.
Constraints

, where .
Sample Input

STDIN           Function
-----           --------
1               q = 1
2               n = 2
112 42 83 119   matrix = [[112, 42, 83, 119], [56, 125, 56, 49], \
56 125 56 49              [15, 78, 101, 43], [62, 98, 114, 108]]
15 78 101 43
62 98 114 108
Sample Output

414
Explanation

Start out with the following  matrix:

Perform the following operations to maximize the sum of the  submatrix in the upper-left quadrant:

Reverse column  (), resulting in the matrix:
Reverse row  (), resulting in the matrix:
The sum of values in the  submatrix in the upper-left quadrant is .
"""
#!/bin/python3

import math
import os
import random
import re
import sys



#
# Complete the 'flippingMatrix' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY matrix as parameter.
#
def flippingMatrix(matrix):
    # Write your code here
    """
    for i in range(0, int(len(matrix)/2)):
        for j in range(0,len(matrix)):
            temp = matrix[len(matrix)-1 - i][j]
            matrix[len(matrix)-1 - i][j] = matrix[i][j]
            matrix[i][j] = temp
    for i in range(0, len(matrix)):
        matrix[i].reverse()
    for i in range(0, len(matrix)):
        print(matrix[i])
    """
    n = len(matrix)
    s = 0
    for i in range(n//2):
        for j in range(n//2):
            s += max(matrix[i][j], matrix[i][n-j-1], matrix[n-i-1][j], matrix[n-i-1][n-j-1])
    return s


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        n = int(input().strip())

        matrix = []

        for _ in range(2 * n):
            matrix.append(list(map(int, input().rstrip().split())))

        result = flippingMatrix(matrix)

        fptr.write(str(result) + '\n')

    fptr.close()
