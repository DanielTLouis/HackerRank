"""
You are given a tree (a simple connected graph with no cycles).
Find the maximum number of edges you can remove from the tree to get a forest such that each
connected component of the forest contains an even number of nodes.
As an example, the following tree with 4 nodes can be cut at most 1 time to create an even
forest.
    image
Function Description
    Complete the evenForest function in the editor below. It should return an integer as
    described.
    evenForest has the following parameter(s):
        t_nodes: the number of nodes in the tree
        t_edges: the number of undirected edges in the tree
        t_from: start nodes for each edge
        t_to: end nodes for each edge, (Match by index to t_from.)
Input Format
    The first line of input contains two integers t_nodes and t_edges, the number of nodes and
    edges.
    The next t_edges lines contain two integers T_from [i[ and t_to [0]which specify nodes
    connected by an edge of the tree. The root of the tree is node 1.
Constraints
    2<=n<=100
    n isAnElementOf(Z+ even)
    Note: The tree in the input will be such that it can always be decomposed into components
    containing an even number of nodes. Z+even is the set of positive even integers.
Output Format
    Print the number of removed edges.
Sample Input 1
    10 9
    2 1
    3 1
    4 3
    5 2
    6 1
    7 2
    8 6
    9 8
    10 8
Sample Output 1
    2
Explanation 1
    Remove edges (1,3) and (1,6) to get the desired result.
        imageimage
    No more edges can be removed.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

class Graph:
    def __init__(self, n, t_from, t_to):
        self.n_nodes = n
        self.adj_list = {i:set() for i in range(n)}
        for w, v in zip(t_from, t_to):
            self.adj_list[w-1].add(v-1)
            self.adj_list[v-1].add(w-1)
        self.out = 0

    def dfs(self, v, p):
        s = (1 + sum(self.dfs(w, v) for w in self.adj_list[v] if w != p)) % 2
        self.out += not s
        return s


# Complete the evenForest function below.
def evenForest(t_nodes, t_edges, t_from, t_to):
    g = Graph(t_nodes, t_from, t_to)
    g.dfs(0, 0)
    return g.out-1

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t_nodes, t_edges = map(int, input().rstrip().split())

    t_from = [0] * t_edges
    t_to = [0] * t_edges

    for i in range(t_edges):
        t_from[i], t_to[i] = map(int, input().rstrip().split())

    res = evenForest(t_nodes, t_edges, t_from, t_to)

    fptr.write(str(res) + '\n')

    fptr.close()
