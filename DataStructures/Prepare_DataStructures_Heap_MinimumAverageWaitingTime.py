"""
Tieu owns a pizza restaurant and he manages it in his own way. While in a normal
restaurant, a customer is served by following the first-come, first-served rule, Tieu
simply minimizes the average waiting time of his customers. So he gets to decide who is
served first, regardless of how sooner or later a person comes.
Different kinds of pizzas take different amounts of time to cook. Also, once he starts
cooking a pizza, he cannot cook another pizza until the first pizza is completely
cooked. Let's say we have three customers who come at time t=0, t=1, & t=2 respectively,
and the time needed to cook their pizzas is 3, 9, & 6 respectively. If Tieu applies
first-come, first-served rule, then the waiting time of three customers is 3, 11, & 16
respectively. The average waiting time in this case is (3 + 11 + 16) / 3 = 10. This is
not an optimized solution. After serving the first customer at time t=3, Tieu can choose
to serve the third customer. In that case, the waiting time will be 3, 7, & 17
respectively. Hence the average waiting time is (3 + 7 + 17) / 3 = 9.
Help Tieu achieve the minimum average waiting time. For the sake of simplicity, just
find the integer part of the minimum average waiting time.
Input Format
    -The first line contains an integer N, which is the number of customers.
    -In the next N lines, the ith line contains two space separated numbers Ti and Li.
    Ti is the time when ith customer order a pizza, and Li is the time required to cook
    that pizza.
    -The ith customer is not the customer arriving at the ith arrival time.
Output Format
    Display the integer part of the minimum average waiting time.
Constraints
    1 ≤ N ≤ 10^5
    0 ≤ Ti ≤ 10^9
    1 ≤ Li ≤ 10^9
Note
    The waiting time is calculated as the difference between the time a customer orders
    pizza (the time at which they enter the shop) and the time she is served.
    Cook does not know about the future orders.
Sample Input #00
    3
    0 3
    1 9
    2 6
Sample Output #00
    9
Sample Input #01
    3
    0 3
    1 9
    2 5
Sample Output #01
    8
Explanation #01
    Let's call the person ordering at time = 0 as A, time = 1 as B and time = 2 as C. By
    delivering pizza for A, C and B we get the minimum average wait time to be
        (3 + 6 + 16)/3 = 25/3 = 8.33
    the integer part is 8 and hence the answer.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'minimumAverage' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY customers as parameter.
#

from heapq import *
from collections import deque
def minimumAverage(customers):
    customers.sort()

    t = customers[0][0]
    w = [customers[0][1]]
    d = {}
    d[customers[0][1]] = deque()
    d[customers[0][1]].append(customers[0][0])
    i = 1
    totalWaitTime = 0

    while w:
        #start baking
        n = heappop(w)
        orderTime = d[n].popleft()
        t += n
        totalWaitTime += (t - orderTime)

        #customers who show up while that pizza is baking
        while i < len(customers) and customers[i][0] <= t:
            c = customers[i]
            heappush(w, c[1])
            if c[1] in d.keys():
                d[c[1]].append(c[0])
            else:
                d[c[1]] = deque()
                d[c[1]].append(c[0])
            i += 1

        #if no one shows up while that pizza is baking, advance to next in line
        if i < len(customers) and len(w) == 0:
            c = customers[i]
            t = c[0]
            heappush(w, c[1])
            if c[1] in d.keys():
                d[c[1]].append(c[0])
            else:
                d[c[1]] = deque()
                d[c[1]].append(c[0])
            i += 1

    return totalWaitTime//len(customers)

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    customers = []

    for _ in range(n):
        customers.append(list(map(int, input().rstrip().split())))

    result = minimumAverage(customers)

    fptr.write(str(result) + '\n')

    fptr.close()
