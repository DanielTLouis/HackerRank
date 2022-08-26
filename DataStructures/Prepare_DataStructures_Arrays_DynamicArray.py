"""
-Declare a 2-dimensional array, , of  empty arrays. All arrays are zero indexed.
-Declare an integer, LastAnswer, and initialize it to 0.
-There are 2 types of queries, given as an array of strings for you to parse:
    1.Query: 1 x y
        1.Let idx=((x^lastAnswer)%n).
        2.Append the integer y to arr[idx].
    2.Query: 2 x y
        1.Let idx=((x^lastAnswer)%n).
        2.Assign the value arr[idx][y%size(arr[idx])] to lastAnswer.
        3.Store the new value of lastAnswer to an answers array.
Note: ^ is the bitwise XOR operation, which corresponds to the ^ operator in most languages. Learn more about it on Wikipedia. % is the modulo operator.
Finally, size(arr[idx]) is the number of elements in arr[idx]
Function Description
    Complete the dynamicArray function below.
    dynamicArray has the following parameters:
        - int n: the number of empty arrays to initialize in
        - string queries[q]: query strings that contain 3 space-separated integers
Returns
    int[]: the results of each type 2 query in the order they are presented
Input Format
    The first line contains two space-separated integers, n, the size of arr to create,
    and q, the number of queries, respectively.
    Each of the q subsequent lines contains a query string, queries[i].
Constraints
    1<=n,q<=10^5
    0<=x,y<=10^9
    It is guaranteed that query type 2 will never query an empty array or index.
Sample Input
    2 5
    1 0 5
    1 1 7
    1 0 3
    2 1 0
    2 1 1
Sample Output
    7
    3
Explanation
    Initial Values:
        lastAnswer=0
        n=2
        arr[0]= [ ]
        arr[1]= [ ]
    Query 0: Append 5 to arr[((0^0)%2)]=arr[0].
        lastAnswer = 0
        arr[0]= [5]
        arr[1]= [ ]
    Query 1: Append 7 to arr[((0^0)%2)]=arr[0].
        arr[0]= [5]
        arr[1]= [7]
    Query 2: Append 3 to arr[((0^0)%2)]=arr[0].
        lastAnswer=0
        arr[0]= [5, 3]
        arr[1]= [7]
    Query 3: Assign the value at index 0 of arr[((1^0)%2)]=arr[1] to lastAnswer, print
    lastAnswer.
        lastAnswer=7
        arr[0]= [5, 3]
        arr[1]= [7]
            7
    Query 4: Assign the value at index 1 of arr[((1^7)%2)] = arr[0] to lastAnswer,
    print lastAnswer.
        lastAnswer = 3
        arr[0]= [5, 3]
        arr[1]= [7]
            3
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'dynamicArray' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER n
#  2. 2D_INTEGER_ARRAY queries
#

def dynamicArray(n, queries):
    # Write your code here
    lastAnswer = 0
    arr = [[] for _ in range(n)]
    ans = []
    for q in queries:
        idx = (q[1] ^ lastAnswer) % n
        if(q[0] == 1):
            arr[idx].append(q[2])
        else:
            pos = q[2] % len(arr[idx])
            lastAnswer = arr[idx][pos]
            ans.append(lastAnswer)
    return ans

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    q = int(first_multiple_input[1])

    queries = []

    for _ in range(q):
        queries.append(list(map(int, input().rstrip().split())))

    result = dynamicArray(n, queries)

    fptr.write('\n'.join(map(str, result)))
    fptr.write('\n')

    fptr.close()
