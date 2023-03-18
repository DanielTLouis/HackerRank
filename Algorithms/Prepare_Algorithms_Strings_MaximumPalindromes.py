"""
Madam Hannah Otto, the CEO of Reviver Corp., is fond of palindromes, or words that read
the same forwards or backwards. She thinks palindromic brand names are appealing to
millennials.
As part of the marketing campaign for the company's new juicer called the Rotator™,
Hannah decided to push the marketing team's palindrome-searching skills to a new level
with a new challenge.
In this challenge, Hannah provides a string s consisting of lowercase English letters.
Every day, for q days, she would select two integers l and r, take the substring sl...r
(the substring of s from index l to index r), and ask the following question:
Consider all the palindromes that can be constructed from some of the letters from
sl...r. You can reorder the letters as you need. Some of these palindromes have the
maximum length among all these palindromes. How many maximum-length palindromes are
there?
For example, if s=madamimadam, l=4 and r=7, then we have,
    image
Your job as the head of the marketing team is to answer all the queries. Since the
answers can be very large, you are only required to find the answer modulo* 10^9 + 7.
* https://en.wikipedia.org/wiki/Modulo_operation *
Complete the functions initialize and answerQuery and return the number of
maximum-length palindromes modulo 10^9 + 7.
Input Format
    The first line contains the string s.
    The second line contains a single integer q.
    The ith of the next q lines contains two space-separated integers l_i, r_i denoting
    the l and r values Anna selected on the ith day.
Constraints
    Here, |s| denotes the length of s.
    1<=|s|<=10^5
    1<=q<=10^5
    1<=l_i<=r_i<=|s|
Subtasks
    For 30% of the total score:
        1<=|s|<=100
        1<=q<=1000
        r_i -l<=3
    For 60% of the total score:
        1<=|s|<=100
        1<=q<=1000
Output Format
    For each query, print a single line containing a single integer denoting the answer.
Sample Input 0
    week
    2
    1 4
    2 3
Sample Output 0
    2
    1
Explanation 0
    On the first day, l=1 and r=4. The maximum-length palindromes are "ewe" and "eke".
    On the second day, l=2 and r=3. The maximum-length palindrome is "ee".
        image
Sample Input 1
    abab
    1
    1 4
Sample Output 1
    2
Explanation 1
    Here, the maximum-length palindromes are "abba" and "baab".
"""

#!/bin/python3

import math
import os
import random
import re
import sys

maximum = 26
#
# Complete the 'initialize' function below.
#
# The function accepts STRING s as parameter.
#
def initialize(s):
    # This function is called once before all queries.
    global arr, fac, mod, M
    M = 1000000007
    n = len(s)
    arr = [[0 for _ in range(n + 1)] for _ in range(maximum)]
    for i in range(n):
        for j in range(maximum):
            arr[j][i + 1] = arr[j][i] + ((ord(s[i]) - 97) == j)
    fac = [1] * (n + 1)
    mod = [1] * (n + 1)
    for i in range(1, n + 1):
        fac[i] = (fac[i - 1] * i) % M
        mod[i] = pow(fac[i], M - 2, M)
#
# Complete the 'answerQuery' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER l
#  2. INTEGER r
#
def answerQuery(l, r):
    # Return the answer for this query modulo 1000000007.
    global arr, fac, mod, M
    odd = 0
    even = 0
    divs = 1
    for i in range(maximum):
        value = arr[i][r] - arr[i][l - 1]
        odd += (value & 1)
        even += (value // 2)
        divs = (divs * mod[value//2]) % M
    result = (fac[even] * divs) % M
    if (odd > 0):
        result = (result * odd) % M
    return result

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    initialize(s)

    q = int(input().strip())

    for q_itr in range(q):
        first_multiple_input = input().rstrip().split()

        l = int(first_multiple_input[0])

        r = int(first_multiple_input[1])

        result = answerQuery(l, r)

        fptr.write(str(result) + '\n')

    fptr.close()
