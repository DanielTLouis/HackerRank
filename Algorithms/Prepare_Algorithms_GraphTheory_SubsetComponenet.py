"""
You are given an array with n 64-bit integers: d[0],d[1],...,d[n-1].
BIT(x, i) = (x >> i) & 1, where B(x,i) is the ith lower bit of x in binary form. If we regard
every bit as a vertex of a graph G, there is an undirected edge between vertices i and j if there
is a value k such that BIT(d[k], i) == 1 && BIT(d[k], j) == 1.
For every subset of the input array, how many connected-components* are there in that graph?
* http://en.wikipedia.org/wiki/Connected_component_(graph_theory) *
A connected component in a graph is a set of nodes which are accessible to each other via a path
of edges. There may be multiple connected components in a graph.
Example
    d={1,2,3,5}
    In the real challenge, there will be 64 nodes associated with each integer in d represented as
    a 64 bit binary value. For clarity, only 4 bits will be shown in the example but all 64 will
    be considered in the calculations.
        Decimal  Binary Edges   Node ends
        d[0] = 1   0001   0
        d[1] = 2   0010   0
        d[2] = 3   0011   1       0 and 1
        d[3] = 5   0101   1       0 and 2
    Consider all subsets:
                    Edges
        Subset   Count  Nodes  Connected components
        {1}         0           64
        {2}         0           64
        {3}         1   0-1     63
        {5}         1   0-2     63
        {1,2}       0           64
        {1,3}       1   0-1     63
        {1,5}       1   0-2     63
        {2,3}       1   0-1     63
        {2,5}       1   0-2     63
        {3,5}       2   0-1-2   62
        {1,2,3}     1   0-1     63
        {1,2,5}     1   0-2     63
        {1,3,5}     2   0-1-2   62
        {2,3,5}     2   0-1-2   62
        {1,2,3,5}   2   0-1-2   62
        Sum                    944
    The values 3 and 5 have 2 bits set, so they have 1 edge each. If a subset contains only a 3
    or 5, there will be one connected component with 2 nodes, and 62 components with 1 node for a
    total of 63.
    If both 3 and 5 are in a subset, 1 component with nodes 0,1 and 2 is formed since node  is one
    end of each edge described. The other 61 nodes are solitary, so there are 62 connected
    components total.
    All other values have only 1 bit set, so they have no edges. They have 64 components with 1
    node each.
Function Description
    Complete the findConnectedComponents function in the editor below.
    findConnectedComponents has the following parameters:
        * int d[n]: an array of integers
Returns
    int: the sum of the number of connected components for all subsets of d
Input Format
    The first row contains the integer n, the size of d[].
    The next row has n space-separated integers, d[i].
Constraints
    1<=n<=20
    0<=d[i]<=2^63 -1
Sample Input 1
    3
    2 5 9
Sample Output 1
    504
Explanation 1
    There are 8 subset of {2,5,9}.
    {}
        => We don't have any number in this subset => no edge in the graph => Every node is a
        component by itself => Number of connected-components = 64.
    {2}
        => The Binary Representation of 2 is 00000010. There is a bit at only one position. => So
        there is no edge in the graph, every node is a connected-component by itself => Number of
        connected-components = 64.
    {5}
        => The Binary Representation of 5 is 00000101. There is a bit at the 0th and 2nd
        position. => So there is an edge: (0, 2) in the graph => There is one component with a
        pair of nodes (0,2) in the graph. Apart from that, all remaining 62 vertices are
        indepenent components of one node each (1,3,4,5,6...63) => Number of
        connected-components = 63.
    {9}
        => The Binary Representation of 9 is 00001001. => There is a 1-bit at the 0th and 3rd
        position in this binary representation. => edge: (0, 3) in the graph => Number of
        components = 63
    {2, 5}
        => This will contain the edge (0, 2) in the graph which will form one component
        => Other nodes are all independent components
        => Number of connected-component = 63
    {2, 9}
        => This has edge (0,3) in the graph
        => Similar to examples above, this has 63 connected components
    {5, 9}
        => This has edges (0, 2) and (0, 3) in the graph
        => Similar to examples above, this has 62 connected components
    {2, 5, 9}
        => This has edges(0, 2) (0, 3) in the graph. All three vertices (0,2,3) make one
        component => Other 61 vertices are all independent components
        => Number of connected-components = 62
    S=64+64+63+63+63+63+62+62=504
"""
#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the findConnectedComponents function below.
def count_components(i, prev_components, cliques):
    ''' Back-tracking algorithm '''
    if i >= len(cliques):
        return len(prev_components)
    c = count_components(i+1, prev_components, cliques)
    # now add a clique
    new_comp = cliques[i]
    components = []
    for comp in prev_components:
        if comp & new_comp:
            new_comp |= comp
        else:
            components.append(comp)
    if new_comp:
        components.append(new_comp)
    c += count_components(i+1, components, cliques)
    return c

if __name__ == '__main__':
    n = int(input().strip())
    d = input().strip().split()
    d = [int(v) for v in d]
    assert len(d) == n

    singletons = [1<<j for j in range(64)]
    print(count_components(0, singletons, d))
