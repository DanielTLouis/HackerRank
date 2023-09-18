"""
Given a tree T with n nodes, how many subtrees (T') of T have at most K edges connected to
(T - T')?
Input Format
    The first line contains two integers n and K followed by n-1 lines each containing two
    integers a & b denoting that there's an edge between a & b.
Constraints
    1 <= K <= n <= 50
    Every node is indicated by a distinct number from 1 to n.
Output Format
    A single integer which denotes the number of possible subtrees.
Sample Input
    3 1
    2 1
    2 3
Sample Output
    6
Explanation
    There are 2^3 possible sub-trees:
    {} {1} {2} {3} {1, 2} {1, 3} {2, 3} {1, 2, 3}
    But:
        the sub-trees {2} and {1,3} are not valid. {2} isn't valid because it has 2 edges
        connecting to it's complement {1,3} whereas K = 1 in the sample test-case {1,3} isn't
        valid because, well, it's not a sub-tree. The nodes aren't connected.
"""
line = input().split()
n = int(line[0])
K = int(line[1])

adjlst = [[1]]
for i in range(n):
    adjlst.append([])
adjlst[1].append(0)

for i in range(n - 1):
    line = input().split()
    x = int(line[0])
    y = int(line[1])
    adjlst[x].append(y)
    adjlst[y].append(x)

def dfs(node, par, adjlst, K):
    conlst = [0] * (K + 1)
    dislst = [0] * (K + 1)
    conlst[0] = 1
    for chld in adjlst[node]:
        if chld != par:
            tcl, tdl = dfs(chld, node, adjlst, K)
            # print(str(tcl))
            # print(str(tdl))
            dislst[0] += tdl[0]
            tcl2 = [0] * (K + 1)
            for i in range(K):
                dislst[i + 1] += tcl[i] + tdl[i + 1]
                tcl2[i + 1] += conlst[i]
            for i in range(K + 1):
                for j in range(K + 1):
                    if i + j <= K:
                        tcl2[i + j] += tcl[i] * conlst[j]
            conlst = list(tcl2)
    return conlst, dislst

conlst, dislst = dfs(1, 0, adjlst, K)
# print(str(conlst))
# print(str(dislst))
ans = sum(conlst) + sum(dislst) + 1
print(str(ans))
