"""
You will be given a list of 32 bit unsigned integers. Flip all
the bits ( 1->0 and 0->1 ) and return the result as an unsigned
integer.
Example
    n=9_10
    9_10=1001_2. We're working with 32 bits, so:
    00000000000000000000000000001001_2=9_10
    11111111111111111111111111110110_2=4294967286_10
    Return 4294967286.
Function Description
    Complete the flippingBits function in the editor below.
    flippingBits has the following parameter(s):
        -int n: an integer
Returns
    int: the unsigned decimal integer result
Input Format
    The first line of the input contains q, the number of
    queries.
    Each of the next q lines contain an integer, n, to process.
Constraints
    1<=q<=100
    0<=n<=2^32
Sample Input 0
    3
    2147483647
    1
    0
Sample Output 0
    2147483648
    4294967294
    4294967295
Explanation 0
    0111111111111111111111111111111111_2=2147483647_10
    1000000000000000000000000000000000_2=2147483648_10
    0000000000000000000000000000000001_2=1_10
    1111111111111111111111111111111110_2=4294967294_10
    0000000000000000000000000000000000_2=0_10
    1111111111111111111111111111111111_2=4294967295_10
Sample Input 1
    2
    4
    123456
Sample Output 1
    4294967291
    4294843839
Explanation 1
    0000000000000000000000000000100_2=4_10
    1111111111111111111111111111011_2=4294967291_10
    0000000000000001111000100100000_2=123456_10
    1111111111111110000111011011111_2=4294843839_10
Sample Input 2
    3
    0
    802743475
    35601423
Sample Output 2
    4294967295
    3492223820
    4259365872
Explanation 2
    0000000000000000000000000000000000_2=0_10
    1111111111111111111111111111111111_2=4294967295_10
    0010111111011000111001001011001111_2=802743475_10
    1101000000100111000110110100110000_2=342223820_10
    0000001000011111001111000000111111_2=35601425_10
    1111110111100000110000111111000000_2=4259365872_10
*binary may not be accurate and was typed wrong*
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'flippingBits' function below.
#
# The function is expected to return a LONG_INTEGER.
# The function accepts LONG_INTEGER n as parameter.
#

def flippingBits(n):
    # Write your code here
    #converts to binary(bi stars with 0b so need to slice that)
    bit_s = bin(n)[2:]
    #get a string of 32 0s and then slice off the size of the bi
    ## append the bi to end ot string so it has leading 0s
    bit_s = ("0"*32)[len(bit_s):]+ (bit_s)
    inverse_s = ''
    for i in bit_s:
        if i == '0':
            inverse_s += '1'
        else:
            inverse_s += '0'
    return (int(inverse_s,2))

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        n = int(input().strip())

        result = flippingBits(n)

        fptr.write(str(result) + '\n')

    fptr.close()
