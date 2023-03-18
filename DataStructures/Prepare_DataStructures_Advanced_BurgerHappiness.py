"""
In Burger Town new burger restaurants will be opened! Concretely,N  restaurants will
open in N days, while restaurant i will be opened on day i and will be located at X_i.
The town should be imagined as an one dimensional line in which every object's location
can be described by the x coordinate.
Tim has just recently arrived the town after a very bad result in a programming contest.
Thus he wants to cheer himself up by starting a trip to try out some new burgers.
Every burger restaurant  is associated with two integers A_i and B_i. If Tim eats a
burger from , then his happiness will increase by A_i, which can also be negative,
depending on the deliciousness of the burger. On the other hand, if Tim looks through
the window of an opened restaurant i, from which he will not eat a burger, then his
happiness decreases by B_i, since Tim gets sad by only seeing the burgers.
Tim's journey can start from any day d at the burger restaurant d and eats a burger from
there. On each subsequent day n>d, Tim has the following options:
    -Stay at the previous restaurant p.
    -Or go to the new restaurant n to eat a burger from there.
If he decides for the latter option, then on the path from p to n he will look through
all the windows that are on his path and maybe lose some happiness. Concretely, if
X_p<X_n, then he will look through the window of every opened restaurant i, having
X_p<=X_i<X_n. Similar for the case X_n<X_p.
Since Tim is a very good friend of yours you should help him finding a trip that will
maximize his happiness. If he should stay at home since no trip would cheer him up, then
print 0.
Note: Tim's happiness is 0 at the beginning of the trip and is allowed to be negative
throughout the time.
Input Format
    N will be given on the first line, then N lines will follow, describing the
    restaurants numbered from 1 to N accordingly. Restaurant i will be described by X_i,
    A_i and B_i separated by a single space.
Output Format
    Output the maximium happiness on one line.
Constraints
    1<=N<=10^5
    |A_i|<=10^6
    0<=B_i<=10^6
    0<=X_i<=10^9 and no two restaurants will have the same X coordinates.
Sample Input
    3
    2 -5 1
    1 5 1
    3 5 1
Sample Output
    8
Sample Input
    4
    4 10 0
    1 -5 0
    3 0 10
    2 10 0
Sample Output
    15
Sample Input
    3
    1 -1 0
    2 -2 0
    3 -3 0
Sample Output
    0
    First testcase: His trip starts on day 2 at restaurant 2 located at X_2 = 1. He
    gains A_2 = 5 happiness points there by eating a burger. On the next day he goes
    from restaurant 2 to 3, but will look through the window of restaurant 2 and 1.
    Therefore he loses B_2 = 1 and B_1 = 1 points on the way to restaurant 3. There he
    eats a burger and gains another A_3 = 5 points. In total his happiness is equal to
    5-1-1+5 = 8 and this is optimal.
    Second testcase: His trip starts on day 1 at restaurant 1. Then his actions on day
    2, 3 and 4 will be go to restaurant 2, stay at restaurant 2 and go to restaurant 4
    respectively. The happiness of this optimal trip is equal to 10-5+10 = 15.
    Third testcase: It's not worth to start the trip from any of the restaurant since he
    will only have negative happiness. That's why he should stay at home and 0 should be
    printed.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'solve' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY restaurants as parameter.
#
class SegmentTree(object):
    def __init__(self, seq=None, size=0):
        size = len(seq) if seq else size
        depth = int(math.ceil(math.log(size, 2)))
        if seq:
            lowest_lvl = 2 ** depth
            tree = [0] * (lowest_lvl - 1) + seq + [0] * (lowest_lvl - size)
            for d in range(depth - 1, -1, -1):
                for i in range(2 ** d - 1, 2 ** (d + 1) - 1):
                    tree[i] = max(tree[2 * i + 1], tree[2 * i + 2])
        else:
            tree = [0] * (2 ** (depth + 1) - 1)
        self.__tree = tree
        self.__pending = [0] * (2 ** depth - 1)

    def __str__(self):
        return str(self.__tree) + ',' + str(self.__pending)

    def query_point(self, index):
        index += len(self.__tree) // 2
        res = self.__tree[index]
        while index:
            index = (index - 1) // 2
            res += self.__pending[index]
        return res

    def query_left(self, index):
        index += len(self.__tree) // 2
        # Find first node that is not a right child
        while index and index % 2 == 0:
            index = (index - 1) // 2
        res = self.__tree[index]
        # Add pending updates to the result, if node is right child check
        # left as well
        while index:
            if index % 2 == 0:
                res = max(res, self.__tree[index - 1])
            index = (index - 1) // 2
            res += self.__pending[index]
        return res

    def query_right(self, index):
        index += len(self.__tree) // 2
        # Find first node that is not a left child
        while index % 2:
            index = (index - 1) // 2
        res = self.__tree[index]
        # Add pending updates to the result, if node is left child check
        # left as well
        while index:
            if index % 2:
                res = max(res, self.__tree[index + 1])
            index = (index - 1) // 2
            res += self.__pending[index]
        return res

    def update_point(self, index, diff):
        index += len(self.__tree) // 2
        val = self.__tree[index] + diff
        self.__tree[index] = val
        while index:
            index = (index - 1) // 2
            val += self.__pending[index]
            if val <= self.__tree[index]:
                break
            self.__tree[index] = val

    def update_left(self, index, diff):
        index += len(self.__tree) // 2
        # Handle sequence of right children and first left child
        if index and index % 2 == 0:
            while index and index % 2 == 0:
                index = (index - 1) // 2
            self.__pending[index] += diff
            self.__tree[index] += diff
        else:
            self.__tree[index] += diff
        # Here index points to either root or left child and
        # current node is updated
        # Update tree values all the way to the top
        while index:
            # If this is a right child then update the left child
            if index % 2 == 0:
                self.__pending[index - 1] += diff
                self.__tree[index - 1] += diff
            # Moved up the tree
            index = (index - 1) // 2
            # Update this node
            val = max(self.__tree[index * 2 + 1], self.__tree[index * 2 + 2])
            val += self.__pending[index]
            self.__tree[index] = val

    def update_right(self, index, diff):
        index += len(self.__tree) // 2
        # Handle sequence of left children and first right child
        if index % 2:
            while index % 2:
                index = (index - 1) // 2
            self.__pending[index] += diff
            self.__tree[index] += diff
        else:
            self.__tree[index] += diff
        # Here index points to either root or right child and
        # current node is updated
        # Update tree values all the way to the top
        while index:
            # If this is a left child then update the right child
            if index % 2:
                self.__pending[index + 1] += diff
                self.__tree[index + 1] += diff
            # Moved up the tree
            index = (index - 1) // 2
            # Update this node
            val = max(self.__tree[index * 2 + 1], self.__tree[index * 2 + 2])
            val += self.__pending[index]
            self.__tree[index] = val

def solve(restaurants):
    # Write your code here
    coords = {x: i for i, x in enumerate(sorted(map(lambda x: x[0], restaurants)))}
    ascending = SegmentTree(size = n)
    descending = SegmentTree(size = n)
    res = 0
    for x, a, b in restaurants:
        pos = coords[x]
        val = a
        if pos > 0:
            l = ascending.query_left(pos - 1)
            cur = ascending.query_point(pos)
            val = max(val, a + l - cur)
        if pos < n - 1:
            r = descending.query_right(pos + 1)
            cur = descending.query_point(pos)
            val = max(val, a + r - cur)
        res = max(res, val)
        ascending.update_point(pos, val)
        descending.update_point(pos, val)
        if b:
            ascending.update_left(pos, -b)
            descending.update_right(pos, -b)
    return res
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    restaurants = []

    for _ in range(n):
        restaurants.append(list(map(int, input().rstrip().split())))

    result = solve(restaurants)

    fptr.write(str(result) + '\n')

    fptr.close()
