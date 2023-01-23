"""
There is an undirected tree where each vertex is numbered from 1 to n, and each contains
a data value. The sum of a tree is the sum of all its nodes' data values. If an edge is
cut, two smaller trees are formed. The difference between two trees is the absolute
value of the difference in their sums.
Given a tree, determine which edge to cut so that the resulting trees have a minimal
difference between them, then return that difference.
Example
    data=[1,2,3,4,5,6]
    edges=[(1,2),(1,3),(2,6),(3,4),(3,5)]
    In this case, node numbers match their weights for convenience. The graph is shown
    below.
        image
    The values are calculated as follows:
        Edge    Tree 1  Tree 2  Absolute
        Cut     Sum      Sum     Difference
        1        8         13         5
        2        9         12         3
        3        6         15         9
        4        4         17        13
        5        5         16        11
    The minimum absolute difference is 3.
    Note: The given tree is always rooted at vertex 1.
Function Description
    Complete the cutTheTree function in the editor below.
    cutTheTree has the following parameter(s):
        -int data[n]: an array of integers that represent node values
        -int edges[n-1][2]: an 2 dimensional array of integer pairs where each pair
        represents nodes connected by the edge
Returns
    int: the minimum achievable absolute difference of tree sums
Input Format
    The first line contains an integer n, the number of vertices in the tree.
    The second line contains  space-separated integers, where each integer u denotes the
    node[u] data value, data[u].
    Each of then-1  subsequent lines contains two space-separated integers u and v that
    describe edge u<-v in tree t.
Constraints
    3<=n<=10^5
    1<=data[u]<=1001, where 1<=u<=n.
Sample Input
    STDIN                       Function
    -----                       --------
    6                           data[] size n = 6
    100 200 100 500 100 600     data = [100, 200, 100, 500, 100, 600]
    1 2                         edges = [[1, 2], [2, 3], [2, 5], [4, 5], [5, 6]]
    2 3
    2 5
    4 5
    5 6
Sample Output
    400
Explanation
    We can visualize the initial, uncut tree as:
        cut-the-tree.png
    There are n-1=5 edges we can cut:
        1.Edge 1<->2 results in d_(1<->2) = 1500 - 100 = 1400
        2.Edge 2<->3 results in d_(2<->3) = 1500 - 100 = 1400
        3.Edge 2<->5 results in d_(2<->5) = 1200 - 400 = 800
        4.Edge 4<->5 results in d_(4<->5) = 1100 - 500 = 600
        5.Edge 5<->6 results in d_(5<->6) = 1000 - 600 = 400
    The minimum difference is 400.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'cutTheTree' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER_ARRAY data
#  2. 2D_INTEGER_ARRAY edges
#
sys.setrecursionlimit(10**5)

def dfs(conn , node, sums, data, parent):
    if sums[node]!=0:
        return sums[node]
    nb = conn[node]
    if len(nb)==1 and node!=0:
        sums[node] = data[node]
        return data[node]
    ans = 0
    for n1 in nb:
        if n1!=parent:
            ans += dfs(conn, n1, sums, data, node)
    ans += data[node]
    sums[node] = ans
    return ans

def cutTheTree(data, edges):
    conn = [[] for i in range(n)]
    for e in edges:
        e1 = e[0]-1
        e2 = e[1]-1
        conn[e1].append(e2)
        conn[e2].append(e1)
    sums = [0 for i in range(n)]
    dfs(conn , 0, sums, data, 0)
    print(sums)
    mindiff = 999999999
    for i in range(1, n):
        ## seperate node i
        sum1 = sums[i]
        sum2 = sums[0] - sums[i]
        diff = abs(sum1 - sum2)
        mindiff = min(mindiff, diff)
    return mindiff

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    data = list(map(int, input().rstrip().split()))

    edges = []

    for _ in range(n - 1):
        edges.append(list(map(int, input().rstrip().split())))

    result = cutTheTree(data, edges)

    fptr.write(str(result) + '\n')

    fptr.close()
