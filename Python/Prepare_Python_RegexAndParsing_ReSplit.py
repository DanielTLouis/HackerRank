#Problem
"""
Check Tutorial* tab to know how to to solve.
    * https://www.hackerrank.com/challenges/re-split/tutorial *
    You are given a string s consisting only of digits 0-9,
    commas,, and dots .
    Your task is to complete the regex_pattern defined below,
    which will be used to re.split() all of the , and .
    symbols in s.
    It’s guaranteed that every comma and every dot in s is
    preceeded and followed by a digit.
Sample Input 0
    100,000,000.000
Sample Output 0
    100
    000
    000
    000
"""

#regex to say split at a comma or dot (dot is a regex symbol
# so it needs to be escaped)
regex_pattern = r",|\."	# Do not delete 'r'.

import re
print("\n".join(re.split(regex_pattern, input())))
