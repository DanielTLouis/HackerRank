"""
Consider a string, s, of n lowercase English letters where each character, s_i (0<=i<n),
denotes the letter at index i in s. We define an (a,b,c,d) palindromic tuple of  to be a
sequence of indices in satisfying the following criteria:
    * s_a=s_d, meaning the characters located at indices a and d are the same.
    * s_b=s_c, meaning the characters located at indices b and c are the same.
    * 0<=a<b<c<d<|s|, meaning that a, b, c, and d are ascending in value and are valid indices
    within string s.
Given s, find and print the number of (a,b,c,d) tuples satisfying the above conditions. As
this value can be quite large, print it modulo (10^9 +7).
Function Description
    Complete the function shortPalindrome in the editor below.
    shortPalindrome has the following paramter(s):
        - string s: a string
Returns
    - int: the number of tuples, modulo (10^9 +7)
Input Format
    A single string, s.
Constraints
    1<=|s|<=10^6
    It is guaranteed that s only contains lowercase English letters.
Sample Input 0
    kkkkkkz
Sample Output 0
    15
Explanation 0
    The letter z will not be part of a valid tuple because you need at least two of the same
    character to satisfy the conditions defined above. Because all tuples consisting of four
    k's are valid, we just need to find the number of ways that we can choose four of the six
    k's. This means our answer is (6 ove 4)mod(10^9 + 7).
Sample Input 1
    ghhggh
Sample Output 1
    4
Explanation 1
    The valid tuples are:
        1. (0,1,2,3)
        2. (0,1,2,4)
        3. (1,3,4,5)
        4. (2,3,4,5)
    Thus, our answer is 4mod(10^9 +7)=4.
Sample Input 0
    kkkkkkz
Sample Output 0
    15
Sample Input 1
    abbaab
Sample Output 1
    4
Sample Input 2
    akakak
Sample Output 2
    2
Explanation 2
    Tuples possible are (1,2,4,5) and(0,1,3,4)
"""
#!/bin/python3

import math
import os
import random
import re
import sys
import itertools

#
# Complete the 'shortPalindrome' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#

def shortPalindrome(s):
    # Write your code here
    dim1 = [0] * 26
    dim2 = [0] * 26 * 26
    dim3 = [0] * 26

    count = 0

    mod = 1000000007

    for k in s:

        c = ord(k) - ord('a')

        count = (count + dim3[c]) % mod

        ic = c

        for i in range(26):

            dim3[i] = (dim3[i] + dim2[ic]) % mod
            dim2[ic] = (dim2[ic] + dim1[i]) % mod
            ic += 26

        dim1[c] += 1

    return count
    """
    count = 0
    indices = [0] * len(s)
    for i in range(0, len(s)):
        indices[i] = i
    sList = list(s)
    m = list(map(lambda x, y: [x,y], indices, sList))
    for i in itertools.permutations(m):
        #conditions 1 and 2
        if(i[0][1] == i[3][1] and i[1][1] == i[2][1]):
            #need to figure out the number of the indices
            if(i[0][0]<i[1][0] and i[1][0]<i[2][0] and i[2][0]<i[3][0] and i[3][0]<i[4][0]):
                count += 1
    return count
    """

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = shortPalindrome(s)

    fptr.write(str(result) + '\n')

    fptr.close()
