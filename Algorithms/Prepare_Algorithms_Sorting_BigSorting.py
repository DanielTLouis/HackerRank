"""
Consider an array of numeric strings where each string is a positive number with
anywhere from 1 to 10^6 digits. Sort the array's elements in non-decreasing, or
ascending order of their integer values and return the sorted array.
Example
    unsorted = ['1','200','150','3']
    Return the array ['1', '3', '150', '200'].
Function Description
    Complete the bigSorting function in the editor below.
    bigSorting has the following parameter(s):
        -string unsorted[n]: an unsorted array of integers as strings
Returns
    string[n]: the array sorted in numerical order
Input Format
    The first line contains an integer, n, the number of strings in unsorted.
    Each of the n subsequent lines contains an integer string, unsorted[i].
Constraints
    1<=n<=2X10^5
    Each string is guaranteed to represent a positive integer.
    There will be no leading zeros.
    The total number of digits across all strings in unsorted is between 1 and 10^6
    (inclusive).
Sample Input 0
    6
    31415926535897932384626433832795
    1
    3
    10
    3
    5
Sample Output 0
    1
    3
    3
    5
    10
    31415926535897932384626433832795
Explanation 0
    The initial array of strings is unsorted=[31415926535897932384626433832795,1,3,10,
    3,5]. When we order each string by the real-world integer value it represents, we
    get:
        1<=3<=3<=5<=10<=31415926535897932384626433832795
    We then print each value on a new line, from smallest to largest.
Sample Input 1
    8
    1
    2
    100
    12303479849857341718340192371
    3084193741082937
    3084193741082938
    111
    200
Sample Output 1
    1
    2
    100
    111
    200
    3084193741082937
    3084193741082938
    12303479849857341718340192371
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'bigSorting' function below.
#
# The function is expected to return a STRING_ARRAY.
# The function accepts STRING_ARRAY unsorted as parameter.
#
"""
This problem bugged me because it's a trivial sort and yet the outcomes were markedly different in Python 3.6, depending on how you approach it.
Some speculate that sort() is faster than sorted(), but these functions are basically the same except the former is an in-place sort (which shouldn't matter here).
Edit: sorted() is a wrapper for sort(). See also: https://stackoverflow.com/questions/1915376/is-pythons-sorted-function-guaranteed-to-be-stable
Analysis with cprofile kept reporting that print() was the cause of the slowdown, which made no sense at first.
It turned out that int -> str conversions (whether by print or explicitly converting the values first) are surprisingly costly (probably far more costly with huge integers, as test cases #4, #5, and #6 appear to contain). If you're taking the "convert to int, sort, then print" route, you're actually printing ints, which are converted internally to strings for display. And that's why print becomes slow.
First, a typical slow implementation (I originally had a longer form for these - the list comprehension here makes it more compact but not noticeably faster):
for i in sorted([int(s) for s in unsorted]):
    print(i) # int to str = costly
Adding an int -> str conversion before print doesn't help - in fact, it gets a little bit slower:
for i in sorted([int(s) for s in unsorted]):
    s = str(i) # This is a costly step
    print(s)
However, using the key=int sorting argument performs the necessary conversions internally during the sort process itself, while returning the original string values that are quickly printed. (Note that the argument to key is the name of a function that takes one argument, in this case int().) I'm going to guess that str -> int is much faster than int -> str
A fast (challenge-friendly) in-place sort():
unsorted.sort(key=int)
for s in unsorted:
    print(s)
sorted() is virtually the same speed, and doesn't modify unsorted:
for s in sorted(unsorted, key=int):
    print(s)
For grins, let's make it slow again (in fact, this becomes slowest of all the attempts!):
for s in sorted(unsorted, key=int):
    i = int(s) # Forces costly int -> str conversion in print()
    print(i)
More info:
https://docs.python.org/3.6/library/functions.html?highlight=sorted#sorted
https://docs.python.org/3.6/library/profile.html#profile.Profile
"""
def bigSorting(unsorted):
    # Write your code here
    unsorted.sort(key=int)
    return unsorted

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    unsorted = []

    for _ in range(n):
        unsorted_item = input()
        unsorted.append(unsorted_item)

    result = bigSorting(unsorted)

    fptr.write('\n'.join(result))
    fptr.write('\n')

    fptr.close()
