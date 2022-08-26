"""
Given a time in 12-hour AM/PM format, convert it to military (24-hour) time.
Note: - 12:00:00AM on a 12-hour clock is 00:00:00 on a 24-hour clock.
    - 12:00:00PM on a 12-hour clock is 12:00:00 on a 24-hour clock.
Example
    s='12:01:00PM'
        Return '12:01:00'.
    s='12:01:00AM'
        Return '00:01:00'.
Function Description
    Complete the timeConversion function in the editor below. It should return a new
    string representing the input time in 24 hour format.
    timeConversion has the following parameter(s):
        -string s: a time in 12 hour format
Returns
    string: the time in 24 hour format
Input Format
    A single string  that represents a time in 12-hour clock format (i.e.: hh:mm:ssAM or hh:mm:ssPM).
Constraints
    All input times are valid
Sample Input 0
    07:05:45PM
Sample Output 0
    19:05:45
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'timeConversion' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#

def timeConversion(s):
    # Write your code here
    time = s[:-2]
    daynight = s[-2:]
    if(time[:2:] == '12'):
        if(daynight == 'PM'):
            return time
        else:
            timeSep = time.split(":")
            timeSep[0] = '00'
            time = str(timeSep[0]) + ":" + str(timeSep[1]) + ":" + str(timeSep[2])
            return time
    elif(daynight == "PM"):
        timeSep = time.split(":")
        timeSep[0] = (int(timeSep[0]) + 12)
        time = str(timeSep[0]) + ":" + str(timeSep[1]) + ":" + str(timeSep[2])
        return time
    else:
        return time

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = timeConversion(s)

    fptr.write(result + '\n')

    fptr.close()
