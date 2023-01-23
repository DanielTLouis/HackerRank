"""
KnightL is a chess piece that moves in an L shape. We define the possible moves of
KnightL(a,b) as any movement from some position (x1,y1) to some (x2,y2) satisfying
either of the following:
    x2=x1 +- a and y2=y1 +- b, or
    x2=x1 +- b and y2=y1 +- a
Note that (a,b) and (b,a) allow for the same exact set of movements. For example, the
diagram below depicts the possible locations that KnightL(1,2) or KnightL(2,1) can move
to from its current location at the center of a 5X5 chessboard:
    image
Observe that for each possible movement, the Knight moves 2 units in one direction
(i.e., horizontal or vertical) and 1 unit in the perpendicular direction.
Given the value of n for an nXn chessboard, answer the following question for each (a,b)
pair where 1<=a,b<n:
    -What is the minimum number of moves it takes for KnightL(a,b) to get from position
    (0,0) to position (n-1, n-1)? If it's not possible for the Knight to reach that
    destination, the answer is -1 instead.
Then print the answer for each KnightL(a,b) according to the Output Format specified
below.
Input Format
    A single integer denoting n.
Constraints
    5<=n<=25
Output Format
    Print exactly n-1 lines of output in which each line i (where 1<=i<n) contains n-1 space-separated integers describing the minimum number of moves KnightL(i,j) must make for each respective j (where 1<=j<n). If some KnightL(i,j) cannot reach position (n-1,n-1), print -1 instead.
    For example, if n=3, we organize the answers for all the (i,j) pairs in our output like this:
        (1,1) (1,2)
        (2,1) (2,2)
Sample Input 0
    5
Sample Output 0
    4 4 2 8
    4 2 4 4
    2 4 -1 -1
    8 4 -1 1
Explanation 0
    The diagram below depicts possible minimal paths for KnightL(1,1), Knight(1,2), and
    Knight(1,3):
        image
    One minimal path for knightL(1,4) is:
        (0,0)->(1,4)->(2,0)->(3,4)->(4,0)->(0,1)->(4,2)->(0,3)->(4,4)
    We then print 4 4 2 8 as our first line of output because KnightL(1,1) took 4 moves,
    KnightL(1,2) took 4 moves, KnightL(1,3) took 2 moves, and Knight(1,4) took 8 moves.
    In some of the later rows of output, it's impossible for KnightL(i,j) to reach
    position (4,4). For example, KightL(3,3) can only move back and forth between (0,0)
    and (3,3) so it will never reach (4,4).
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'knightlOnAChessboard' function below.
#
# The function is expected to return a 2D_INTEGER_ARRAY.
# The function accepts INTEGER n as parameter.
#
def knightlOnAChessboard(n):
    from collections import deque

    def get_min_moves(a: int, b: int) -> int:
        q = deque([((0, 0), 0)])
        visited = {(0, 0)}

        while q:
            coord, dist = q.popleft()
            i, j = coord
            next_coords = [
                (i + a, j + b), (i + b, j + a),
                (i + a, j - b), (i + b, j - a),
                (i - a, j + b), (i - b, j + a),
                (i - a, j - b), (i - b, j - a),
            ]
            for ni, nj in next_coords:
                if 0 <= ni < n and 0 <= nj < n:
                    if (ni, nj) in visited:
                        continue
                    if ni == nj == n - 1:
                        return dist + 1
                    q.append(((ni, nj), dist + 1))
                    visited.add((ni, nj))
        return -1

    res = [[None] * (n - 1) for _ in range(n - 1)]
    for i in range(n - 1):
        for j in range(i + 1):
            res[i][j] = res[j][i] = get_min_moves(i + 1, j + 1)
    return res

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    result = knightlOnAChessboard(n)

    fptr.write('\n'.join([' '.join(map(str, x)) for x in result]))
    fptr.write('\n')

    fptr.close()
