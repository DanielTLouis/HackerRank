"""
There is a sequence of words in CamelCase as a string of letters, , having the
following properties:
    -It is a concatenation of one or more words consisting of English letters.
    -All letters in the first word are lowercase.
    -For each of the subsequent words, the first letter is uppercase and rest of the
    letters are lowercase.
Given s, determine the number of words in s.
Example
    s=oneTwoThree
    here are 3 words in the string: 'one', 'Two', 'Three'.
Function Description
    Complete the camelcase function in the editor below.
    camelcase has the following parameter(s):
        -string s: the string to analyze
Returns
    int: the number of words in s
Input Format
    A single line containing string s.
Constraints
    1<=length of s <=10^5
Sample Input
    saveChangesInTheEditor
Sample Output
    5
Explanation
    String s contains five words:
        1.save
        2.Changes
        3.In
        4.The
        5.Editor
    Need help? Try this problem first to get familiar with HackerRank environment.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'camelcase' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#

def camelcase(s):
    # Write your code here
    count = 1 #first word starts with lowercase then is divided by upper case
    for i in s:
        if(i.isupper()):
            count += 1
    return count

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = camelcase(s)

    fptr.write(str(result) + '\n')

    fptr.close()
