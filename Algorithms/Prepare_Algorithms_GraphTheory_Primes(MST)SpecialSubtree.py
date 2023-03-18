"""
Given a graph which consists of several edges connecting its nodes, find a 
subgraph of the given graph with the following properties:
    -The subgraph contains all the nodes present in the original graph.
    -The subgraph is of minimum overall weight (sum of all edges) among all such 
    subgraphs.
    -It is also required that there is exactly one, exclusive path between any 
    two nodes of the subgraph.
One specific node S is fixed as the starting point of finding the subgraph using 
Prim's Algorithm*.
Find the total weight or the sum of all edges in the subgraph.
* https://en.wikipedia.org/wiki/Prim%27s_algorithm *
Example
    n=3
    edges=[[1,2,2],[2,3,2],[1,3,3]]
    start=1
        image
    Starting from node 1, select the lower weight edge, i.e. 1<->2, weight 2.
    Choose between the remaining edges, 1<->3, weight 3, and 2<->3, weight 2.
    The lower weight edge is 2<->3 weight 2.
    All nodes are connected at a cost of 2+2=4. The edge 1<->3 is not included 
    in the subgraph.
Function Description
    Complete the prims function in the editor below.
    prims has the following parameter(s):
        -int n: the number of nodes in the graph
        -int edges[m][3]: each element contains three integers, two nodes numbers 
        that are connected and the weight of that edge
        -int start: the number of the starting node
Returns
    int: the minimum weight to connect all nodes in the graph
Input Format
    The first line has two space-separated integers n and m, the number of nodes 
    and edges in the graph.
    Each of the next m lines contains three space-separated integers u, v and w, 
    the end nodes of edges[i], and the edge's weight.
    The last line has an integer start, the starting node.
Constraints
    2<=n<=3000
    1<=m<=(n*(n-1))/2
    1<=u,v,start<=n
    0<=w<=10^5
    There may be multiple edges between two nodes.
Sample Input 0
    5 6
    1 2 3
    1 3 4
    4 2 6
    5 2 2
    2 3 5
    3 5 7
    1
Sample Output 0
    15
Explanation 0
    The graph given in the test case is shown as :
        image
        -The starting node is 1 (in the given test case)
    Applying the Prim's algorithm, edge choices available at first are :
    1->2 (WT. 3) and 1->3 (WT. 4) , out of which 1->2 is chosen (smaller 
    weight of edge).
    Now the available choices are :
    1->3 (WT. 4) , 2->3 (WT. 5) , 2->5 (WT. 2) and 2->4 (WT. 6) , out of which 
    2->5 is chosen by the algorithm.
    Following the same method of the algorithm, the next chosen edges, 
    sequentially are :
    1->3 and 2->4.
    Hence the overall sequence of edges picked up by Prim's are:
    1->2:2->5:1->3:2->4
    and the total weight of the MST (minimum spanning tree) is : 3+2+4+6=15
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'prims' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER n
#  2. 2D_INTEGER_ARRAY edges
#  3. INTEGER start
#

def prims(n, edges, start):
    # Write your code here
    vertices = {start}
    result = 0
    while len(vertices) < n:
        newEdges = [e for e in edges if ((e[0] in vertices and e[1] not in vertices) 
            or (e[1] in vertices and e[0] not in vertices))]
        edge = min(newEdges, key = lambda e: e[2])
        vertices.update(edge[:2])
        result += edge[2]
    return result

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    m = int(first_multiple_input[1])

    edges = []

    for _ in range(m):
        edges.append(list(map(int, input().rstrip().split())))

    start = int(input().strip())

    result = prims(n, edges, start)

    fptr.write(str(result) + '\n')

    fptr.close()
