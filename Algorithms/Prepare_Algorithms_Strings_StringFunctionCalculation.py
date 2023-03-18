"""
Jane loves strings more than anything. She has a string t with her, and value of string
over s function f can be calculated as given below:
    f(s)=|s| X Number Of Times s Occurs In t
Jane wants to know the maximum value of f(s) among all the substrings (s) of string t.
Can you help her?
Input Format
    A single line containing string  t.
Output Format
    Print the maximum value of f(s) among all the substrings (s) of string t.
Constraints
    1<=|t|<=10^5
    The string consists of lowercase English alphabets.
Sample Input 0
    aaaaaa
Sample Output 0
    12
Explanation 0
    f('a') = 6
    f('aa') = 10
    f('aaa') = 12
    f('aaaa') = 12
    f('aaaaa') = 10
    f('aaaaaa') = 6
Sample Input 1
    abcabcddd
Sample Output 1
    9
Explanation 1
    f values of few of the substrings are shown below:
        f("a") = 2
        f("b") = 2
        f("c") = 2
        f("ab") = 4
        f("bc") = 4
        f("ddd") = 3
        f("abc") = 6
        f("abcabcddd") = 9
    Among the function values 9 is the maximum one.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'maxValue' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING t as parameter.
#

def maxValue(t):
    n = len(t)
    sa = suffix_array(t, n)
    lcp = lcp_array(t, sa, n)
    ans = n
    left, right = [-1]*n, [n]*n
    s = [0]
    for i in range(1,n):
        while s and lcp[s[-1]] >= lcp[i]: s.pop()
        if s: left[i] = s[-1]
        s.append(i)
    s = [n-1]
    for i in range(n-2, -1, -1):
        while s and lcp[s[-1]] >= lcp[i]: s.pop()
        if s: right[i] = s[-1]
        s.append(i)
    for i in range(n):
        ans = max(ans, lcp[i]*(right[i]-left[i]))
    return ans


def suffix_array(s, n):
    sa, l = [[s[i],i] for i in range(n)], 0
    while l < 2*n:
        sa.sort(key=lambda x: x[0])
        last, rank, pos_map = sa[0][0], 0, [None]*n
        for i in range(n):
            pos_map[sa[i][1]] = i
            if last != sa[i][0]:
                last = sa[i][0]
                rank += 1
            sa[i][0] = rank
        new_tuple = [(sa[i][0], sa[pos_map[sa[i][1]+l]][0] if sa[i][1]+l < n else -1) for i in range(n)]
        for i in range(n):
            sa[i][0] = new_tuple[i]
        l = 1 if not l else l << 1
    return [i[1] for i in sa]


def lcp_array(s, sa, n):
    rank, k, lcp = [None]*n, 0, [0]*n
    for i in range(n):
        rank[sa[i]] = i
    for i in range(n):
        if rank[i] == n-1:
            k = 0
            continue
        j = sa[rank[i]+1]
        while i+k<n and j+k<n and s[i+k] == s[j+k]:
            k += 1
        lcp[rank[i]] = k
        k = max(0, k-1)
    return lcp

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = input()

    result = maxValue(t)

    fptr.write(str(result) + '\n')

    fptr.close()
