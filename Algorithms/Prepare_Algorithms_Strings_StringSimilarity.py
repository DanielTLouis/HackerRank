"""
For two strings A and B, we define the similarity of the strings to be the length of the
longest prefix common to both strings. For example, the similarity of strings "abc" and "abd"
is 2, while the similarity of strings "aaa" and "aaab" is 3.
Calculate the sum of similarities of a string S with each of it's suffixes.
Input Format
    The first line contains the number of test cases t.
    Each of the next t lines contains a string to process, s.
Constraints
    1<=t<=10
    1<=|s|<=100000
    s is composed of characters in the range ascii[a-z]
Output Format
    Output t lines, each containing the answer for the corresponding test case.
Sample Input
    2
    ababaa
    aa
Sample Output
    11
    3
Explanation
    For the first case, the suffixes of the string are "ababaa", "babaa", "abaa", "baa", "aa"
    and "a". The similarities of these strings with the string "ababaa" are 6,0,3,0,1, & 1
    respectively. Thus, the answer is 6 + 0 + 3 + 0 + 1 + 1 = 11.
    For the second case, the answer is 2 + 1 = 3.
"""

#!/bin/python3

import sys

def stringSimilarity(s):
    # Complete this function
    result = length = len(s)
    right = 0
    left = 0
    z = [length]

    for i in range(1, length):
        z.append(0)
        if i <= right:
            z[i] = min(right - i + 1, z[i - left])
        while i + z[i] < length and s[z[i]] == s[i + z[i]]:
            z[i] += 1
        if i + z[i] - 1 > right:
            left = i
            right = i + z[i] - 1

        result += z[i]

    return result

if __name__ == "__main__":
    t = int(input().strip())
    for a0 in range(t):
        s = input().strip()
        result = stringSimilarity(s)
        print(result)
