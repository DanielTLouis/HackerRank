"""
An English text needs to be encrypted using the following encryption scheme.
First, the spaces are removed from the text. Let L be the length of this text.
Then, characters are written into a grid, whose rows and columns have the 
following constraints:
    floor(sqrt(L))<= row <= column <= ceil(sqrt(L))
Example
    s= if man was meant to stay on the ground good would have given us roots
    After removing spaces, the string is 54 characters long. sqrt(54) is between 
    7 and 8, so it is written in the form of a grid with 7 rows and 8 columns.
        ifmanwas  
        meanttos          
        tayonthe  
        groundgo  
        dwouldha  
        vegivenu  
        sroots
        -Ensure that rowsXcolumns>=L
        -If multiple grids satisfy the above conditions, choose the one with the 
        minimum area, i.e. Rows X columns.
    The encoded message is obtained by displaying the characters of each column, 
    with a space between column texts. The encoded message for the grid above is:
    imtgdvs fearwer mayoogo anouuio ntnnlvt wttddes aohghn sseoau
    Create a function to encode a message.
Function Description
    Complete the encryption function in the editor below.
    encryption has the following parameter(s):
        -string s: a string to encrypt
Returns
    string: the encrypted string
Input Format
    One line of text, the string S
Constraints
    1<=length of s <=81
    s contains characters in the range ascii[a-z] and space, ascii(32).
Sample Input
    haveaniceday
Sample Output 0
    hae and via ecy
Explanation 0
    L=12, sqrt(12) is between 3 and 4.
    Rewritten with 3 rows and 4 columns:
        have
        anic
        eday
Sample Input 1
    feedthedog    
Sample Output 1 
    fto ehg ee dd
Explanation 1
    L=10, sqrt(10) is between 3 and 4.
    Rewritten with 3 rows and 4 columns:
        feed
        thed
        og
Sample Input 2
    chillout
Sample Output 2
    clu hlt io
Explanation 2
    L=8, sqrt(8) is between 2 and 3.
    Rewritten with 3 columns and 3 rows (2*3=6<8 so we have to use 3X3.)
        chi
        llo
        ut
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'encryption' function below.
#
# The function is expected to return a STRING.
# The function accepts STRING s as parameter.
#

def encryption(s):
    # Write your code here
    encoded = []
    result = ''
    L = len(s.replace(' ', ''))
    rows = math.floor(math.sqrt(L))
    cols = math.ceil(math.sqrt(L))
    if (rows*cols < L):
        rows += 1
    i = 0
    row_block = 0
    while i < rows:
        try:
            encoded.append(list(s[row_block:row_block+cols]))
        except IndexError:
            encoded.append(list(s[row_block:]))
        row_block += cols
        i += 1
    for col in range(cols):
        for row in range(rows):
            try:
                result += encoded[row][col]
            except IndexError:
                break
        result += ' '
    return result

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = encryption(s)

    fptr.write(result + '\n')

    fptr.close()