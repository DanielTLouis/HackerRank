"""
Greg has a tree of nodes containing integer data. He wants to
insert a node with some non-zero integer value somewhere into
the tree. His goal is to be able to cut two edges and have the
values of each of the three new trees sum to the same amount.
This is called a balanced forest. Being frugal, the data value
he inserts should be minimal. Determine the minimal amount that
a new node can have to allow creation of a balanced forest. If
it's not possible to create a balanced forest, return -1.
For example, you are given node values c=[15,12,8,14,13] and
edges=[[1,2],[1,3],[1,4],[4,5]]. It is the following tree:
    image
The blue node is root, the first number in a node is node number
and the second is its value. Cuts can be made between nodes 1
and 2 and nodes 1 and 4 to have three trees with sums 27, 27 and
8. Adding a new node w of c[w]=19 to the third tree completes
the solution.
Function Description
    Complete the balancedForest function in the editor below. It
    must return an integer representing the minimum value of c[w]
    that can be added to allow creation of a balanced forest, or
    -1 if it is not possible.
    balancedForest has the following parameter(s):
        -c: an array of integers, the data values for each node
        -edges: an array of 2 element arrays, the node pairs per
        edge
Input Format
    The first line contains a single integer, q, the number of
    queries.
    Each of the following q sets of lines is as follows:
        -The first line contains an integer, n, the number of
        nodes in the tree.
        -The second line contains n space-separated integers
        describing the respective values of c[1],c[2],...,c[n],
        where each c[i] denotes the value at node i.
        -Each of the following n-1 lines contains two
        space-separated integers, x[j] and y[j], describing edge
        j connecting nodes x[j] and y[j].
Constraints
    1<=q<=5
    1<=n<=5X10^4
    1<=c[i]<=10^9
    Each query forms a valid undirected tree.
Subtasks
    For 30% of the maximum score:
        1<=n<=100
        1<=c[i]<=100
    For 50% of the maximum score:
        1<=n<=2000
        1<=c[i]<=10^9
Output Format
    For each query, return the minimum value of the integer
    c[w]. If no such value exists, return -1 instead.
Sample Input
    2
    5
    1 2 2 1 1
    1 2
    1 3
    3 5
    1 4
    3
    1 3 5
    1 3
    1 2
Sample Output
    2
    -1
Explanation
    We perform the following two queries:
    1.The tree initially looks like this:
        image
    Greg can add a new node w=6 with c[w]=2 and create a new
    edge connecting nodes 4 and 6. Then he cuts the edge
    connecting nodes 1 and 4 and the edge connecting nodes 1 and
    3. We now have a three-tree balanced forest where each tree
    has a sum of 3.
        image
    2.In the second query, it's impossible to add a node in such
    a way that we can split the tree into a three-tree balanced
    forest so we return -1.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'balancedForest' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER_ARRAY c
#  2. 2D_INTEGER_ARRAY edges
#
from collections import Counter, defaultdict
from math import inf

def balancedForest(c, edges):
    n = len(c)
    adj = [[] for i in range(n)]
    for v0, v1 in edges:
        adj[v0 - 1].append(v1 - 1)
        adj[v1 - 1].append(v0 - 1)

    def sumTree(i, p):
        s = 0
        for j in adj[i]:
            if j != p:
                s += sumTree(j, i)

        s += c[i]
        sumCounts[s] += 1
        totals[i] = s
        return s

    def minExtra(i, p, path):
        s = totals[i]
        path.add(s)
        m = min((minExtra(j, i, path) for j in adj[i] if j != p), default=inf)

        if 3*s < t:
            if (t + s) % 2 == 0:
                s0 = (t + s) // 2
                if s0 in path:
                    m = min(m, s0 - 2*s)
                s1 = (t - s) // 2
                sumCount = sumCounts[s1]
                if sumCount > 0 and (s1 not in path or sumCount > 1):
                    m = min(m, s1 - s)
        else:
            s0 = 2*s
            if s0 in path:
                m = min(m, s + s0 - t)
            s0 = t - s
            if s0 in path:
                m = min(m, 2*s - s0)
            # s1 = s
            if sumCounts[s] > 1:
                m = min(m, 3*s - t)

        path.remove(s)
        return m

    sumCounts = Counter()
    totals = {}
    t = sumTree(0, None)
    m = minExtra(0, None, set())
    return m if m < inf else -1

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        n = int(input().strip())

        c = list(map(int, input().rstrip().split()))

        edges = []

        for _ in range(n - 1):
            edges.append(list(map(int, input().rstrip().split())))

        result = balancedForest(c, edges)

        fptr.write(str(result) + '\n')

    fptr.close()
