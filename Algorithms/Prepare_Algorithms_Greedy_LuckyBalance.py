"""
Lena is preparing for an important coding competition that is
preceded by a number of sequential preliminary contests. Initially,
her luck balance is 0. She believes in "saving luck", and wants to
check her theory. Each contest is described by two integers,
L[i] and T[i]:
    -L[i] is the amount of luck associated with a contest. If Lena
    wins the contest, her luck balance will decrease by L[i]; if she
    loses it, her luck balance will increase by L[i].
    -T[i] denotes the contest's importance rating. It's equal to 1 if
    the contest is important, and it's equal to 0 if it's unimportant.
If Lena loses no more than k important contests, what is the maximum
amount of luck she can have after competing in all the preliminary
contests? This value may be negative.
Example
    k=2
    L=[5,1,4]
    T=[1,1,0]
        Contest        L[i]    T[i]
        1        5    1
        2        1    1
        3        4    0
    If Lena loses all of the contests, her will be 5+1+4=10. Since
    she is allowed to lose 2 important contests, and there are only 2
    important contests, she can lose all three contests to maximize
    her luck at 10.
    If k=1, she has to win at least 1 of the 2 important contests.
    She would choose to win the lowest value important contest
    worth 1. Her final luck will be 5+4-1=8.
Function Description
    Complete the luckBalance function in the editor below.
    luckBalance has the following parameter(s):
    int k: the number of important contests Lena can lose
    int contests[n][2]: a 2D array of integers where each contests[i]
    contains two integers that represent the luck balance and
    importance of the ith contest
Returns
    int: the maximum luck balance achievable
Input Format
    The first line contains two space-separated integers n and k, the
    number of preliminary contests and the maximum number of
    important contests Lena can lose.
    Each of the next n lines contains two space-separated integers,
    L[i] and T[i], the contest's luck balance and its importance
    rating.
Constraints
    1<=n<=100
    0<=k<=N
    1<=L[i]<=10^4
    T[i] isAnElementOf({0,1})
Sample Input
    STDIN   Function
    -----  --------
    6 3    n = 6, k = 3
    5 1    contests=[[5, 1], [2, 1], [1, 1], [8, 1], [10, 0], [5, 0]]
    2 1
    1 1
    8 1
    10 0
    5 0
Sample Output
    29
Explanation
    There are n=6 contests. Of these contests, 4 are important and
    she cannot lose more than k=3 of them. Lena maximizes her luck if
    she wins the 3rd important contest (where L[i]=1) and loses all
    of the other five contests for a total luck balance of
    5+2+8+10+5-1=29.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'luckBalance' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER k
#  2. 2D_INTEGER_ARRAY contests
#

def luckBalance(k, contests):
    # Write your code here
    im = []
    nonIm = []
    val = 0
    for i in contests:
        if(i[1] == 1):
            im.append(i)
        else:
            nonIm.append(i)
    im.sort(reverse=True)
    print(im)
    for i in range(0,len(im)):
        if(i < k):
            val += im[i][0]
        else:
            val -= im[i][0]
    for i in nonIm:
        val += i[0]
    return val

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    k = int(first_multiple_input[1])

    contests = []

    for _ in range(n):
        contests.append(list(map(int, input().rstrip().split())))

    result = luckBalance(k, contests)

    fptr.write(str(result) + '\n')

    fptr.close()
