#!/bin/python3

import math
import os
import random
import re
import sys



#
# Complete the 'sortedSum' function below.
#
# The function is expected to return an INTEGER.
# The function accepts INTEGER_ARRAY a as parameter.
#

def sortedSum(a):
    # Write your code here
    total = 0
    for j in range(0, len(a)):
        b = a[0:j+1]
        b.sort()
        for i in range(0,len(b)):
            total += (i+1) * b[i]
    return total  % ((10**9) +7)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    a_count = int(input().strip())

    a = []

    for _ in range(a_count):
        a_item = int(input().strip())
        a.append(a_item)

    result = sortedSum(a)

    fptr.write(str(result) + '\n')

    fptr.close()
