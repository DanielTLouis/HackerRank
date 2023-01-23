"""
A string is said to be a child of a another string if it can be formed
by deleting 0 or more characters from the other string. Letters cannot
be rearranged. Given two strings of equal length, what's the longest
string that can be constructed such that it is a child of both?
Example
    s1='ABCD'
    s2='ABDC'
    These strings have two children with maximum length 3, ABC and
    ABD. They can be formed by eliminating either the D or C from both
    strings. Return 3.
Function Description
    Complete the commonChild function in the editor below.
    commonChild has the following parameter(s):
        string s1: a string
        string s2: another string
Returns
    int: the length of the longest string which is a common child of
    the input strings
Input Format
    There are two lines, each with a string, s1 and s2.
Constraints
    1<=|s1|,|s2|<=5000 where |s| means "the length of s"
    All characters are upper case in the range ascii[A-Z].
Sample Input
    HARRY
    SALLY
Sample Output
    2
Explanation
    The longest string that can be formed by deleting zero or more characters from HARRY and SALLY is AY, whose length is 2.
Sample Input 1
    AA
    BB
Sample Output 1
    0
Explanation 1
    AA and BB have no characters in common and hence the output is 0.
Sample Input 2
    SHINCHAN
    NOHARAAA
Sample Output 2
    3
Explanation 2
    The longest string that can be formed between SHINCHAN and
    NOHARAAA while maintaining the order is NHA.
Sample Input 3
    ABCDEF
    FBDAMN
Sample Output 3
    2
Explanation 3
    BD is the longest child of the given strings.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'commonChild' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. STRING s1
#  2. STRING s2
#

def commonChild(s1, s2):
    # Write your code here
    m = len(s1)
    n = len(s2)
    # 2D Array m*n
    counter = [[0] * (n + 1) for x in range(m + 1)]
    longest = 0

    for i in range(m):
        for j in range(n):
            if s1[i] == s2[j]:
                c = counter[i][j] + 1
                counter[i + 1][j + 1] = c
                if c > longest:
                    longest = c
            else:
                counter[i + 1][j + 1] = max(counter[i + 1][j], counter[i][j + 1])
    return longest
    """
    #need to do all cases not just one i.e. removing c then remove d to get
    ## 2 distinct strings
    ans = ''
    for i in s1:
        for j in s2:
            if(i == j):
                ans += i
                s1 = s1.replace(i,'',1)
                s2 = s2.replace(j,'',1)
                break
    return len(ans)
    """

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s1 = input()

    s2 = input()

    result = commonChild(s1, s2)

    fptr.write(str(result) + '\n')

    fptr.close()
