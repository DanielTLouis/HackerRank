"""
Ema built a quantum computer! Help her test its capabilities by
solving the problem below.
Given a grid of size nXm, each cell in the grid is either good
or bad.
A valid plus is defined here as the crossing of two segments
(horizontal and vertical) of equal lengths. These lengths must
be odd, and the middle cell of its horizontal segment must cross
the middle cell of its vertical segment.
In the diagram below, the blue pluses are valid and the orange
ones are not valid.
    pluseses.png
Find the two largest valid pluses that can be drawn on good
cells in the grid, and return an integer denoting the maximum
product of their areas. In the above diagrams, our largest
pluses have areas of 5 and 9. The product of their areas is
5X9=45.
Note: The two pluses cannot overlap, and the product of their
areas should be maximal.
Function Description
    Complete the twoPluses function in the editor below. It
    should return an integer that represents the area of the two
    largest pluses.twoPluses has the following parameter(s):
        -grid: an array of strings where each string represents
        a row and each character of the string represents a
        column of that row
Input Format
    The first line contains two space-separated integers, n and
    m.
    Each of the next n lines contains a string of m characters
    where each character is either G (good) or B (bad). These
    strings represent the rows of the grid. If the yth character
    in the xth line is G, then (x,y) is a good cell. Otherwise
    it's a bad cell.
Constraints
    2<=n<=15
    2<=m<=15
Output Format
    Find 2 pluses that can be drawn on good cells of the grid, and return an integer denoting the maximum product of their areas.
Sample Input 0
    5 6
    GGGGGG
    GBBBGB
    GGGGGG
    GGBBGB
    GGGGGG
Sample Output 0
    5
Sample Input 1
    6 6
    BGBBGB
    GGGGGG
    BGBBGB
    GGGGGG
    BGBBGB
    BGBBGB
Sample Output 1
    25
Explanation
    Here are two possible solutions for Sample 0 (left) and
    Sample 1 (right):
        plusss.png
    Explanation Key:
        Green: good cell
        Red: bad cell
        Blue: possible pluses.
    For the explanation below, we will refer to a plus of length
    i as Pi.
Sample 0
    There is enough good space to color one P3 plus and one P1 plus. Area(P3)=5 units, and Area(P1)=1 unit. The product of their areas is 5X1=5.
Sample 1
    There is enough good space to color two P3 pluses. Area(P3)=5 units. The product of the areas of our two P3 pluses is 5X5=25.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'twoPluses' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING_ARRAY grid as parameter.
#

def twoPluses(grid):
    # Write your code here
    plusses=[]
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] != 'B':
                max_plus_length=min((len(grid)-1)//2,
                    (len(grid[0])-1)//2, i, j, len(grid)-i-1, len(grid[0])-j-1)
                plus = set()
                plus.add((i,j))
                plusses.append(plus)
                for k in range(1, max_plus_length+1):
                    if grid[i-k][j] == 'G' and \
                       grid[i+k][j] == 'G' and \
                       grid[i][j-k] == 'G' and \
                       grid[i][j+k] == 'G':
                        plus.add((i-k,j))
                        plus.add((i+k,j))
                        plus.add((i,j-k))
                        plus.add((i,j+k))
                    else:
                        break
                    subplus = plus.copy()
                    plusses.append(subplus)

    max_area_product = 0
    for pi in plusses:
        for pj in plusses:
            if not pi.intersection(pj):
                max_area_product = max(max_area_product, len(pi)*len(pj))

    return max_area_product

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    m = int(first_multiple_input[1])

    grid = []

    for _ in range(n):
        grid_item = input()
        grid.append(grid_item)

    result = twoPluses(grid)

    fptr.write(str(result) + '\n')

    fptr.close()
