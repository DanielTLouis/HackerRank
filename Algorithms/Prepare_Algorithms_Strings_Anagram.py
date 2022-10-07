"""
Two words are anagrams of one another if their letters can be
rearranged to form the other word.
Given a string, split it into two contiguous substrings of
equal length. Determine the minimum number of characters to
change to make the two substrings into anagrams of one another.
Example
    s=abccde
    Break s into two parts: 'abc' and 'cde'. Note that all
    letters have been used, the substrings are contiguous and
    their lengths are equal. Now you can change 'a' and 'b' in
    the first substring to 'd' and 'e' to have 'dec' and 'cde'
    which are anagrams. Two changes were necessary.
Function Description
    Complete the anagram function in the editor below.
    anagram has the following parameter(s):
        string s: a string
Returns
    int: the minimum number of characters to change or -1.
Input Format
    The first line will contain an integer, q, the number of
    test cases.
    Each test case will contain a string s.
Constraints
    1<=q<=100
    1<=|s|<010^4
    s consists only of characters in the range ascii[a-z].
Sample Input
    6
    aaabbb
    ab
    abc
    mnop
    xyyx
    xaxbbbxx
Sample Output
    3
    1
    -1
    2
    0
    1
Explanation
    Test Case #01: We split  into two strings ='aaa' and
    ='bbb'. We have to replace all three characters from the
    first string with 'b' to make the strings anagrams.
    Test Case #02: You have to replace 'a' with 'b', which
    will generate "bb".
    Test Case #03: It is not possible for two strings of
    unequal length to be anagrams of one another.
    Test Case #04: We have to replace both the characters of
    first string ("mn") to make it an anagram of the other
    one.
    Test Case #05: S1 and S2 are already anagrams of one
    another.
    Test Case #06: Here S1 = "xaxb" and S2 = "bbxx". You must
    replace 'a' from S1 with 'b' so that S1 = "xbxb".
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'anagram' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#

def anagram(s):
    # Write your code here
    if len(s) % 2: return -1

    from collections import Counter
    d1 = Counter(s[:len(s)//2])
    d2 = Counter(s[len(s)//2:])
    return sum( (d1-d2).values())
    """
    #way to slow
    if(len(s)%2==0):
        s1 = s[:len(s)//2]
        s2 = s[len(s)//2:]
    else:
        return -1
    print(s, s1, s2)
    s1 = "".join(sorted(s1))
    s2 = "".join(sorted(s2))
    dif = 0
    repeat = True
    while(repeat):
        repeat = False
        for i in range(0,len(s1)):
            for j in range(0,len(s2)):
                if(s1[i]==s2[j]):
                    #delete them
                    s1.replace(s1[i],"",1)
                    s2.replace(s2[j],"",1)
                    repeat = True
                    continue
    print(len(s1))
    return len(s1)
    """

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        s = input()

        result = anagram(s)

        fptr.write(str(result) + '\n')

    fptr.close()
