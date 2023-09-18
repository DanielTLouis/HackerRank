"""
A substring is defined as a contiguous sequence of one or more characters in the string. More
information on substrings can be found here.
You are given n strings w[1], w[2], ......, w[n]. Let S[i] denote the set of all distinct
substrings of the string w[i]. Let S={S[1]US[2]U...S[n]}, that is, S is a set of strings that is
the union of all substrings in all sets S[1], S[2], ..... S[n]. There will be many queries. For
each query you will be given an integer 'k'. Your task is to find the kth element of the 1-indexed
lexicographically ordered set of substrings in the set S. If there is no element k, return INVALID.
For example, your strings are w=[abc,cde]. All of the substrings are S[1]={a,b,c,ab,bc,abc} and
S[2]={c,d,e,cd,de,cde}. Combine the two sets and sort them to get
S={a,ab,abc,b,bc,c,cd,cde,d,de,e}. So, for instance if k=1, we return 'a'. If k=5, we return 'bc'.
If k=20 though, there is not an S[20] so we return INVALID.
Function Description
    Complete the findStrings function in the editor below. It should return array of strings.
    findStrings has the following parameter(s):
        * w: an array of strings
        * queries: an array of integers
Input Format
    The first line contains an integer n, the number of strings in the array w.
    Each of the next n lines consists of a string w[i].
    The next line contains an integer q, the number of queries.
    Each of the next q lines consists of a single integer k.
Constraints
    1<=n<=50
    1<=|w[i]|<=2000
    1<=q<=500
    1<=k<=10^9
    Each character of w[i] isAnElementOf(ascii[a-z])
Output Format
    Return an array of q strings where the ith string is the answer to the ith query. If a k is
    invalid, return "INVALID" for that case.
Sample Input
    2
    aab
    aac
    3
    3
    8
    23
Sample Output
    aab
    c
    INVALID
Explanation
    For the sample test case, we have 2 strings "aab" and "aac".
    S1 = {"a", "aa", "aab", "ab", "b"} . These are the 5 unique substrings of "aab".
    S2 = {"a", "aa", "aac",  "ac", "c" } . These are the 5 unique substrings of "aac".
    Now, S = {S1 U S2} = {"a", "aa", "aab", "aac", "ab", "ac", "b", "c"}. Totally, 8 unique
    strings are present in the set S.
    The lexicographically 3rd smallest string in S is "aab" and the lexicographically 8th smallest
    string in S is "c". Since there are only 8 distinct substrings, the answer to the last query
    is "INVALID".
"""
from operator import attrgetter

def lcp(s, t):
    length = min(len(s), len(t))
    for i in range(length):
        if s[i] != t[i]:
            return i
    return length

class Suffix(object):
    def __init__(self, s):
        self.t = s
        self.start = 0
        self.c = -1

    def count(self, s):
        if s:
            self.start = lcp(self.t, s.t)
        self.c = len(self.t) - self.start

class SuffixArray(object):
    def __init__(self):
        self.suffixes = []

    def add(self, s):
        for i in range(len(s)):
            self.suffixes.append(Suffix(s[i:]))

    def select(self, i):
        for j in range(len(self.suffixes)):
            suffix = self.suffixes[j]
            if suffix.c == -1:
                if j == 0:
                    suffix.count(None)
                else:
                    suffix.count(self.suffixes[j - 1])
            if i <= suffix.c:
                return suffix.t[:suffix.start + i]
            else:
                i = i - suffix.c
        return 'INVALID'

def makeSuffixArray():
    sa = SuffixArray()
    n = int(input())
    for i in range(n):
        w = input()
        sa.add(w)
    sa.suffixes.sort(key = attrgetter('t'))
    return sa

def selectOutput():
    sa = makeSuffixArray()
    q = int(input())
    for i in range(q):
        k = int(input())
        print(sa.select(k))

selectOutput()
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'findStrings' function below.
#
# The function is expected to return a STRING_ARRAY.
# The function accepts following parameters:
#  1. STRING_ARRAY w
#  2. INTEGER_ARRAY queries
#
def findStrings(w, queries):
    # Write your code here
    sub1 = []
    sub2 = []
    for i in range(0, len(w[0])+1):
        for j in range(i+1, len(w[0])+1):
            sub1.append(w[0][i:j])
    sub1 = [*set(sub1)]

    for i in range(0, len(w[1])+1):
        for j in range(i+1, len(w[1])+1):
            sub2.append(w[1][i:j])
    sub2 = [*set(sub2)]

    oneUtwo = set(sub1).union(set(sub2))
    oneUtwo = list(oneUtwo)
    oneUtwo.sort()

    ans = []
    for i in queries:
        if(i > len(oneUtwo)):
            ans.append("INVALID")
        else:
            ans.append(oneUtwo[i-1])
    return ans

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    w_count = int(input().strip())

    w = []

    for _ in range(w_count):
        w_item = input()
        w.append(w_item)

    queries_count = int(input().strip())

    queries = []

    for _ in range(queries_count):
        queries_item = int(input().strip())
        queries.append(queries_item)

    result = findStrings(w, queries)

    fptr.write('\n'.join(result))
    fptr.write('\n')

    fptr.close()
"""
