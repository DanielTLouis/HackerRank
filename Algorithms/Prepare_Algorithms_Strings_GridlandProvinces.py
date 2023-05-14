"""
The Kingdom of Gridland contains P provinces. Each province is defined as a 2XN grid where each
cell in the grid represents a city. Every cell in the grid contains a single lowercase
character denoting the first character of the city name corresponding to that cell.
From a city with the coordinates (i,j), it is possible to move to any of the following cells in
1 unit of time (provided that the destination cell is within the confines of the grid):
    * (i-1, j)
    * (i+1, j)
    * (i, j-1)
    * (i, j+1)
A knight wants to visit all the cities in Gridland. He can start his journey in any city and
immediately stops his journey after having visited each city at least once. Moreover, he always
plans his journey in such a way that the total time required to complete it is minimum.
After completing his tour of each province, the knight forms a string by concatenating the
characters of all the cells in his path. How many distinct strings can he form in each province?
Input Format
    The first line contains a single integer, P, denoting the number of provinces. The 3*P
    subsequent lines describe each province over the following three lines:
    The first line contains an integer, N, denoting the number of columns in the province.
    Each of the next two lines contains a string, S, of length N denoting the characters for
    the first and second row of the province.
Constraints
    1<=P<=15
    1<=N<=600
    Si IsAnElementOf({a-z})
Output Format
    For each province, print the number of distinct strings the knight can form on a new line.
Sample Input
    3
    1
    a
    a
    3
    dab
    abd
    5
    ababa
    babab
Sample Output
    1
    8
    2
Explanation
    Province 0:
        query 0
        The knight can only form one string (aa), so we print 1 on a new line.
    Province 1:
        query 1
        The knight can form eight different strings (abdbad, adabdb, badabd, bdbada,
        dababd, dabdba, dbabad, and dbadab), so we print 8 on a new line.
    Province 2:
        query 2
        The knight can form two different strings (ababababab and bababababa), so we print 2 on
        a new line.
"""

#!/bin/python3

import os
import sys

PRIME = 1000000007*65535

PMAP = [int((1<<(5*i)) % PRIME) for i in range(1202)]

def chash(s, p = 0):
    for c in s:
        p = ((p<<5) + ord(c)) % PRIME
    return p

def hmap(s):
    ret = [0]
    for c in s:
        ret.append(((ret[-1]<<5)+ord(c)) % PRIME)
    return ret

def hrange(l,i,j,s):
    return (l[j] + ((s-l[i]) * PMAP[j-i])) % PRIME

def count(s1 : str, s2 : str, s1rev, s2rev):
    ret = set()
    n,n2 = len(s1),2*len(s1)
    left_to_top = s2rev + s1
    left_to_bot = s1rev + s2
    right_from_top = s1 + s2rev
    right_from_bot = s2 + s1rev
    mid_even_tb = [ord(s1[i//2]) if ((i%4) in (0,3)) else ord(s2[i//2]) for i in range(n2)]
    mid_odd_tb = [ord(s2[i//2]) if ((i%4) in (0,3)) else ord(s1[i//2]) for i in range(n2)]
    left_to_top,left_to_bot,right_from_top,right_from_bot = map(hmap,(left_to_top,left_to_bot,right_from_top,right_from_bot))
    mid_even_tb = [mid_even_tb[2*j+1] + mid_even_tb[2*j] * PMAP[1] for j in range(n)]
    mid_odd_tb = [mid_odd_tb[2*j+1] + mid_odd_tb[2*j] * PMAP[1] for j in range(n)]
    for left,mids,rights in (left_to_top,(mid_even_tb,mid_odd_tb),(right_from_top,right_from_bot)),(left_to_bot,(mid_odd_tb,mid_even_tb),(right_from_bot,right_from_top)):
        for i in range(0,n+1):
            mid = mids[i&1]
            s = hrange(left,n-i,n+i,0)
            for j in range(i, n):
                ret.add(hrange(rights[j&1],j,n2-j,s))
                s = (s * PMAP[2] + mid[j]) % PRIME
            ret.add(s)
            rights = rights[::-1]
    return ret

def gridlandProvinces(s1, s2):
    s1rev,s2rev = s1[::-1],s2[::-1]
    return len(count(s1, s2, s1rev, s2rev).union(count(s1rev, s2rev, s1, s2)))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    p = int(input())

    for p_itr in range(p):
        n = int(input())

        s1 = input()

        s2 = input()

        result = gridlandProvinces(s1, s2)

        fptr.write(str(result) + '\n')

    fptr.close()
