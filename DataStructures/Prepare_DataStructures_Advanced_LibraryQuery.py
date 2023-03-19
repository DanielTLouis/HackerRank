"""
A giant library has just been inaugurated this week. It can be modeled as a sequence of
N consecutive shelves with each shelf having some number of books. Now, being the geek
that you are, you thought of the following two queries which can be performed on these
shelves.
    -Change the number of books in one of the shelves.
    -Obtain the number of books on the shelf having the kth rank within the range of
    shelves.
A shelf is said to have the kth rank if its position is k when the shelves are sorted
based on the number of the books they contain, in ascending order.
Can you write a program to simulate the above queries?
Input Format
    The first line contains a single integer T, denoting the number of test cases.
    The first line of each test case contains an integer N denoting the number of
    shelves in the library.
    The next line contains N space separated integers where the ith integer represents
    the number of books on the ith shelf where 1<=i<=N.
    The next line contains an integer Q denoting the number of queries to be performed.
    Q lines follow with each line representing a query.
    Queries can be of two types:
        * 1 x k - Update the number of books in the xth shelf to k (1 <= x <= N).
        * 0 x y k - Find the number of books on the shelf between the shelves x and y
        (both inclusive) with the kth rank (1 <= x <= y <= N, 1 <= k <= y-x+1).
Output Format
    For every test case, output the results of the queries in a new line.
Constraints
    1 <= T <= 5
    1 <= N <= 104
    1 <= Q <= 104
    The number of books on each shelf is always guaranteed to be between 1 and 1000.
Sample Input
    2
    2
    1 2
    2
    0 1 2 1
    0 1 2 2
    4
    4 3 2 1
    4
    0 1 1 1
    1 1 1
    0 1 1 1
    0 1 4 3
Sample Output
    1
    2
    4
    1
    2
Explanation
    There are two test cases :
    1.The first test case contains only two shelves which can be represented as [1, 2].
    Two queries are to be processed :
        i) The first query asks for smallest number of books between the 1st and 2nd
        shevles which is 1.
        ii) The second query asks for the 2nd smallest number of books between the 1st
        and 2nd shevles which is 2.
    2.The second test case contains four shelves which can be represented as
    [4, 3, 2, 1]. Four queries are to be processed :
        i) The first query asks for the smallest number of books in the 1st shelf which
         is 4.
        ii) The second query updates the number of books in the 1st shelf to 1. Hence
        the shelves now look like [1, 3, 2, 1].
        iii) The third query asks for the smallest number of books in the 1st shelf
        which is now 1.
        iv) The last query asks for the 3rd smallest number of books between the 1st and
        4th shelves which is 2.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
# -*- coding: utf-8 -*-

class BinaryIndexedTree2D:
    '''1 based indexing'''

    def __init__(self,max_x=10000):
        self.x_max = 10000
        self.y_max = 1000
        self.tree = [[0 for i in range(self.y_max + 5)] for j in range(self.x_max + 5)]

    def update(self, x, y, val):
        while x <= self.x_max:
            y1 = y
            while y1 <= self.y_max:
                self.tree[x][y1] += val
                y1 += (y1 & -y1)
            x += (x & -x)

    def getFrequency(self, x, y):
        sum_ = 0
        while x > 0:
            y1 = y
            while y1 > 0:
                sum_ += self.tree[x][y1]
                y1 -= (y1 & -y1)
            x -= (x & -x)
        return sum_


def solve(t, l, r, k):
    low = 1
    high = t.y_max
    ans = -1
    while low <= high:
        mid = (low + high) // 2
        v2 = t.getFrequency(r, mid)
        v1 = t.getFrequency(l - 1, mid)
        if v2 - v1 >= k:
            ans = mid
            high = mid - 1
        else:
            low = mid + 1
    return ans


s = ''

for _ in range(int(input())):
    n = int(input())
    tree = BinaryIndexedTree2D(n)

    no_books=[0] +list(map(int, input().split()))
    for i in range(1, n+1):
        tree.update(i, no_books[i], 1)

    q = int(input())
    for i in range(q):
        query = list(map(int, input().split()))
        t = query[0]
        if t == 0:
            x, y, k = query[1:]
            res = solve(tree, x, y, k)
            s += str(res) + '\n'
        else:
            x, k = query[1:]
            tree.update(x, no_books[x], -1)
            no_books[x] = k
            tree.update(x, no_books[x], 1)


print(s)
