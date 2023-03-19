"""
Natural numbers from 1 to N have been placed in an increasing order over some helix ( a
circular structure ). When the helix starts rotating, it is easy to find out
    1. The position of a given number
    2. The number located at a given position.
The helix has numbers arranged in the following fashion:
[1, 2, 3, ..., N]
Due to some malfunction, the helix has started rotating in a weird manner. Right now, every
possible contiguous interval can be rotated, and hence, locating a particular number or
identifying the number at a given position is almost impossible. For example, if at some
particular instant, the integer list is like this:
[1, 2, 3, 4, 5, ..., N]
rotating the interval [5...N] will leave the list like this:
[1, 2, 3, 4, N, N - 1, N - 2, ..., 5]
We need a software to handle this. Can you help us?
Input Format
    The first line of the input consists of two space separated integers, N, Q. N signifies
    that initially our list contains numbers from 1 to N, placed in an increasing order. Q
    lines follow and contain input in one of the following formats:
        1 A B
    indicating that the helix rotated circularly in the interval [A..B] ( both inclusive);
        2 A
    indicating that we are interested in knowing the current position of the number A
        3 A
    indicating that we are interested in knowing the number at position A.
Output Format
    For each line in the input of the form 2 A
    output a line saying
        element A is at position x
    where A is the number we are interested in and x is its current position.
    For each line of the form 3 A
    output a line saying
        element at position A is x
    where A is the position we are interested in and x is the integer located at this position.
Constraints
    1 ≤ N, Q ≤ 105
    positions are 1-indexed.
Sample Input
    5 10
    1 1 3
    2 3
    3 3
    1 3 5
    1 2 4
    3 1
    3 5
    2 4
    1 5 5
    2 2
Sample Output
    element 3 is at position 1
    element at position 3 is 1
    element at position 1 is 3
    element at position 5 is 1
    element 4 is at position 2
    element 2 is at position 4
Explanation
    Initially elements are placed like this:
        [1, 2, 3, 4, 5]
    after the first rotation, they are placed like this:
        [3, 2, 1, 4, 5]
    and that's how we get the first 2 results (first 2 lines in the output). After second
    rotation, they are placed like this:
        [3, 2, 5, 4, 1]
    and third one does this:
        [3, 4, 5, 2, 1]
    In the last rotation (1 5 5), it's easy to see that output matches the initial positions
    of the elements. Last rotation doesn't change the positions of the elements.
"""
# Enter your code here. Read input from STDIN. Print output to STDOUT
def size(node):
    if node:
        return node.size
    return 0


class Node:

    def __init__(self, id=-1):
        self.id = id
        self.left =None
        self.right =None
        self.parent = None
        self.size = 1
        self.rev = False

    def release(self):
        if self.rev:
            self.rev = False
            self.left, self.right = self.right, self.left
            if self.left:
                self.left.rev ^= True
            if self.right:
                self.right.rev ^= True

    def update(self):
        self.size = 1 + size(self.left) + size(self.right)


def zig(p):
    q = p.parent
    r = q.parent
    q.left=p.right
    if q.left:
        q.left.parent = q
    p.right = q
    q.parent = p
    p.parent=r

    if p.parent:
        if r.left == q:
            r.left = p
        if r.right == q:
            r.right = p
    q.update()


def zag(p):
    q = p.parent
    r = q.parent
    q.right=p.left
    if q.right:
        q.right.parent = q
    p.left = q
    q.parent = p
    p.parent=r
    if p.parent:
        if r.left == q:
            r.left = p
        if r.right == q:
            r.right = p
    q.update()


def splay(root, p, b=None):
    p.release()
    while p.parent != b:
        q = p.parent

        if q.parent == b:
            q.release()
            p.release()
            if q.left == p:
                zig(p)
            else:
                zag(p)
        else:
            r = q.parent
            r.release()
            q.release()
            p.release()
            if r.left == q:
                if q.left == p:
                    zig(q)
                    zig(p)
                else:
                    zag(p)
                    zig(p)
            elif q.left == p:
                zig(p)
                zag(p)
            else:
                zag(q)
                zag(p)
    p.update()
    if b == None:
        root = p
    else:
        b.update()
    return root


def find(k, p):
    if not p or p.size < k:
        return None
    while k:
        p.release()
        if p.left and p.left.size >= k:
            p = p.left
        else:
            if p.left:
                k -= p.left.size
            k -= 1
            if k > 0:
                p = p.right
    return p


def build( a, b):

    global T

    if a > b:
        return None
    if a == b:
        prx = T[a]
        prx.left =None
        prx.right =None
        prx.parent = None

        return prx
    mid = (a + b)//2
    prx = T[mid]
    prx.parent = None

    prx.left = build( a, mid - 1)

    if prx.left:
        prx.left.parent = prx
    prx.right = build( mid + 1, b)
    if prx.right:
        prx.right.parent = prx
    prx.update()


    return prx


def reverse(root, a, b):
    if a == b:
        return
    lfx = a + 1
    rgx = b + 1
    prev = find(lfx - 1, root)
    nxt = find(rgx + 1, root)
    root=splay(root, prev)
    root=splay(root, nxt, prev)
    nxt.left.rev ^= True
    return root






n, q = map(int, input().split())

T = [None for i in range(n + 2)]
for i in range(n + 2):
    T[i] = Node(i)


root = build( 0, n + 1)

s = ''
for k in range(q):

    query = tuple(map(int, input().split()))
    t = query[0]

    if t == 1:
        i, j = query[1], query[2]
        root=reverse(root, i, j)

    elif t == 2:
        i = query[1]
        ptx = T[i]
        root = splay(root, ptx)
        s += 'element {} is at position {}\n'.format(i, size(ptx.left))

    else:
        i = query[1]
        ptx = find(i + 1,root)
        s += 'element at position {} is {}\n'.format(i, ptx.id)
print(s)
