"""
Transforming data into some other data is typical of a programming job. This problem is about
a particular kind of transformation which we'll call the max transform.
Let A be a zero-indexed array of integers. For 0<=i<=j<length(A), let A_(i...j) denote the
subarray of A from index i to index j, inclusive.
Let's define the max transform of A as the array obtained by the following procedure:
    Let B be a list, initially empty.
    For k from 0 to length(A)-1:
        For i from 0 to length(A)-k-1:
            Let j=i+k.
            Append  max(A_(i...j))to the end of B.
    Return B.
The returned array is defined as the max transform of A. We denote it by S(A).
Complete the function solve that takes an integer array A as input.
Given an array A, find the sum of the elements of S(S(A)), i.e., the max transform of the max
transform of A. Since the answer may be very large, only find it modulo 10^9+7.
Input Format
    The first line of input contains a single integer n denoting the length of A.
    The second line contains n space-separated integers A_0,A-1,...,A_(n-1) denoting the
    elements of A.
Constraints
    1<=n<=2X10^5
    1<=A_i<=10^6
Subtasks
    For 33.33% of the total score, 1<=n<=4000
Output Format
    Print a single line containing a single integer denoting the answer.
Sample Input 0
    3
    3 2 1
Sample Output 0
    58
Explanation 0
    In the sample case, we have:
            A=[3,2,1]
          S(A)=[3,2,1,3,2,3]
        S(S(A))=[3,2,1,3,2,3,3,2,3,3,3,3,3,3,3,3,3,3,]
    Therefore, the sum of the elements of S(S(A)) is 58.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

# Complete the solve function below.

import math
import os
import random
import re
import sys
sys.setrecursionlimit(9999999)
from decimal import Decimal
def t1(n):
    return Decimal(n * (n + 1) / 2)


def t2(n):
    return Decimal(n * (n + 1) * (n + 2) / 6)


def u2(n):
    return Decimal(n * (n + 2) * (2 * n + 5) / 24)


def countzip(a, b):
    return u2(a + b) - u2(abs(a - b)) + t2(abs(a - b))


def countends(x, n, ex):
    return countzip(n, ex) - countzip(x, ex) - countzip(n - 1 - x, 0)


def countsplit(x, n):
    return t1(t1(n)) - t1(x) - countzip(n - x - 1, x - 1)


K = 20
lg = [0] * (1 << K)
for i in range(K):
    lg[1 << i] = i
for i in range(1, 1 << K):
    lg[i] = max(lg[i], lg[i - 1])


def make_rangemax(A):
    n = len(A)
    assert 1 << K > n

    key = lambda x: A[x]
    mxk = []
    mxk.append(range(n))
    for k in range(K - 1):
        mxk.append(list(mxk[-1]))
        for i in range(n - (1 << k)):
            mxk[k + 1][i] = max(
            mxk[k][i], mxk[k][i + (1 << k)],
             key=key)

    def rangemax(i, j):
        k = lg[j - i]
        return max(mxk[k][i], mxk[k][j - (1 << k)], key=key)

    return rangemax


def brutesolo(A):
    rangemax = make_rangemax(A)
    stack = [(0, len(A))]
    ans = 0
    while stack:
        i, j = stack.pop()
        if i != j:
            x = rangemax(i, j)
            stack.append((i, x))
            stack.append((x + 1, j))
            ans += A[x] * (x - i + 1) * (j - x)
    return ans


def make_brute(A):
    rangemax = make_rangemax(A)

    def brute(i, j):
        stack = [(i, j)]
        ans = 0
        while stack:
            i, j = stack.pop()
            if i != j:
                x = rangemax(i, j)
                stack.append((i, x))
                stack.append((x + 1, j))
                ans += A[x] * countends(x - i, j - i, 0)
        return ans

    return brute, rangemax


def ends(A, B):
    brutea, rangemaxa = make_brute(A)
    bruteb, rangemaxb = make_brute(B)

    stack = [(len(A), len(B))]
    ans = 0
    while stack:
        i, j = stack.pop()
        if i == 0:
            ans += bruteb(0, j)
        elif j == 0:
            ans += brutea(0, i)
        else:
            x = rangemaxa(0, i)
            y = rangemaxb(0, j)
            if A[x] < B[y]:
                ans += bruteb(y + 1, j)
                ans += B[y] * countends(y, j, i)
                stack.append((i, y))
            else:
                ans += brutea(x + 1, i)
                ans += A[x] * countends(x, i, j)
                stack.append((x, j))

    return ans


def maxpairs(a):
    return [max(x, y) for x, y in zip(a, a[1:])]


def solve(A):
    n = len(A)
    x = max(range(n), key=lambda x: A[x])
    return (int((brutesolo(A[:x]) +
    ends(A[x + 1:][::-1], maxpairs(A[:x])) +
    A[x] * countsplit(x, n))%(10**9+7)))



if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input())

    A = list(map(int, input().rstrip().split()))

    result = solve(A)

    fptr.write(str(result) + '\n')

    fptr.close()
