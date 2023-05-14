"""
Nikita just came up with a new array game. The rules are as follows:
    * Initially, Nikita has an array of integers.
    * In each move, Nikita must partition the array into 2 non-empty contiguous parts such
    that the sum of the elements in the left partition is equal to the sum of the elements in
    the right partition. If Nikita can make such a move, she gets 1 point; otherwise, the game
    ends.
    * After each successful move, Nikita discards either the left partition or the right
    partition and continues playing by using the remaining partition as array arr.
Nikita loves this game and wants your help getting the best score possible. Given arr, can you
find and print the maximum number of points she can score?
For example, Nikita starts with the array arr=[1,2,3,6]. She first splits it into al=[1,2,3]
and a=[6], then discards a2, arr=al->al=[1,2], a2=[3]. Discard a2 leaving arr=[1,2]. This
cannot be further split, so Nikita scored 2.
Function Description
    Complete the arraySplitting function in the editor below. It should return an integer that
    reperesents the number of times Nikita can split the array.
    arraySplitting has the following parameter(s):
        arr: an array of integers
Input Format
    The first line contains an integer t, the number of test cases.
    Each of the next t pairs of lines is as follows:
        The first line contains an integer n, the size of array arr.
        The next line contains n space-separated integers arr[i].
Constraints
    1<=t<=10
    1<=n<=2^14
    0<=arr[i]<=10^9
Scoring
    1<=n<=2^8 for 30% of the test data
    1<=n<=2^11 for 60% of the test data
    1<=n<=2^14 for 100% of the test data
Output Format
    For each test case, print Nikita's maximum possible score on a new line.
Sample Input
    3
    3
    3 3 3
    4
    2 2 2 2
    7
    4 1 0 1 1 0 1
Sample Output
    0
    2
    3
Explanation
    Test Case 0:
    Nikita cannot partition A into 2 parts having equal sums. Therefore, her maximum possible
    score is 0 and we print 0 on a new line.
    Test Case 1:
        Initially, A looks like this:
            split(3).png
        She splits the array into 2 partitions having equal sums, and then discards the left
        partition:
            split(1).png
        She then splits the new array into 2 partitions having equal sums, and then discards
        the left partition:
            split(2).png
        At this point the array only has 1 element and can no longer be partitioned, so the
        game ends. Because Nikita successfully split the array twice, she gets 2 points and we
        print 2 on a new line.
    Test Case 2:
            array              a1       a2
            [4,1,0,1,1,0,1]    [4]      [1,0,1,1,0,1]
            [1,0,1,1,0,1]      [1,0,1]  [1,0,1]
            [1,0,1]            [1,0]    [1]
        The answer is 3.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'arraySplitting' function below.
#
# The function is expected to return an INTEGER.
# The function accepts INTEGER_ARRAY arr as parameter.
#
def find(arr,st,end,sum_till,cut,su):
    cf = find_crtcl_index(arr,sum_till,cut,st,end,su/2)

    if cf != None:
        left = find(arr,st,cf,sum_till,cut,su/2)
        right = find(arr,cf + 1,end,sum_till,cut + (su/2),su/2)
        return 1 + max(left,right)
    else:
        return 0

def find_crtcl_index(arr,sum_till,cut,st,end,fulfil):
    if st == end:return
    ans = None
    while st <= end:
        mid = (st+end)//2
        val = sum_till[mid]-cut

        if val == fulfil:
            ans = mid

        if val < fulfil:
            st = mid + 1
        else:
            end = mid - 1
    return ans




def arraySplitting(arr):
    # Write your code here
    sum_till = []
    pr = 0
    for i in arr:
        pr += i
        sum_till.append(pr)
    if set(arr) == {0}:
        return len(arr)-1
    return find(arr,0,len(arr)-1,sum_till,0,sum_till[-1])
"""
def arraySplitting(arr):
    # Write your code here
    moved = True
    points = 0
    while(moved):
        moved = False
        for i in range(0,len(arr)):
            temp1 = arr[:i]
            temp2 = arr[i:]
            if(sum(temp1) == sum(temp2)):
                if(len(temp1) >= len(temp2)):
                    arr = temp1
                else:
                    arr = temp2
                moved = True
                points += 1
                break
        if(len(arr) <= 1):
            moved = False
    return points
"""

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        arr_count = int(input().strip())

        arr = list(map(int, input().rstrip().split()))

        result = arraySplitting(arr)

        fptr.write(str(result) + '\n')

    fptr.close()
x
