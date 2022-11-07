"""
There are 2XN nodes in an undirected graph, and a number of edges connecting some 
nodes. In each edge, the first value will be between 1 and N, inclusive. The 
second node will be between N+1 and 2XN, inclusive. Given a list of edges, 
determine the size of the smallest and largest connected components that have 2 
or more nodes. A node can have any number of connections. The highest node value 
will always be connected to at least 1 other node.
Note Single nodes should not be considered in the answer.
Example
    bg=[[1,5],[1,6],[2,4]]
    image
    The smaller component contains 2 nodes and the larger contains 3. Return the 
    array [2,3].
Function Description
    Complete the connectedComponents function in the editor below.
    connectedComponents has the following parameter(s):
        - int bg[n][2]: a 2-d array of integers that represent node ends of graph 
        edges
Returns
    - int[2]: an array with 2 integers, the smallest and largest component sizes
Input Format
    The first line contains an integer n, the size of bg.
    Each of the next n lines contain two space-separated integers, bg[i][0] and 
    bg[i]]1.
Constraints
    1<=numberofnodesN<=15000
    1<=bg[i][0]<=N
    N+1<=bg[i][1]<=2N
Sample Input
    STDIN   Function
    -----   --------
    5       bg[] size n = 5
    1 6     bg = [[1, 6],[2, 7], [3, 8], [4,9], [2, 6]]
    2 7
    3 8
    4 9
    2 6
Sample Output
    2 4
Explanation
    image
    Since the component with node 5 contains only one node, it is not considered.
    The number of vertices in the smallest connected component in the graph is 2 
    based on either (3,8) or (4,9).
    The number of vertices in the largest connected component in the graph is 4 
    i.e. 1-2-6-7.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'componentsInGraph' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts 2D_INTEGER_ARRAY gb as parameter.
#

def componentsInGraph(gb):
    # Write your code here
    # Build graph
    graph = {}
    for l,r in gb:
        if l in graph: 
            graph[l].add(r)
        else: graph[l] = {r}
        if r in graph: 
            graph[r].add(l)
        else: graph[r] = {l}

    # find all nodes in each cluster and count the number
    # of nodes
    visited = set() 
    cluster = 0 # cluster index
    counter = [] # number of nodes in cluster
    for node in graph:
        if node not in visited:
    # if its unvisited node, its a new cluster
            counter.append(0)
    # find all nodes in this cluster start with current node
            stack = [node]
            while stack:
    # get the next node in cluster
                n = stack.pop()
                if n not in visited:
                    counter[cluster] += 1
    # mark node as visited
                    visited.add(n)
    # add connected nodes to the stack
                    stack.extend(graph[n].difference(visited))
    # if node was not visited, it is a new cluster
            cluster += 1
    return [min(counter), max(counter)]

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    gb = []

    for _ in range(n):
        gb.append(list(map(int, input().rstrip().split())))

    result = componentsInGraph(gb)

    fptr.write(' '.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
