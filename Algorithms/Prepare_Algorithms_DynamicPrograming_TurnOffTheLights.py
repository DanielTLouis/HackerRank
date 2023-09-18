"""
There are  bulbs in a straight line, numbered from 0 to n-1. Each bulb  has a button associated
with it, and there is a cost, c_i, for pressing this button. When some button  is pressed, all the
bulbs at a distance <=k from bulb i will be toggled(off->on, on->off).
    Given n, k, and the costs for each button, find and print the minimum cost of turning off all
    bulbs if they're all on initially.
Input Format
    The first line contains two space-separated integers describing the respective values of  and .
    The second line contains  space-separated integers describing the respective costs of each
    bulb (i.e., c0,c1,...,c(n-1)).
Constraints
    3<=n<=10^4
    0<=k<=10000<=c_i<=10^9
Output Format
    Print a long integer denoting the minimum cost of turning off all n bulbs.
Sample Input
    3 1
    1 1 1
Sample Output
    1
Explanation
    If we press the middle switch, the middle bulb and the k=1 closest adjacent bulbs (i.e., the
    first and third) will turn off. Because all bulbs will be off in one button press, this cost
    is minimal. Thus, we print  as our answer.
"""
#!/bin/python3

import os
import sys

def get_sum(s, c, k, t):
    v = None
    for p in range(s, len(c), 2 * k + 1):
        print(p, end=' ')
        if v:
            t += 2 * k + 1
        else:
            v = 0

        v += c[p]

    if t < len(c):
        v = None

    print(' => ', v, 't=', t)
    return v

#
# Complete the turnOffTheLights function below.
#
def turnOffTheLights(k, c):
    min_sum = None
    for s in range(k + 1):
        summ = get_sum(s, c, k, k + 1 + s)
        if not min_sum or (summ and min_sum > summ):
            min_sum = summ

    return min_sum


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n, k = map(int, input().split())
    c = list(map(int, input().rstrip().split()))

    result = turnOffTheLights(k, c)
    fptr.write(str(result) + '\n')
    fptr.close()
