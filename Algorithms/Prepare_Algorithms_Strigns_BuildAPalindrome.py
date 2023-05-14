"""
You have two strings, a and b. Find a string, s, such that:
    * s can be expressed as s=s_a + a_b where s_a is a non-empty substring of a and s_b is a
    non-empty substring of b.
    * s is a palindromic string.
    * The length of s is as long as possible.
For each of the q pairs of strings (a_i and b_i) received as input, find and print string s_i
on a new line. If you're able to form more than one valid string s_i, print whichever one
comes first alphabetically. If there is no valid answer, print -1 instead.
Input Format
    The first line contains a single integer, q, denoting the number of queries. The
    subsequent lines describe each query over two lines:
        1. The first line contains a single string denoting a.
        2. The second line contains a single string denoting b.
Constraints
    1<=q<=10
    1<=|a|,|b|<=10^5
    a and b contain only lowercase English letters.
    Sum of |a| over all queries does not exceed 2X10^5
    Sum of |b| over all queries does not exceed 2X10^5
Output Format
    For each pair of strings (a_i and b_i), find some s_i satisfying the conditions above and
    print it on a new line. If there is no such string, print -1 instead.
Sample Input
    3
    bac
    bac
    abc
    def
    jdfh
    fds
Sample Output
    aba
    -1
    dfhfd
Explanation
    We perform the following three queries:
        1.Concatenate s_a = "a" with s_b = "ba" to create .
        We're given a="abc and s_a = "def"; because both strings are composed of unique
        characters, we cannot use them to form a palindromic string. Thus, we print -1.
        Concatenate s_a="dfh" with s_b="fd" to create s="dfhfd". Note that we chose these
        particular substrings because the length of string s must be maximal.
"""

#!/bin/python3

import math
import os
import random
import re
import sys
def build_palindrome_lookup(s):
    sx = '|' + '|'.join(s) + '|'
    sxlen = len(sx)
    rslt = [0] * sxlen
    c, r, m, n = 0, 0, 0, 0
    for i in range(1, sxlen):
        if i > r:
            rslt[i] = 0
            m = i - 1
            n = i + 1
        else:
            i2 = c * 2 - i
            if rslt[i2] < r - i:
                rslt[i] = rslt[i2]
                m = -1
            else:
                rslt[i] = r - i
                n = r + 1
                m = i * 2 - n
        while m >= 0 and n < sxlen and sx[m] == sx[n]:
            rslt[i] += 1
            m -= 1
            n += 1
        if i + rslt[i] > r:
            r = i + rslt[i]
            c = i
    res = [0] * len(s)
    for i in range(1, sxlen - 1):
        idx = (i - rslt[i]) // 2
        res[idx] = max(res[idx], rslt[i])
    return res

class state:
    def __init__(self):
        self.link = -1
        self.length = 0
        self.childs = {}

def build_part_st(a, st, num, last, sz):
    for c in a:
        cur = sz
        sz += 1
        st[cur].length = st[last].length + 1
        p = last
        while p != -1 and c not in st[p].childs:
            st[p].childs[c] = cur
            p = st[p].link
        if p == -1:
            st[cur].link = 0
        else:
            q = st[p].childs[c]
            if st[p].length + 1 == st[q].length:
                st[cur].link = q
            else:
                clone = sz
                sz += 1
                st[clone].length = st[p].length + 1
                st[clone].childs = dict((x, y) for (x, y) in st[q].childs.items())
                st[clone].link = st[q].link
                while p != -1 and st[p].childs[c] == q:
                    st[p].childs[c] = clone
                    p = st[p].link
                st[q].link = clone
                st[cur].link = clone
        last = cur
    return last, sz

def print_st(st):
    i = 0
    for s in st:
        print('#{} link:{} childs:{}'.format(i, s.link, s.childs))
        i += 1

def solve(a, b):
    n = len(a)
    blen = len(b)
    st = [state() for x in range(2 * n)]
    st[0].link = -1
    st[0].length = 0
    last = 0
    sz = 1
    last, sz = build_part_st(a, st, 1, last, sz)
    plookup = build_palindrome_lookup(b)
    apos, start, left, mid, total, curlen = 0, -1, 0, 0, 0, 0
    for i in range(blen):
        c = b[i]
        if c not in st[apos].childs:
            while apos!=-1 and c not in st[apos].childs:
                apos = st[apos].link
            if apos == -1:
                apos = 0
                curlen=0
                continue
            curlen = st[apos].length
        curlen += 1
        apos = st[apos].childs[c]
        new_start = i - curlen + 1
        new_mid = 0
        if i + 1 < blen:
           new_mid = plookup[i + 1]
        new_total = 2 * curlen + new_mid
        if total < new_total or (total == new_total and lex_gt(b,start, new_start,curlen + mid)):
            left = curlen
            mid = new_mid
            total = new_total
            start = new_start
    palindrome = []
    for i in range(left + mid):
        palindrome.append(b[start + i])
    for i in range(left - 1, -1, -1):
        palindrome.append(palindrome[i])
    return ''.join(palindrome)

def lex_gt(s, old_start, new_start, size):
    for i in range(size):
        if s[old_start + i] != s[new_start + i]:
            if s[old_start + i] > s[new_start + i]:# old lex greater so pick new one
                return True
            break
    return False

def suffix_automata(a,b):
    rb = b[::-1] # reverse b
    rslt1 = solve(a, rb)
    rslt2 = solve(rb, a)
    rslt = None
    if len(rslt1) > len(rslt2):
        rslt = rslt1
    elif len(rslt1) < len(rslt2):
        rslt = rslt2
    else:
        rslt= rslt1 if rslt1 < rslt2 else rslt2
    if len(rslt) == 0:
        return '-1'
    return rslt

def process_helper(a,b):
    return suffix_automata(a,b)

for _ in range(int(input())):
    a = input()
    b = input()
    print(process_helper(a,b))
"""
#
# Complete the 'buildPalindrome' function below.
#
# The function is expected to return a STRING.
# The function accepts following parameters:
#  1. STRING a
#  2. STRING b
#

def buildPalindrome(a, b):
    # Write your code here
    lena = len(a)
    lenb = len(b)
    wasPal =False
    while(lena > 0 and lenb > 0):
        pal = a + b
        wasPal = True
        for i in range(0, len(pal)):
            if(pal[i] != pal[len(pal)-1-i]):
                wasPal = False
                break
        if(wasPal):
            return pal
        else:
            if(a[0] != b[len(b)-1] and lena > lenb):
                a = a[1:]
                lena -= 1
            elif(a[0] != b[len(b)-1]):
                b = b[:len(b)-1]
                lenb -= 1
            elif(a[len(a)-1] != b[0]):
                a = a[:len(a)-1]
                lena -= 1
            else:
                b = b[1:]
                lenb -= 1
        print(a,b)
    return "-1"

    if(a[0] == b[len(b)-1]):
        pal = " ".join([a,b])
        print(pal)
        for i in range(0,len(pal)):
            if(a[i] != b[len(b)-1-i]):
                return -1
        return pal
    elif(a[len(a)-1] == b[0]):
        pal = " ".join([b,a])
        print(pal)
        for i in range(0,len(pal)):
            if(a[i] != b[len(b)-1-i]):
                return -1
        return pal
    else:
        return "-1"


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        a = input()

        b = input()

        result = buildPalindrome(a, b)

        fptr.write(result + '\n')

    fptr.close()
"""
