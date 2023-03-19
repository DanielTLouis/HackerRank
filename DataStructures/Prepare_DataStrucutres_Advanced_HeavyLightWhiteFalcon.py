"""
Our lazy white falcon finally decided to learn heavy-light decomposition. Her teacher gave an
assignment for her to practice this new technique. Please help her by solving this problem.
You are given a tree with N nodes and each node's value is initially 0. The problem asks you
to operate the following two types of queries:
    * "1 u x" assign x to the value of the node u.
    * "2 u v" print the maximum value of the nodes on the unique path between u and v.
Input Format
    First line consists of two integers seperated by a space: N and Q.
    Following N-1 lines consisting of two integers denotes the undirectional edges of the
    tree.
    Following Q lines consist of the queries you are asked to operate.
Constraints
    1<=N,Q,x<=50000
    It is guaranteed that input denotes a connected tree with N nodes. Nodes are enumerated
    with 0-based indexing.
Output Format
    For each second type of query print single integer in a single line, denoting the asked
    maximum value.
Sample Input
    3 3
    0 1
    1 2
    1 0 1
    1 1 2
    2 0 2
Sample Output
    2
Explanation
After the first two updates value of the 0th node is 1 and 1st node is 2. That is why maxiumum value on the path between 0 and 2 is max(1,2)=2.
"""

def segtree_init(ary):
    ary = list(ary)
    seg = [ary]
    while len(ary) > 1:
        if len(ary) & 1: ary.append(0)
        ary = [max(ary[i], ary[i + 1]) for i in range(0, len(ary), 2)]
        seg.append(ary)
    return seg

def segtree_set(seg, i, x):
    ary = seg[0]
    ary[i] = x
    for j in range(1, len(seg)):
        x = max(ary[i], ary[i ^ 1])
        ary = seg[j]
        i >>= 1
        ary[i] = x

def segtree_max(seg, lo, hi):
    m = 0
    j = 0
    while lo < hi:
        ary = seg[j]
        if lo & 1:
            x = ary[lo]
            if x > m: m = x
            lo += 1
        if hi & 1:
            hi -= 1
            x = ary[hi]
            if x > m: m = x
        lo >>= 1
        hi >>= 1
        j += 1
    return m

class heavy_light_node:
    def __init__(self, segtree):
        self.parent = None
        self.pos = -1
        self.segtree = segtree

def build_tree(i, edges, location):
    children = []
    members = [i]
    ed = edges[i]
    while ed:
        for j in range(1, len(ed)):
            child = build_tree(ed[j], edges, location)
            child.pos = len(members) - 1
            children.append(child)
        i = ed[0]
        members.append(i)
        ed = edges[i]
    node = heavy_light_node(segtree_init(0 for j in members))
    for child in children:
        child.parent = node
    for j in range(len(members)):
        location[members[j]] = (node, j)
    return node

def read_tree(N):
    edges = [[] for i in range(N)]
    for i in range(N - 1):
        x, y = map(int, input().split())
        edges[x].append(y)
        edges[y].append(x)
    size = [0] * N
    active = [0]
    while active:
        i = active[-1]
        if size[i] == 0:
            size[i] = 1
            for j in edges[i]:
                edges[j].remove(i)
                active.append(j)
        else:
            active.pop()
            edges[i].sort(key = lambda j: -size[j])
            size[i] = 1 + sum(size[j] for j in edges[i])
    location = [None] * N
    build_tree(0, edges, location)
    return location

def root_path(i, location):
    loc = location[i]
    path = [loc]
    loc = loc[0]
    while loc.parent != None:
        path.append((loc.parent, loc.pos))
        loc = loc.parent
    path.reverse()
    return path

def max_weight(x, y):
    px = root_path(x, location)
    py = root_path(y, location)
    m = 1
    stop = min(len(px), len(py))
    while m < stop and px[m][0] == py[m][0]: m += 1
    loc, a = px[m - 1]
    b = py[m - 1][1]
    if a > b: a, b = b, a
    w = segtree_max(loc.segtree, a, b + 1)
    for j in range(m, len(px)):
        loc, i = px[j]
        x = segtree_max(loc.segtree, 0, i + 1)
        if x > w: w = x
    for j in range(m, len(py)):
        loc, i = py[j]
        x = segtree_max(loc.segtree, 0, i + 1)
        if x > w: w = x
    return w

N, Q = map(int, input().split())
location = read_tree(N)
for i in range(Q):
    t, x, y = map(int, input().split())
    if t == 1:
        loc, i = location[x]
        segtree_set(loc.segtree, i, y)
    elif t == 2:
        print(max_weight(x, y))
