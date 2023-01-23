"""
Victoria has a tree, T, consisting of N nodes numbered from 1
to N. Each edge from node U_i to V_i in tree T has an integer
weight, W_i.
Let's define the cost, C, of a path from some node X to some
other node Y as the maximum weight (W) for any edge in the
unique path from node X to node Y.
Victoria wants your help processing Q queries on tree T, where
each query contains 2 integers, L and R, such that L<=R. For
each query, she wants to print the number of different paths in
T that have a cost, C, in the inclusive range [L,R].
It should be noted that path from some node X to some other node
Y is considered same as path from node Y to X i.e {X,Y} is same
as {Y,X}.
Input Format
    The first line contains 2 space-separated integers, N (the
    number of nodes) and Q (the number of queries),
    respectively.
    Each of the N-1 subsequent lines contain 3 space-separated
    integers, U, V, and W, respectively, describing a
    bidirectional road between nodes U and V which has weight W.
    The Q subsequent lines each contain 2 space-separated
    integers denoting L and R.
Constraints
    1<=N,Q<=10^5
    1<=U,V<=N
    1<=W<=10^9
    1<=L<=R<=10^9
Scoring
    1<=N,Q<=10^3 for 30% of the test data.
    1<=N,Q<=10^5 for 100% of the test data.
Output Format
    For each of the Q queries, print the number of paths in T
    having cost C in the inclusive range [L,R] on a new line.
Sample Input
    5 5
    1 2 3
    1 4 2
    2 5 6
    3 4 1
    1 1
    1 2
    2 3
    2 5
    1 6
Sample Output
    1
    3
    5
    5
    10
Explanation
    Q1: {3,4}
    Q2: {1,3},{3,4},{1,4}
    Q3: {1,4},{1,2},{2,4},{1,3},{2,3}
    Q4: {1,4},{1,2},{2,4},{1,3},{2,3}
    ...etc.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'solve' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. 2D_INTEGER_ARRAY tree
#  2. 2D_INTEGER_ARRAY queries
#
from bisect import bisect_left,bisect_right
parents = {}
rep = {}
def make_set(n):
    global parents,rep
    parents=dict(zip(range(1,n+1),range(1,n+1)))
    rep=dict(zip(range(1,n+1),({i} for i in range(1,n+1))))
def add_edge(x, y,paths,w):
    xroot = find(x)
    yroot = find(y)
    paths[w]+=len(rep[xroot])*len(rep[yroot])
    if xroot == yroot:
        return
    else:
        if len(rep[yroot])<len(rep[xroot]):
            parents[yroot] = xroot
            rep[xroot].update(rep[yroot])
            del rep[yroot]
        else:
            parents[xroot] = yroot
            rep[yroot].update(rep[xroot])
            del rep[xroot]

def find(x):
    if parents[x] != x:
        parent = find(parents[x])
        parents[x] = parent
    return parents[x]
def solve(tree, queries):
    n = len(tree)+1
    tree.sort(key=lambda e:e[2])
    paths = {0:0}
    weights = [0]
    prev = 0
    make_set(len(tree)+1)
    for a,b,w in tree:
        if w != prev:
            weights.append(w)
            paths[w] = paths[prev]
        add_edge(a,b,paths,w)
        prev=w
    for l,r in queries:
        wr = weights[bisect_right(weights,r)-1]
        wl = weights[bisect_right(weights,l-1)-1]
        yield paths[wr]-paths[wl]

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    q = int(first_multiple_input[1])

    tree = []

    for _ in range(n - 1):
        tree.append(list(map(int, input().rstrip().split())))

    queries = []

    for _ in range(q):
        queries.append(list(map(int, input().rstrip().split())))

    result = solve(tree, queries)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
