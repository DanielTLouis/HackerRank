"""
You can perform the following operations on the string, a:
    1. Capitalize zero or more of a's lowercase letters.
    2. Delete all of the remaining lowercase letters in a.
Given two strings, a and b, determine if it's possible to make a equal to b as described. If
so, print YES on a new line. Otherwise, print NO.
For example, given a=AbcDE and b=ABDE, in a we can convert b and delete c to match b. If
a=AbcDE and b=AFDE, matching is not possible because letters may only be capitalized or
discarded, not changed.
Function Description
    Complete the function abbreviation in the editor below. It must return either YES or NO.
    abbreviation has the following parameter(s):
        a: the string to modify
        b: the string to match
Input Format
    The first line contains a single integer q, the number of queries.
    Each of the next q pairs of lines is as follows:
        - The first line of each query contains a single string, a.
        - The second line of each query contains a single string, b.
Constraints
    1<=q<=10
    1<=|a|,|b|<=1000
    String a consists only of uppercase and lowercase English letters, ascii[A-Za-z].
    String b consists only of uppercase English letters, ascii[A-Z].
Output Format
    For each query, print YES on a new line if it's possible to make string a equal to
    string b. Otherwise, print NO.
Sample Input
    1
    daBcd
    ABC
Sample Output
    YES
Explanation
        image
    We have a= daBcd and b= ABC. We perform the following operation:
        1. Capitalize the letters a and c in a so that a = dABCd.
        2. Delete all the remaining lowercase letters in a so that a = ABC.
    Because we were able to successfully convert a to b, we print YES on a new line.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'abbreviation' function below.
#
# The function is expected to return a STRING.
# The function accepts following parameters:
#  1. STRING a
#  2. STRING b
#
"""
def abbreviation(a, b):
    # Write your code here
    for i in range(0,len(b)):
        for j in range(i,len(a)):
            print(b[i], a[j].upper())
            if(b[i] == a[j].upper()):
                a = a[0:j] + a[j].upper() + a[j+1:len(a)]
                break
    aModed = ""
    for i in range(0,len(a)):
        if(a[i].isupper()):
            aModed += a[i]
        print(":      ", aModed)
    if(aModed == b):
        return "YES"
    else:
        return "NO"
"""
def abbreviation(a, b):
    dp = [[False for _ in range(len(b)+1)] for _ in range(len(a)+1)]
    dp[0][0] = True
    for i in range(len(a)):
        for j in range(len(b)+1):
            if dp[i][j]:
                if j < len(b) and a[i].upper() == b[j]:
                    dp[i+1][j+1] = True
                if a[i].islower():
                    dp[i+1][j] = True
    return 'YES' if dp[len(a)][len(b)] else 'NO'
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        a = input()

        b = input()

        result = abbreviation(a, b)

        fptr.write(result + '\n')

    fptr.close()
