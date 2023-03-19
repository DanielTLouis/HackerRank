"""
Consider an n-integer sequence, A={a_0,a_1,...,a_(n-1)}. We perform a query on A by
using an integer, d, to calculate the result of the following expression:
    min(max a_j); 0<=i<=n-d i<=j<i+d
In other words, if we let m_i=max(a_i,a_i+1,a_i+2,...,a_i+d-1), then you need to
calculate min(m_0,m_1,...,m_n-d).
Given arr and q queries, return a list of answers to each query.
Example
    arr=[2,3,4,5,6]
    queries=[2,3]
    The first query uses all of the subarrays of length 2: [2,3],[3,4],[4,5],[5,6] . The
    maxima of the subarrays are [3,4,5,6]. The minimum of these is 3.
    The second query uses all of the subarrays of length 3: [2,3,4],[3,4,5],[4,5,6]. The
    maxima of the subarrays are [4,5,6]. The minimum of these is 4.
    Return [3,4].
Function Description
    Complete the solve function below.
    solve has the following parameter(s):
        -int arr[n]: an array of integers
        -int queries[q]: the lengths of subarrays to query
Returns
    int[q]: the answers to each query
Input Format
    The first line consists of two space-separated integers, n and q.
    The second line consists of n space-separated integers, the elements of arr.
    Each of the q subsequent lines contains a single integer denoting the value of d for
    that query.
Constraints
    1<=n<=10^5
    0<=arr[i]<10^5
    1<=q<=100
    1<=d<=n
Sample Input 0
    5 5
    33 11 44 11 55
    1
    2
    3
    4
    5
Sample Output 0
    11
    33
    44
    44
    55
Explanation 0
For d=1, the answer is
    min(max(a_0),max(a_1),max(a_2),max(a_3),max(a_4))=11
.
For d=2, the answer is
    min(max(a_0,a_1),max(a_1,a_2),max(a_2,a_3),max(a_3,a_4))=33
.
For d=3, the answer is
    min(max(a_0,a_1,a_2),max(a_1,a_2,a_3),max(a_2,a_3,a_4))=44
.
For d=4, the answer is
    min(max(a_0,a_1,a_2,a_3),max(a_1,a_2,a_3,a_4))=44
.
For d=5, the answer is
    min(max(a_0,a_1,a_2,a_3,a_4,a_5))=55
.
Sample Input 1
    5 5
    1 2 3 4 5
    1
    2
    3
    4
    5
Sample Output 1
    1
    2
    3
    4
    5
Explanation 1
    For each query, the "prefix" has the least maximum value among the consecutive
    subsequences of the same size.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'solve' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER_ARRAY arr
#  2. INTEGER_ARRAY queries
#

def solve(arr, queries):
    # Write your code here
    n = len(arr)
    minimums = []
    for d in queries:
        maximum = minimum = max(arr[0:d])
        for i in range(1, n - d + 1):
            # New upper bound is higher
            if arr[i + d - 1] > maximum:
                maximum = arr[i + d - 1]
            # Previous lower bound was the maximum
            elif arr[i - 1] == maximum:
                maximum = max(arr[i : i + d])
            # Else, we mantain the current maximum

            # We update the minimum
            if maximum < minimum:
                minimum = maximum
        minimums.append(minimum)
    return minimums

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    q = int(first_multiple_input[1])

    arr = list(map(int, input().rstrip().split()))

    queries = []

    for _ in range(q):
        queries_item = int(input().strip())
        queries.append(queries_item)

    result = solve(arr, queries)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
