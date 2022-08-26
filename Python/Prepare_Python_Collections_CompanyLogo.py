#Problem
"""
A newly opened multinational brand has decided to base their
company logo on the three most common characters in the company
name. They are now trying out various combinations of company
names and logos based on this condition. Given a string s, which
is the company name in lowercase letters, your task is to find
the top three most common characters in the string.
    -Print the three most common characters along with their
    occurrence count.
    -Sort in descending order of occurrence count.
    -If the occurrence count is the same, sort the characters in
    alphabetical order.
For example, according to the conditions described above,
GOOGLE would have it's logo with the letters G,O,E.
Input Format
    A single line of input containing the string S.
Constraints
    3<len(S)<=10^4
    S has at least 3 distinct characters
Output Format
    Print the three most common characters along with their
    occurrence count each on a separate line.
    Sort output in descending order of occurrence count.
    If the occurrence count is the same, sort the characters in
    alphabetical order.
Sample Input 0
    aabbbccde
Sample Output 0
    b 3
    a 2
    c 2
Explanation 0
    aabbbccde
    Here, b occurs 3 times. It is printed first.
    Both a and c occur 4 times. So, a is printed in the second
    line and c in the third line because a comes before c in the
    alphabet.
    Note: The string S has at least 3 distinct characters.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

def fill_completions(s):
    c_dict = {}
    for i in s:
        if i in c_dict:
            c_dict[i] += 1
        else:
            c_dict[i] = 1
    return c_dict
if __name__ == '__main__':
    s = input()

    c_dict= fill_completions(s)
    #c_dict = dict(sorted(c_dict.items(),
        #key=lambda item: item[1], reverse = True))
    c_dict = dict(sorted(c_dict.items(),
        key=lambda item: (-item[1], item[0]), reverse = False))
    i = 0
    for item in c_dict:
        print(item, c_dict[item])
        if(i == 2):
            break
        i+=1
