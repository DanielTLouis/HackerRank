"""
There is a string, , of lowercase English letters that is
repeated infinitely many times. Given an integer, n, find and
print the number of letter a's in the first n letters of the
infinite string.
Example
    s='abcac'
    n=10
    The substring we consider is abcacabcacabcac, the first 10
    characters of the infinite string. There are 4 occurrences
    of a in the substring.
Function Description
    Complete the repeatedString function in the editor below.
    repeatedString has the following parameter(s):
        s: a string to repeat
        n: the number of characters to consider
Returns
    int: the frequency of a in the substring
Input Format
    The first line contains a single string, s.
    The second line contains an integer, n.
Constraints
    1<=|s|<=100
    1<=n<=10^12
    For 25% of the test cases, n<=10^6.
Sample Input
Sample Input 0
    aba
    10
Sample Output 0
    7
Explanation 0
    The first n=10 letters of the infinite string are
    abaabaabaa. Because there are 7 a's, we return 7.
Sample Input 1
    a
    1000000000000
Sample Output 1
    1000000000000
Explanation 1
    Because all of the first n = 1000000000000 letters of the
    infinite string are a, we return 1000000000000.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'repeatedString' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts following parameters:
#  1. STRING s
#  2. LONG_INTEGER n
#

def repeatedString(s, n):
    # Write your code here
    if s == "a":
        return n
    else:
        return (n // len(s))*s.count("a")  + s[:n%len(s)].count('a')

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    n = int(input().strip())

    result = repeatedString(s, n)

    fptr.write(str(result) + '\n')

    fptr.close()
