"""
Given the time in numerals we may convert it into words, as shown below:
    5:00->five o' clock
    5:01->one minute past five
    5:10->ten minutes past five
    5:15->quarter past five
    5:30->half past five
    5:40->twenty minutes to six
    5:45->quarter to six
    5:47->thirteen minutes to six
    5:28->twenty eight minutes past five
At minutes=0, use o' clock. For 1<=minutes<=30, use past, and for 30<minutes use to. Note the space between the apostrophe and clock in o' clock. Write a program which prints the time in words for the input given in the format described.
Function Description
    Complete the timeInWords function in the editor below.
    timeInWords has the following parameter(s):
        int h: the hour of the day
        int m: the minutes after the hour
Returns
    string: a time string as described
Input Format
    The first line contains h, the hours portion The second line contains m, the 
    minutes portion
Constraints
    1<=h<=12
    0<=m<60
Sample Input 0
    5
    47
Sample Output 0
    thirteen minutes to six
Sample Input 1
    3
    00
Sample Output 1
    three o' clock
Sample Input 2
    7
    15
Sample Output 2
    quarter past seven
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'timeInWords' function below.
#
# The function is expected to return a STRING.
# The function accepts following parameters:
#  1. INTEGER h
#  2. INTEGER m
#
def hour(h):
    if(h == 1):
        return "one"
    if(h == 2):
        return "two"
    if(h == 3):
        return "three"
    if(h == 4):
        return "four"
    if(h == 5):
        return "five"
    if(h == 6):
        return "six"
    if(h == 7):
        return "seven"
    if(h == 8):
        return "eight"
    if(h == 9):
        return "nine"
    if(h == 10):
        return "ten"
    if(h == 11):
        return "eleven"
    if(h == 12):
        return "twelve"
    if(h == 13):
        return "one"
    return "no hour"

def minutes(mn):
    if(mn == 0):
        return ""
    if(mn == 1):
        return "one"
    if(mn == 2):
        return "two"
    if(mn == 3):
        return "three"
    if(mn == 4):
        return "four"
    if(mn == 5):
        return "five"
    if(mn == 6):
        return "six"
    if(mn == 7):
        return "seven"
    if(mn == 8):
        return "eight"
    if(mn == 9):
        return "nine"
    if(mn == 10):
        return "ten"
    if(mn == 11):
        return "Eleven"
    if(mn == 12):
        return "twelve"
    if(mn == 13):
        return "thirteen"
    if(mn == 14):
        return "fourteen"
    if(mn == 15):
        return "fifteen"
    if(mn == 16):
        return "sixteen"
    if(mn == 17):
        return "seventeen"
    if(mn == 18):
        return "eighteen"
    if(mn == 19):
        return "nineteen"
    if(int(mn) >= 20):
        print(minutes(9))
        return "twenty " + str(minutes(int(str(mn)[1])))


        
def timeInWords(h, m):
    # Write your code here
    ans = ""
    if(m == 0):
        hr = hour(h)
        ans = hr + " o' clock"
    elif(int(m) % 15 == 0):
        if(m == 15):
            ans = "quarter past " + hour(h)
        if(m == 30):
            ans = "half past " + hour(h)
        if(m == 45):
            ans = "quarter to " + hour(h + 1)
    else:
        if(m < 30):
            if(m == 1):
                ans = str(minutes(m)) + " minute past " + hour(h)
            else:
             ans = str(minutes(m)) + " minutes past " + hour(h)
        else:  
            if(m == 59):
                ans = str(minutes(60 - m)) + " minute to " + hour(h+1)
            else:
                ans = str(minutes(60 - m)) + " minutes to " + hour(h+1)
    return ans       

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    h = int(input().strip())

    m = int(input().strip())

    result = timeInWords(h, m)

    fptr.write(result + '\n')

    fptr.close()
