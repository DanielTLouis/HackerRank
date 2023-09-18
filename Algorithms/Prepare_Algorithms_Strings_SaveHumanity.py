"""
Oh!! Mankind is in trouble again. This time, it's a deadly disease spreading at a rate never seen
before. The need of the hour is to set up efficient virus detectors. You are the lead at Central
Hospital and you need to find a fast and reliable way to detect the footprints of the virus DNA in
that of the patient.
The DNA of the patient as well as of the virus consists of lowercase letters. Since the collected
data is raw, there may be some errors. You will need to find all substrings in the patient DNA
that either exactly match the virus DNA or have at most one mismatch, i.e., a difference in at
most one location.
For example, "aa" and "aa" are matching, "ab" and "aa" are matching, while "abb" and "bab" are not.
Function Description
    Complete the virusIndices function in the editor below. It should print a list of
    space-separated integers that represent the starting indices of matching substrings in
    increasing order, or No match!.
    virusIndices has the following parameter(s):
        * p: a string that represents patient DNA
        * v: a string that represents virus DNA
Input Format
    The first line contains an integer t, the number of test cases.
    . Each of the next t lines contains two space-separated strings p (the patient DNA) and v (the virus DNA).
Constraints
    1<=t<=10
    1<=|p|,|v|<=10^5
    All characters in p and v isAnElementOF(ascii[a-z]).
Output Format
    For each test case, output a single line containing a space-delimited list of starting indices
    (0-indexed) of substrings of p which are matching with  according to the condition mentioned
    above. The indices have to be in increasing order. If there is no matching substring, output
    No Match!.
Sample Input 0
    3
    abbab ba
    hello world
    banana nan
Sample Output 0
    1 2
    No Match!
    0 2
Explanation 0
    For the first case, the substrings of p starting at indices 1 and 2 are "bb" and "ba" and they
    are matching with the string v which is "ba".
    For the second case, there are no matching substrings so the output is No Match!.
    For the third case, the substrings of p starting at indices 0 and 2 are "ban" and "nan" and
    they are matching with the string v which is "nan".
Sample Input 1
    3
    cgatcg gc
    atcgatcga cgg
    aardvark ab
Sample Output 1
    1 3
    2 6
    0 1 5
Explanation 1
    For the first case, the substrings of p starting at indices 1 and 3 are "ga" and "gc" and they
    are matching with the string  which is "gc".
    For the second case, the substrings of p starting at indices 2 and 6 are "cga" and "cga" and
    they are matching with the string  which is "cgg".
    For the third case, the substrings of p starting at indices 0, 1 and 5 are "aa", "ar" and "ar"
    and they are matching with the string  which is "ab".
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'virusIndices' function below.
#
# The function accepts following parameters:
#  1. STRING p
#  2. STRING v
#
def small_match(w1, w2):
    counter = 0
    for i in range(len(w1)):
        if w1[i] != w2[i]:
            counter += 1
            if counter > 1:
                return 0
    return 1
def match(w1, w2):
    length = len(w1)
    if length < 10:
        return small_match(w1, w2)
    w11 = w1[:length // 2]
    w12 = w1[length // 2:]
    w21 = w2[:length // 2]
    w22 = w2[length // 2:]

    s1 = (w11 == w21)
    s2 = (w12 == w22)

    if s1 and s2:
        return True
    elif s1 and not s2:
        return match(w12, w22)
    elif not s1 and s2:
        return match(w11, w21)
    else:
        return False

def virusIndices(p, v):
    # Print the answer for this test case in a single line
    res = ''
    if len(v) > len(p):
        return "No Match!"
    else:
        for i in range(len(p) - len(v) + 1):
            temp = p[i:i + len(v)]

            flag = match(temp, v)
            if flag:
                res += str(i) + ' '
        if len(res) == 0:
            return "No Match!"
        else:
            return res.strip()

if __name__ == '__main__':
    t = int(input().strip())

    for t_itr in range(t):
        first_multiple_input = input().rstrip().split()

        p = first_multiple_input[0]

        v = first_multiple_input[1]

        print(virusIndices(p, v))
