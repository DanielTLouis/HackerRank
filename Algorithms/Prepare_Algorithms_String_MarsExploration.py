"""
A space explorer's ship crashed on Mars! They send a series of SOS messages to Earth
for help.
    NASA_Mars_Rover.jpg
Letters in some of the SOS messages are altered by cosmic radiation during
transmission. Given the signal received by Earth as a string, s, determine how many
letters of the SOS message have been changed by radiation.
Example
    s = 'SOSTOT'
    The original message was SOSSOS. Two of the message's characters were changed in
    transit.
Function Description
    Complete the marsExploration function in the editor below.
    marsExploration has the following parameter(s):
        -string s: the string as received on Earth
Returns
    int: the number of letters changed during transmission
Input Format
    There is one line of input: a single string, s.
Constraints
    1<=length of s <=99
    length of s modulo 3 = 0
    s will contain only uppercase English letters, ascii[A-Z].
Sample Input 0
    SOSSPSSQSSOR
Sample Output 0
    3
Explanation 0
    s = SOSSPSSQSSOR, and signal length |s|=12. They sent 4 SOS messages (i.e.: 12/3=4).
        Expected signal: SOSSOSSOSSOS
        Recieved signal: SOSSPSSQSSOR
        Difference:          X  X   X
Sample Input 1
    SOSSOT
Sample Output 1
    1
Explanation 1
    s = SOSSOT, and signal length |s|=6. They sent 2 SOS messages (i.e.: 6/3=2).
        Expected Signal: SOSSOS
        Received Signal: SOSSOT
        Difference:           X
Sample Input 2
    SOSSOSSOS
Sample Output 2
    0
Explanation 2
    Since no character is altered, return 0.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'marsExploration' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#

def marsExploration(s):
    # Write your code here
    count = 0
    for i in range(0,len(s),3):
        sos = s[i:i+3]
        if(sos[0] != "S"):
            count += 1
        if(sos[1] != "O"):
            count += 1
        if(sos[2] != "S"):
            count += 1
    return count

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = marsExploration(s)

    fptr.write(str(result) + '\n')

    fptr.close()
