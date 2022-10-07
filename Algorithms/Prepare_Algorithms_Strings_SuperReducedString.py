"""
Reduce a string of lowercase characters in range
ascii[‘a’..’z’]by doing a series of operations. In each
operation, select a pair of adjacent letters that match, and
delete them.
Delete as many characters as possible using this method and
return the resulting string. If the final string is empty,
return Empty String
Example.
    s='aab
    aab shortens to b in one operation: remove the adjacent
    a characters.
    s='abba'
    Remove the two 'b' characters leaving 'aa'. Remove the
    two 'a' characters to leave ''. Return 'Empty String'.
Function Description
    Complete the superReducedString function in the editor
    below.
    superReducedString has the following parameter(s):
        string s: a string to reduce
Returns
    string: the reduced string or Empty String
Input Format
    A single string, s.
Constraints
    1<=length of s<=100
Sample Input 0
    aaabccddd
Sample Output 0
    abd
Explanation 0
    Perform the following sequence of operations to get the
    final string:
        aaabccddd → abccddd → abddd → abd
Sample Input 1
    aa
Sample Output 1
    Empty String
Explanation 1
    aa → Empty String
Sample Input 2
    baab
Sample Output 2
    Empty String
Explanation 2
    baab → bb → Empty String
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'superReducedString' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#

def superReducedString(s):
    # Write your code here
    found = True
    while(found):
        found = False
        i = 0
        for i in range(0, len(s)-1):
            print(len(s), i)
            if(s[i] == s[i+1]):
                found = True
                if(i == len(s)-1 or i == 0):
                    if(i == 0 and len(s) > 2):
                        s = s[i+2:]
                        break
                    if(i == len(s) - 1 and len(s) > 2):
                        s = s[:i+2]
                        break
                    else:
                        return "Empty String"
                else:
                    s = s[:i] + s[i+2:]
                    break
    if(len(s) == 0):
        return "Empty String"
    else:
        return s

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = superReducedString(s)

    fptr.write(result + '\n')

    fptr.close()
