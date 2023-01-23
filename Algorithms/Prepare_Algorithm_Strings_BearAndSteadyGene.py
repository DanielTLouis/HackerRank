"""
A gene is represented as a string of length n (where n is divisible by 4), composed of
the letters A, C, T, and G. It is considered to be steady if each of the four letters
occurs exactly n/4 times. For example, GACT and AAGTGCCT are both steady genes.
Bear Limak is a famous biotechnology scientist who specializes in modifying bear DNA to
make it steady. Right now, he is examining a gene represented as a string gene. It is
not necessarily steady. Fortunately, Limak can choose one (maybe empty) substring of
gene and replace it with any string of the same length.
Modifying a large substring of bear genes can be dangerous. Given a string gene, can you
help Limak find the length of the smallest possible substring that he can replace to
make gene a steady gene?
Note: A substring of a string s is a subsequence made up of zero or more contiguous
characters of s.
As an example, consider gene=ACTGAAAG. The substring AA just before or after G can be
replaced with CT or TC. One selection would create ATCGACTG.
Function Description
    Complete the steadyGene function in the editor below. It should return an integer
    that represents the length of the smallest substring to replace.
    steadyGene has the following parameter:
        gene: a string
Input Format
    The first line contains an interger n divisible by 4, that denotes the length of a
    string gene.
    The second line contains a string gene of length n.
Constraints
    4<=n<=500000
    n is divisible by 4
    gene[i] isAnElementOf([CGAT])
Subtask
    4<=n<=2000 in tests worth 30% points.
Output Format
    Print the length of the minimum length substring that can be replaced to make gene
    stable.
Sample Input
    8
    GAAATAAA
Sample Output
    5
Explanation
    One optimal solution is to replace AAATA with TTCCG resulting in GTTCCGAA.
    The replaced substring has length 5.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'steadyGene' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING gene as parameter.
#

if sys.version_info[:2] >= (3,10): # Counter supports comparision
    from collections import Counter
else:  # add operator ">=" to class Counter
    from collections import Counter as Counter_orig
    class Counter(Counter_orig):
        def __ge__(self,other):
            return all(self[k]>=other[k] for k in other.keys())

def steadyGene(gene):
    baddies = Counter(
        {k:v-len(gene)//4 for k,v in Counter(gene).items()
                if v > len(gene)//4} )
    if not baddies: return 0
    genecount_win,cur_winsize,min_winsize = Counter(),0,len(gene)
    left_it = iter(gene)
    cl = next(left_it) # cl: char at window's left margin
    for cr in gene:
        cur_winsize += 1
        genecount_win[cr] += 1
        if cr not in baddies: continue
        while cl not in baddies or genecount_win[cl] > baddies[cl]:
            cur_winsize -= 1
            genecount_win[cl] -=1
            cl = next(left_it)
        if genecount_win >= baddies and cur_winsize < min_winsize:
            min_winsize = cur_winsize
    return min_winsize

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    gene = input()

    result = steadyGene(gene)

    fptr.write(str(result) + '\n')

    fptr.close()
