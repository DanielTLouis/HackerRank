"""
James found a love letter that his friend Harry has
written to his girlfriend. James is a prankster, so he
decides to meddle with the letter. He changes all the
words in the letter into palindromes.
To do this, he follows two rules:
    1.He can only reduce the value of a letter by 1, i.e.
    he can change d to c, but he cannot change c to d or d
    to b.
    2.The letter a may not be reduced any further.
Each reduction in the value of any letter is counted as a
single operation. Find the minimum number of operations
required to convert a given string into a palindrome.
Example
    s=cde
    The following two operations are performed: cde → cdd
    → cdc. Return 2.
Function Description
    Complete the theLoveLetterMystery function in the
    editor below.
    theLoveLetterMystery has the following parameter(s):
        string s: the text of the letter
Returns
    int: the minimum number of operations
Input Format
    The first line contains an integer q, the number of
    queries.
    The next q lines will each contain a string s.
Constraints
    1<=q<=10
    1<=| s |<=10^4
    All strings are composed of lower case English letters,
    ascii[a-z], with no spaces.
Sample Input
    STDIN   Function
    -----   --------
    4       q = 4
    abc     query 1 = 'abc'
    abcba
    abcd
    cba
Sample Output
    2
    0
    4
    2
Explanation
    1.For the first query, abc → abb → aba.
    2.For the second query, abcba is already a palindromic
    string.
    3.For the third query, abcd → abcc → abcb → abca
    → abba.
    4.For the fourth query, cba → bba → aba.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'theLoveLetterMystery' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#

def theLoveLetterMystery(s):
    # Write your code here
    count = 0
    j= len(s)-1
    for i in range(0, len(s)//2):
        if(s[i] != s[j]):
            while(s[i] != s[j]):
                if(ord(s[i]) > ord(s[j])):
                    s = s[:i] + chr(ord(s[i])-1) + s[i+1:]
                    count += 1
                else:
                    s = s[:j] + chr(ord(s[j])-1) + s[j+1:]
                    count += 1
        j-=1
    return count
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        s = input()

        result = theLoveLetterMystery(s)

        fptr.write(str(result) + '\n')

    fptr.close()
