"""
Objective
    In the previous challenge, we calculated a mean. In this challenge, we practice
    calculating a weighted mean. Check out the Tutorial* tab for learning materials
    and an instructional video!
    * https://www.hackerrank.com/challenges/s10-weighted-mean/tutorial *
Task
    Given an array, X, of N integers and an array, W, representing the respective
    weights of X's elements, calculate and print the weighted mean of X's elements.
    Your answer should be rounded to a scale of 1 decimal place (i.e., 12.3 format).
Example
    X=[1,2,3]
    W=[5,6,7]
    The array of values X[i]*W[i]=[5,12,21]. Their sum is 38. The sum of W=18. The
    weighted mean is 38/18=2.11111111..... Print 2.1 and return.
Function Description
    Complete the weightedMean function in the editor below.
    weightedMean has the following parameters:
        - int X[N]: an array of values
        - int W[N]: an array of weights
Prints
    - float: the weighted mean to one decimal place
Input Format
    The first line contains an integer, N, the number of elements in arrays X and W.
    The second line contains N space-separated integers that descdribe the elements of
    array X.
    The third line contains N space-separated integers that descdribe the elements of
    array W.
Constraints
    5<=N<=50
    0<X[i]<=100, where X[i] is the ith element of array X.
    0<W[i]<=100, where W[i] is the ith element of array W.
Output Format
    Print the weighted mean on a new line. Your answer should be rounded to a scale of
    1 decimal place (i.e., 12.3 format).
Sample Input
    STDIN           Function
    -----           --------
    5               X[] and W[] size n = 5
    10 40 30 50 20  X = [10, 40, 30, 50, 20]
    1 2 3 4 5       W = [1, 2, 3, 4, 5]
Sample Output
    32.0
Explanation
    We use the following formula to calculate the weighted mean:
        m_w=sumation(X_i * W_i)/sumation(W_i) -> (10*1+40*2+30*3+50*4+20*5)/(1+2+3+4+5)
            =480/15=32.0
    And then print our result to a scale of 1 decimal place (32.0) on a new line.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'weightedMean' function below.
#
# The function accepts following parameters:
#  1. INTEGER_ARRAY X
#  2. INTEGER_ARRAY W
#

def weightedMean(X, W):
    # Write your code here
    totalXW = 0
    totalW = 0
    for i in range(0, len(X)):
        totalXW += X[i] * W[i]
    for i in range(0, len(W)):
        totalW += W[i]
    print(round(totalXW / totalW,1))
if __name__ == '__main__':
    n = int(input().strip())

    vals = list(map(int, input().rstrip().split()))

    weights = list(map(int, input().rstrip().split()))

    weightedMean(vals, weights)
