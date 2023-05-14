"""
Ashton appeared for a job interview and is asked the following question. Arrange all the
distinct substrings* of a given string in lexicographical order and concatenate them. Print
the kth character of the concatenated string. It is assured that given value of k will be
valid i.e. there will be a kth character. Can you help Ashton out with this?
For example, given the string s=abc, its distinct substrings are
[a,ab,abc,abcd,b,bc,bcd,c,cd,d]. Sorted and concatenated, they make the string
aababcabcdbbcbcdccdd. If K=5 then, the answer is b, the 5th character of the 1-indexed
concatenated string.
* https://en.wikipedia.org/wiki/Substring *
Note We have distinct substrings here, i.e. if string is aa, it's distinct substrings are a
and aa.
Function Description
    Complete the ashtonString function in the editor below. It should return the kth character
    from the concatenated string, 1-based indexing.
    ashtonString has the following parameters:
        - s: a string
        - k: an integer
Input Format
    The first line will contain an integer t, the number of test cases.
    Each of the subsequent t pairs of lines is as follows:
        - The first line of each test case contains a string, s.
        - The second line contains an integer, k.
Constraints
    1<=t<=5
    1<=|s|<=10^5
    Each character of string s isAnElementOf(ascii[a-z])
    k will be an appropriate integer.
Output Format
    Print the kth character (1-based index) of the concatenation of the ordered distinct
    substrings of s.
Sample Input
    1
    dbac
    3
Sample Output
    c
Explanation
    The substrings when arranged in lexicographic order are as follows
        a, ac, b, ba, bac, c, d, db, dba, dbac
    On concatenating them, we get
        aacbbabaccddbdbadbac
    The third character in this string is c.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'ashtonString' function below.
#
# The function is expected to return a CHARACTER.
# The function accepts following parameters:
#  1. STRING s
#  2. INTEGER k
#
#
def ashtonString(s, k):
    # Write your code here.
    #
    kv = k - 1
    N = len(s)
    sr = [[0 for _ in range(N)] for __ in range(17)]
    sr[0] = [ord(c)-97 for c in s]

    L = [0]*N
    cnt = 1
    kf = lambda x: x[0]*(N+1) + x[1]
    for i in range(1, 17):
        for j in range(N):
            L[j] = (sr[i-1][j], sr[i-1][j+cnt] if j+cnt < N else -1, j)
        L.sort(key=kf)

        sr[i][L[0][2]] = 0
        cr = 0
        for j in range(1, N):
            if L[j-1][0] != L[j][0] or L[j-1][1] != L[j][1]:
                cr += 1
            sr[i][L[j][2]] = cr
        cnt *= 2
        if cnt >= N:
            break

    sa = [l[2] for l in L]
    rank = [0]*N
    lcp = [0]*N

    for i in range(N):
        rank[sa[i]] = i

    k = 0
    for i in range(N):
        if rank[i] == N-1:
            k = 0
            continue
        j = sa[rank[i] + 1]
        while j + k < N and i + k < N and s[i+k] == s[j+k]:
            k += 1
        lcp[rank[i]] = k
        if k > 0:
            k -= 1

    numprev = 0
    tri = lambda x: ((x+1)*x)>>1
    print(sa)
    print(lcp)
    for i in range(N):
        mylen = N - sa[i]
        tt = tri(mylen) - tri(numprev)
        if kv < tt:
            for j in range(1 + numprev, 1 + mylen):
                if kv < j:
                    return s[sa[i]+kv]
                kv -= j
        kv -= tt
        numprev = lcp[i]

    return ''
"""
def ashtonString(s, k):
    # Write your code here

    #Get all SubStrings
    subStrings = []
    for i in range(0, len(s)):
        for j in range(i+1, len(s)+1):
            tempString = s[i:j]
            if(len(tempString) > 0):
                subStrings.append(tempString)

    # Python3 code to demonstrate working of
    # Get all substrings of string
    # Using list comprehension + string slicing

    # Get all substrings of string
    # Using list comprehension + string slicing
    #substrigns = [s[i: j] for i in range(len(s))
           # for j in range(i + 1, len(s) + 1)]

    # sort & printing result
    subStrings.sort()

    #Concatanat string
    newString = ""
    for i in subStrings:
        newString += i

    index = k - 1
    for i in subStrings:
        if(len(i) > index):
            return i[index]
        else:
            index -= len(i)
    #return kth result
    #return char
"""

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        s = input()

        k = int(input().strip())

        res = ashtonString(s, k)

        fptr.write(str(res) + '\n')

    fptr.close()
