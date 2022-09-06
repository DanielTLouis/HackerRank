"""
Given a string of lowercase letters in the range ascii[a-z], determine the index of a
character that can be removed to make the string a palindrome. There may be more than
one solution, but any will do. If the word is already a palindrome or there is no
solution, return -1. Otherwise, return the index of a character to remove.
Example
    s="bcbc"
    Either remove 'b' at index 0 or 'c' at index 3.
Function Description
    Complete the palindromeIndex function in the editor below.
    palindromeIndex has the following parameter(s):
        -string s: a string to analyze
Returns
    int: the index of the character to remove or -1
Input Format
    The first line contains an integer q, the number of queries.
    Each of the next q lines contains a query string s.
Constraints
    1<=q<=20
    1<=length of s<=10^5 + 5
    All characters are in the range ascii[a-z].
Sample Input
    STDIN   Function
    -----   --------
    3       q = 3
    aaab    s = 'aaab' (first query)
    baa     s = 'baa'  (second query)
    aaa     s = 'aaa'  (third query)
Sample Output
    3
    0
    -1
Explanation
    Query 1: "aaab"
    Removing 'b' at index 3 results in a palindrome, so return 3.
    Query 2: "baa"
    Removing 'b' at index 0 results in a palindrome, so return 0.
    Query 3: "aaa"
    This string is already a palindrome, so return -1. Removing any one of the
    characters would result in a palindrome, but this test comes first.
    Note: The custom checker logic for this challenge is available here.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'palindromeIndex' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#

def palindromeIndex(s):
    # Write your code here
    j = len(s) - 1
    temp = s
    error = True
    index = [0,0]
    while(error):
        #this is not good and needs refactoring but it works
        error = False
        for i in range(0, len(temp)//2):
            if(temp[i] != temp[j]):
                error = True
                index[0] = i
                index[1] = j
                break
            else:
                j -= 1
        if(error):
            temp = temp[:index[0]] + temp[index[0]+1:]
            print(index[0])
            print(temp)
            j = len(temp) - 1
            error = False
            for i in range(0, len(temp)//2):
                if(temp[i] != temp[j]):
                    error = True
                    break
                else:
                    j -= 1
            if(error):
                return index[1]
            else:
                return index[0]
    return -1

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        s = input()

        result = palindromeIndex(s)

        fptr.write(str(result) + '\n')

    fptr.close()
