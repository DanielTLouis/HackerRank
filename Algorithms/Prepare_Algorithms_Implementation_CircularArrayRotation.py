"""
John Watson knows of an operation called a right circular
rotation on an array of integers. One rotation operation moves
the last array element to the first position and shifts all
remaining elements right one. To test Sherlock's abilities,
Watson provides Sherlock with an array of integers. Sherlock
is to perform the rotation operation a number of times then
determine the value of the element at a given position.
For each array, perform a number of right circular rotations
and return the values of the elements at the given indices.
Example
    a=[3,4,5]
    k=2
    queries=[1,2]
    Here k is the number of rotations on a, and queries holds
    the list of indices to report. First we perform the two
    rotations: [3,4,5]->[5,3,4]->[4,5,3]
    Now return the values from the zero-based indices 1 and 2
    as indicated in the queries array.
    a[1]=5
    a[2]=3
Function Description
    Complete the circularArrayRotation function in the editor
    below.
    circularArrayRotation has the following parameter(s):
        int a[n]: the array to rotate
        int k: the rotation count
        int queries[1]: the indices to report
Returns
    int[q]: the values in the rotated  as requested in m
Input Format
    The first line contains 3 space-separated integers, n, k,
    and q, the number of elements in the integer array, the
    rotation count and the number of queries.
    The second line contains n space-separated integers, where
    each integer  describes array element a[i] (where 0<=i<n).
    Each of the q subsequent lines contains a single integer,
    queries[i], an index of an element in a to return.
Constraints
    1<=n<=10^5
    1<=a[i]<=10^5
    1<=k<=10^5
    1<=q<=500
    0<=queries[i]<n
Sample Input 0
    3 2 3
    1 2 3
    0
    1
    2
Sample Output 0
    2
    3
    1
Explanation 0
    After the first rotation, the array is [3,1,2].
    After the second (and final) rotation, the array is
    [2,3,1].
    We will call this final state array b=[2,3,1]. For each
    query, we just have to get the value of b[queries[i]].
        1. queries[0]=0, b[0]=2.
        2. queries[1]=1, b[1]=3.
        3. queries[2]=2, b[2]=1.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'circularArrayRotation' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER_ARRAY a
#  2. INTEGER k
#  3. INTEGER_ARRAY queries
#

def circularArrayRotation(a, k, queries):
    # Write your code here
    if(k > len(a)):
        k = k % len(a)
    ans=[]
    shift=a[len(a)-k:]+a[:len(a)-k]
    for i in queries:
        ans.append(shift[i])
    return ans
    """
    #Works for going around
    indexing = []
    for i in a:
        indexing.append(i)
    print(a)
    for i in range(0,k):
        for i in range(0, len(a)):
            if(i == 0):
                indexing[i] = a[len(a)-1]
                continue
            else:
                indexing[i] = a[i-1]
        for i in range(0, len(indexing)):
            a[i] = indexing[i]
        print("A:",a)
    print(indexing)
    ans = []
    for i in queries:
        ans.append(indexing[i])
    return ans
    """
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    k = int(first_multiple_input[1])

    q = int(first_multiple_input[2])

    a = list(map(int, input().rstrip().split()))

    queries = []

    for _ in range(q):
        queries_item = int(input().strip())
        queries.append(queries_item)

    result = circularArrayRotation(a, k, queries)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
