"""
You will be given a square chess board with one queen and a number of obstacles 
placed on it. Determine how many squares the queen can attack.
A queen* is standing on an nXn chessboard**. The chess board's rows are numbered 
from 1 to n, going from bottom to top. Its columns are numbered from 1 to n, 
going from left to right. Each square is referenced by a tuple, (r,c), describing 
the row, r, and column, c, where the square is located.
* https://en.wikipedia.org/wiki/Queen_%28chess%29 *
** https://en.wikipedia.org/wiki/Chess **
The queen is standing at position (r_q,c_q). In a single move, she can attack any 
square in any of the eight directions (left, right, up, down, and the four 
diagonals). In the diagram below, the green circles denote all the cells the 
queen can attack from (4,4):
    image
There are obstacles on the chessboard, each preventing the queen from attacking 
any square beyond it on that path. For example, an obstacle at location (3,5) in 
the diagram above prevents the queen from attacking cells (3,5), (2,6), and (1,7):
    image
Given the queen's position and the locations of all the obstacles, find and print 
the number of squares the queen can attack from her position at (r_q,c_q). In the 
board above, there are 24 such squares.
Function Description
    Complete the queensAttack function in the editor below.
    queensAttack has the following parameters:
        - int n: the number of rows and columns in the board
        - nt k: the number of obstacles on the board
        - int r_q: the row number of the queen's position
        - int c_q: the column number of the queen's position
        - int obstacles[k][2]: each element is an array of  integers, the row and 
        column of an obstacle
Returns
    - int: the number of squares the queen can attack
Input Format
    The first line contains two space-separated integers n and k, the length of 
    the board's sides and the number of obstacles.
    The next line contains two space-separated integers r_q and c_q, the queen's 
    row and column position.
    Each of the next k lines contains two space-separated integers r[i] and c[i], 
    the row and column position of obstacle[i].
Constraints
    0<n<=10^5
    0<=k<=10^5
    A single cell may contain more than one obstacle.
    There will never be an obstacle at the position where the queen is located.
Subtasks
    For 30% of the maximum score:
        0<n<=100
        0<=k<=100
    For 55% of the maximum score:
        0<n<=1000
        0<=k<=10^5
Sample Input 0
    4 0
    4 4
Sample Output 0
    9
Explanation 0
    The queen is standing at position (4,4) on a 4X4 chessboard with no obstacles:
        image
Sample Input 1
    5 3
    4 3
    5 5
    4 2
    2 3
Sample Output 1
    10
Explanation 1
    The queen is standing at position (4,3) on a %X% chessboard with k=3 
    obstacles:
        image
    The number of squares she can attack from that position is 10.
Sample Input 2
    1 0
    1 1
Sample Output 2
    0
Explanation 2
    Since there is only one square, and the queen is on it, the queen can move 0 
    squares.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'queensAttack' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER n
#  2. INTEGER k
#  3. INTEGER r_q
#  4. INTEGER c_q
#  5. 2D_INTEGER_ARRAY obstacles
#

def queensAttack(n, k, r_q, c_q, obstacles):
    # Write your code here
    q = r_q+(c_q)*1j
    see = 0
    obs = set([(a+b*1j) for a,b in obstacles])
    for k in range(8):
        for e in range(1,n):
            next = q+e*(1+(k//4)*1j)*1j**(k-1)
            r, i = next.real, next.imag
            if next not in obs and (0<r<=n) and (0<i<=n): see += 1
            else: break
    return see

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    k = int(first_multiple_input[1])

    second_multiple_input = input().rstrip().split()

    r_q = int(second_multiple_input[0])

    c_q = int(second_multiple_input[1])

    obstacles = []

    for _ in range(k):
        obstacles.append(list(map(int, input().rstrip().split())))

    result = queensAttack(n, k, r_q, c_q, obstacles)

    fptr.write(str(result) + '\n')

    fptr.close()
