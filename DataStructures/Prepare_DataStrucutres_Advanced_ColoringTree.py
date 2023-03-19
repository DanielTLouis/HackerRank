"""
You are given a tree with N nodes with every node being colored. A color is represented by an
integer ranging from 1 to 109. Can you find the number of distinct colors available in a
subtree rooted at the node s?
Input Format
    The first line contains three space separated integers representing the number of nodes in
    the tree (N), number of queries to answer (M) and the root of the tree.
    In each of the next N-1 lines, there are two space separated integers(a b) representing an
    edge from node a to Node b and vice-versa.
    N lines follow: N+ith line contains the color of the ith node.
    M lines follow: Each line containg a single integer s.
Output Format
    Output exactly M lines, each line containing the output of the ith query.
Constraints
    0 <= M <= 105
    1 <= N <= 105
    1 <= root <= N
    1 <= color of the Node <= 109
Example
Sample Input
    4 2 1
    1 2
    2 4
    2 3
    10
    20
    20
    30
    1
    2
Sample Output
    3
    2
Explanation
    Query 1-Subtree rooted at 1 is the entire tree and colors used are 10 20 20 30 , so the
    answer is 3(10,20 and 30)
    Query 2-Subtree rooted at 2 contains color 20 20 30, so the answer is 2(20 and 30)
"""
from collections import Counter

n, m, root = map(int, input().split())
uniquenum = dict()
multipleset = dict()
adj = dict()
for _ in range(n - 1):
    n1, n2 = map(int, input().split())
    if n1 in adj:
        adj[n1].add(n2)
    else:
        adj[n1] = set([n2])
    if n2 in adj:
        adj[n2].add(n1)
    else:
        adj[n2] = set([n1])
colors = [int(input()) for _ in range(n)]
multiples = set(Counter(colors) - Counter(set(colors)))
colors.insert(0, 0)
totalcolors = len(set(colors[1:]))
stack = [root]
added = set([root])
visited = set()
while len(stack) > 0:
    node = stack[len(stack) - 1]
    if node not in visited:
        visited.add(node)
        for child in adj[node] - added:
            stack.append(child)
            added.add(child)
    else:
        if colors[node] in multiples:
            uniquenum[node] = 0
            multipleset[node] = set([colors[node]])
        else:
            uniquenum[node] = 1
            multipleset[node] = set()
        for child in adj[node] - added:
            uniquenum[node] += uniquenum[child]
            multipleset[node] |= multipleset[child]
        stack.pop()
        added.remove(node)
for _ in range(m):
    node = int(input())
    print(uniquenum[node] + len(multipleset[node]))
