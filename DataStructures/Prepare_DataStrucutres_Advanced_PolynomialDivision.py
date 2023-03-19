"""
Consider a sequence, c0,c1,...,cn-1, and a polynomial of degree 1 defined as Q(x)=a*x+b. You
must perform q queries on the sequence, where each query is one of the following two types:
    * 1 i x: Replace ci with x.
    * 2 l r: Consider the polynomial P(x)=xl*x^0 +cl+1 *x^1 + ... + cr *x^r-1 and determine
    whether P(x) is divisible by Q(x)=a*x+b over the field Zp, where p=10^9 +7. In other words,
    check if there exists a polynomial R(x) with integer coefficients such that each
    coefficient of P(x)-R(x)*Q9x is divisible by p. If a valid R(x) exists, print Yes on a new
    line; otherwise, print No.
Given the values of n, a, b, and q queries, perform each query in order.
Input Format
    The first line contains four space-separated integers describing the respective values of
    n (the length of the sequence), a (a coefficient in Q(x)), b (a coefficient in Q(x)), and
    q (the number of queries).
    The second line contains n space-separated integers describing c0,c1,...,cn-1.
    Each of the q subsequent lines contains three space-separated integers describing a query
    of either type 1 or type 2.
Constraints
    1<=n,q<=10^5
    For query type 1: 0<=i<=n-1 and 0<=x<1-^9 +7.
    For query type 2: 0<=l<=r<=n-1.
    0<=a,b,ci<10^9 +7
    a!=0
Output Format
    For each query of type 2, print Yes on a new line if Q(x) is a divisor of P(x); otherwise,
    print No instead.
Sample Input 0
    3 2 2 3
    1 2 3
    2 0 2
    1 2 1
    2 0 2
Sample Output 0
    No
    Yes
Explanation 0
    Given Q(x)=2*x+2 and the initial sequence c={1,2,3}, we perform the following q=3 queries:
        1. Q(x)=2*x+2 is not a divisor of P(x)=1+2*x+3*x^2, so we print No on a new line.
        2. Set c2 to 1, so c={1,2,1}.
        3. After the second query, P(x)=1+2*x+1*x^2. Because (2*x+2)*(50000004*x+50000004)mod
        (10^9 +7)=1+2*x+1*x^2, we print Yes on a new line.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

# returns d, x, y so that gcd(a, b) = d and ax + by = d
def extended_euclidean_alg(a,b):
    # starts out as p[0] = P_{-1}, p[1] = P_0 and same for q
    # in general it's the previous 2 terms, P_{i-1}, P_{i-2}
    p = [0, 1]
    q = [1, 0]
    counter = 1
    while b != 0:
        quo = a//b
        rem = a % b
        newP = quo*p[1] + p[0]
        newQ = quo*q[1] + q[0]
        p[0] = p[1]
        p[1] = newP
        q[0] = q[1]
        q[1] = newQ
        a = b
        b = rem
        counter = (counter + 1) % 2
    minusOne = (counter-1) % 2
    return a, q[0]*((-1)**minusOne), p[0]*((-1)**(counter))

def leastSigBit(num):
    return (num & -num)

# implementation of a Fenwick tree
class PrefixSumTree(object):
    def __init__(self,array):
        l = len(array)
        self.sums = [0] * l
        for i in range(1,l):
            cl = i - leastSigBit(i)
            for j in range(cl+1,i+1):
                self.sums[i] = (self.sums[i] + array[j]) % p

    def sum(self,i):
        sum = 0
        while i > 0:
            sum = (sum + self.sums[i]) % p
            i -= leastSigBit(i)
        return sum

    # adds toAdd to the ith element of array
    def add(self,i,toAdd):
        while i <= len(self.sums)-1:
            self.sums[i] = (self.sums[i] + toAdd) % p
            i += leastSigBit(i)

p = 10**9 + 7

def polynomialDivision(a, b, c, queries):
    res = []
    a_inv = extended_euclidean_alg(p, a)[2]
    x = -b*a_inv % p
    # if x != 0 then we have to build the sum tree
    if x != 0:
        l = len(c)
        # polyArray[i+1] = c[i]*x^i % p and polyArray[0] = 0
        polyArray = [0] * (l+1)
        polyArray[1] = c[0]
        # powsOfX[i] = x^i % p
        powsOfX = [1] * l
        for i in range(1,l):
            newPow = (powsOfX[i-1]*x) % p
            powsOfX[i] = newPow
            polyArray[i+1] = (c[i]*newPow) % p
        sumTree = PrefixSumTree(polyArray)
    for q in queries:
        if q[0] == 1:
            # compute how much we need to add for the sum
            toAdd = q[2]-c[q[1]]
            # update the array c with our new entry q[2]
            c[q[1]] = q[2]
            if x != 0:
                # then we add the appropriate amount to our prefix sums.
                # since sumTree keeps track of sum c_i * x^i we multiply by the
                # appropriate power of x
                sumTree.add(q[1]+1,(toAdd*(powsOfX[q[1]])) % p)
        else:
            # remember c is zero indexed but sumTree is one indexed
            # so we do sum(q[2]+1) - sum(q[1]) instead of sum(q[2]) - sum(q[1]-1)
            pOfX = c[q[1]] if x == 0 else (sumTree.sum(q[2]+1) - sumTree.sum(q[1])) % p
            if pOfX == 0:
                res.append("Yes")
            else:
                res.append("No")
    return res


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nabq = input().split()

    n = int(nabq[0])

    a = int(nabq[1])

    b = int(nabq[2])

    q = int(nabq[3])

    c = [int(t) for t in input().rstrip().split()]

    queries = []

    for _ in range(q):
        queries.append([int(t) for t in input().rstrip().split()])

    result = polynomialDivision(a, b, c, queries)

    fptr.write('\n'.join(result))
    fptr.write('\n')

    fptr.close()
