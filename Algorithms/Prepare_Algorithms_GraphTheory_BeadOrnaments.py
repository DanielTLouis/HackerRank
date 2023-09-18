"""
There are N colors of beads. You have bi beads of the ith color. You want to make an ornament by
joining all the beads together. You create the ornament by using the following algorithm:

    * Step #1 Arrange all the beads in any order such that beads of the same color are placed
    together.
    * Step #2 The ornament initially consists of only the first bead from the arrangement.
    * Step #3 For each subsequent bead in order, join it to a bead of the same color in the
    ornament. If there is no bead of the same color, it can be joined to any bead in the ornament.
All beads are distinct, even if they have the same color. Two ornaments are considered different
if two beads are joined by a thread in one configuration, but not in the other. How many different
ornaments can be formed using this algorithm? Return the answer modulo (10^9 +7).
Update/clarification
    Think of the bead formation as a tree and not as a straight line. Any number of beads can be
    connected to a bead.
Example
    b=[2]
    There are two beads of color a: a1 and a2. These can occur as a1,a2 or a2,a1. In both cases,
    the same two beads are joined, so the arrangements are not different. There is 1 way to join
    these beads.
    b=[2,2]
    There are two beads of two colors, a1,a2,b1,b2. They can be arranged as a1,a2,a2,a1,b1,b2 and
    b2,b1. Call these groups A1, A2, B1 and . The 8 possible arranements of groups are shown below.
        1 A1, B1 = a1, a2, b1, b2
        2 A2, B1 = a2, a1, b1, b2
        3 A1, B2 = a1, a2, b2, b1
        4 A2, B2 = a2, a1, b2, b1
        5 B1, A1 = b1, b2, a1, a2
        6 B2, A1 = b2, b1, a1, a2
        7 B1, A2 = b1, b2, a2, a1
        8 B2, A2 = b2, b1, a2, a1
    Note that in line 1, (a1,a2), (a2,a1) and (b1,b) are the connections. This also occurs on line
    8, so these two lines are not different. In fact, line 8 is just line 1 reversed, like
    flipping the string of beads end for end. Using the same logic, the other similar lines are
    (2,6),(3,7),(4,5). There are only 4 different arrangements.
Function Description
    Complete the beadOrnaments function in the editor below.
    beadOrnaments has the following parameters:
        int b[n]: the number of beads of each color
Returns
    int: the number of arrangements modulo (10^9 + 7)
Input Format
    The first line contains the number of test cases T.
    Each of the following T pairs of lines contain:
        - An integer, n, the number of elements in array b
        -  space-separated integers that comprise b
Constraints
    1<=T<=20
    1<=n<=10
    1<=b[i]<=30
Sample Input
    STDIN       Function
    -----       --------
    5           T = 5
    2           b[] size n = 2
    2 1         b = [2, 1]
    2           n = 2
    2 2         b = [2, 2]
    1           n = 1
    4           b = [4]
    2           n = 2
    3 1         b = [3, 1]
    5           n = 5
    1 1 1 1 1   b = [1, 1, 1, 1, 1]
Sample Output
    2
    4
    16
    9
    125
Explanation
    Testcase 1:
        Let us label the beads A1,A2 and B1. Initially, they can be arranged in 4 ways - "A1,A2,
        B1", "A2,A1,B1", "B1,A1,A2", and "B1,A2,A1".
        For each of the first two arrangements, an ornament can be formed in 2 ways (A1-A2-B1 or
        B1-A1-A2 from the first one and A2-A1-B1 or B1-A2-A1 from the second one).
        For each of the last two arrangements, an ornament can be formed in 1 way.
        However, of the total 6 possible ornaments, there are only 2 unique ones : A1 - A2 - B1,
        and A2 - A1 - B1.
    Testcase 2:
        The possible unique ornaments are A1 - A2 - B1 - B2, A1 - A2 - B2 - B1, A2 - A1 - B1 - B2,
         and A2 - A1 - B2 - B1.
    Testcase 3:
        For the third test-case, it might be easier to see there are only 2 types of graphs on 4
        vertices: the path or the star. It's not hard to see that there are 12 paths and 4 stars
        (explanation courtesy: zlangley)
    Testcase 5:
        For the fifth test-case, a lot of people claimed that the total number of possible ways is
        (5!)/2=60. But that is wrong. The correct answer is 125. Here's the hint: Once again,
        you've to think of it as a tree.
        So one possible arrangement can be:
        A is a root node and has two edges (A-B and A-C). Now, think of B as a sub-root node with
        two edges (B-D and B-E). Similarly, you can figure out the other possible bead
        arrangements. This will lead you to the correct answer.
"""

#!/bin/python3

import os
import sys
from functools import reduce
from operator import mul

#
# Complete the beadOrnaments function below.
#
def beadOrnaments(b):
    return int((reduce(mul, map(lambda x: x ** (x - 1), b), 1) * (sum(b) ** (len(b) - 2))) % ((10 ** 9) + 7))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input())

    for t_itr in range(t):
        b_count = int(input())

        b = list(map(int, input().rstrip().split()))

        result = beadOrnaments(b)

        fptr.write(str(result) + '\n')

    fptr.close()
