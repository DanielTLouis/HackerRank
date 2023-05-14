"""
Markov takes out his Snakes and Ladders game, stares at the board and wonders: "If I can
always roll the die to whatever number I want, what would be the least number of rolls to
 reach the destination?"
Rules The game is played with a cubic die of 6 faces numbered 1 to 6.
    1. Starting from square 1, land on square 100 with the exact roll of the die. If moving
    the number rolled would place the player beyond square 100, no move is made.
    2. If a player lands at the base of a ladder, the player must climb the ladder. Ladders go
    up only.
    3. If a player lands at the mouth of a snake, the player must go down the snake and come
    out through the tail. Snakes go down only.
Function Description
    Complete the quickestWayUp function in the editor below. It should return an integer that
    represents the minimum number of moves required.
    quickestWayUp has the following parameter(s):
        * ladders: a 2D integer array where each ladders[i] contains the start and end cell
        numbers of a ladder
        * snakes: a 2D integer array where each snakes[i] contains the start and end cell
        numbers of a snake
Input Format
    The first line contains the number of tests, t.
    For each testcase:
        - The first line contains n, the number of ladders.
        - Each of the next n lines contains two space-separated integers, the start and end of
        a ladder.
        - The next line contains the integer n, the number of snakes.
        - Each of the next n lines contains two space-separated integers, the start and end of
        a snake.
Constraints
    1<=t<=10
    1<=n,m<=15
    The board is always 10X10 with squares numbered 1 to 100.
    Neither square 1 nor square 100 will be the starting point of a ladder or snake.
    A square will have at most one endpoint from either a snake or a ladder.
Output Format
    For each of the t test cases, print the least number of rolls to move from start to finish
    on a separate line. If there is no solution, print -1.
Sample Input
    2
    3
    32 62
    42 68
    12 98
    7
    95 13
    97 25
    93 37
    79 27
    75 19
    49 47
    67 17
    4
    8 52
    6 80
    26 42
    2 72
    9
    51 19
    39 11
    37 29
    81 3
    59 5
    79 23
    53 7
    43 33
    77 21
Sample Output
    3
    5
Explanation
    For the first test:
    The player can roll a 5 and a 6 to land at square 12. There is a ladder to square 98. A
    roll of 2 ends the traverse in 3 rolls.
    For the second test:
    The player first rolls 5 and climbs the ladder to square 80. Three rolls of 6 get to
    square 98. A final roll of 2 lands on the target square in 5 total rolls.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'quickestWayUp' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. 2D_INTEGER_ARRAY ladders
#  2. 2D_INTEGER_ARRAY snakes
#
def quickestWayUp(ladders, snakes):
    # Write your code here
    # Store snakes and ladders for lookup
    graph = {s[0]: s[1] for s in snakes}
    graph.update({l[0]: l[1] for l in ladders})

    visited = set([1])
    queue = [1]
    rolls = {}

    while queue:
        idx = queue.pop(0)
        for i in range(1, 7):
            # If neighbour is a snake/ladder, jump to its end point
            # else, increment as is
            neighbour = graph.get(idx + i, idx + i)
            if neighbour not in visited:
                rolls[neighbour] = rolls.get(idx, 0) + 1
                visited.add(neighbour)
                queue.append(neighbour)
            if neighbour == 100:
                return rolls[neighbour]
    return -1

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        n = int(input().strip())

        ladders = []

        for _ in range(n):
            ladders.append(list(map(int, input().rstrip().split())))

        m = int(input().strip())

        snakes = []

        for _ in range(m):
            snakes.append(list(map(int, input().rstrip().split())))

        result = quickestWayUp(ladders, snakes)

        fptr.write(str(result) + '\n')

    fptr.close()
