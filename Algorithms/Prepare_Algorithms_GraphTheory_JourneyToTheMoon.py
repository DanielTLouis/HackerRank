"""
The member states of the UN are planning to send 2 people to the moon. They want them to be
from different countries. You will be given a list of pairs of astronaut ID's. Each pair is
made of astronauts from the same country. Determine how many pairs of astronauts from
different countries they can choose from.
Example
    n=4
    astronaut = [1,2],[2,3]
    There are 4 astronauts numbered 0 through 3. Astronauts grouped by country are [0] and
    [1,2,3]. There are 3 pairs to choose from: [0,1],[0,2], and [0,3].
Function Description
    Complete the journeyToMoon function in the editor below.
    journeyToMoon has the following parameter(s):
        -int n: the number of astronauts
        -int astronaut[p][2]: each element astronaut[i] is a 2 element array that represents
        the ID's of two astronauts from the same country
Returns
    - int: the number of valid pairs
Input Format
    The first line contains two integers n and p, the number of astronauts and the number of
    pairs.
    Each of the next p lines contains 2 space-separated integers denoting astronaut ID's of
    two who share the same nationality.
Constraints
    1<=n<=10^5
    1<=p<=10^4
Sample Input 0
    5 3
    0 1
    2 3
    0 4
Sample Output 0
    6
Explanation 0
    Persons numbered [0,1,4] belong to one country, and those numbered [2,3] belong to
    another. The UN has 6 ways of choosing a pair:
        [0,2],[0,3],[1,2],[1,3],[4,2],[4,3]
Sample Input 1
    4 1
    0 2
Sample Output 1
    5
Explanation 1
    Persons numbered [0,2] belong to the same country, but persons 1 and 3 don't share
    countries with anyone else. The UN has 5 ways of choosing a pair:
        [0,1],[0,3],[1,2],[1,3],[2,3]
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'journeyToMoon' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER n
#  2. 2D_INTEGER_ARRAY astronaut
#
def bfs(graph, n):
    result = 0
    # sizes = [0 for _ in range(n)]
    seen = [False for _ in range(n)]
    ini_queue = [None for _ in range(n)]
    for v in range(n):
        if (seen[v]):
            continue
        counter = 0
        seen[v] = True
        queue = ini_queue[:]

        i = 0
        j = 0
        queue[j] = v
        j += 1
        while (i < j):
            w = queue[i]
            i += 1
            counter += 1
            for x in graph[w]:
                if not seen[x]:
                    seen[x] = True
                    queue[j] = x
                    j += 1
        result += math.comb(counter, 2)
    return result

def journeyToMoon(n, astronauts):
    actual_n = 0
    for t in astronauts:
        actual_n = max(max(t) + 1, actual_n)
    graph = [[] for _ in range(actual_n)]

    for [a, b] in astronauts:
        graph[a].append(b)
        graph[b].append(a)
    #sizes = bfs(graph, n)
    return math.comb(n, 2) - bfs(graph, actual_n) #sum(math.comb(x, 2) for x in sizes if x > 0)
    # k = sum(math.comb(x, 2) for x in sizes_of_countries)
    # return math.comb(n, 2) - k

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    p = int(first_multiple_input[1])

    astronaut = []

    for _ in range(p):
        astronaut.append(list(map(int, input().rstrip().split())))

    result = journeyToMoon(n, astronaut)

    fptr.write(str(result) + '\n')

    fptr.close()
