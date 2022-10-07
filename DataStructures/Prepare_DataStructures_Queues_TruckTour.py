"""
Suppose there is a circle. There are N petrol pumps on that circle. Petrol
pumps are numbered 0 to (N-1) (both inclusive). You have two pieces of
information corresponding to each of the petrol pump: (1) the amount of
petrol that particular petrol pump will give, and (2) the distance from
that petrol pump to the next petrol pump.
Initially, you have a tank of infinite capacity carrying no petrol. You can
start the tour at any of the petrol pumps. Calculate the first point from
where the truck will be able to complete the circle. Consider that the
truck will stop at each of the petrol pumps. The truck will move one
kilometer for each litre of the petrol.
Input Format
    The first line will contain the value of N.
    The next N lines will contain a pair of integers each, i.e. the amount
    of petrol that petrol pump will give and the distance between that
    petrol pump and the next petrol pump.
Constraints:
    1<=N<=10^5
    1<=amount of petrol, distance <=10^9
Output Format
    An integer which will be the smallest index of the petrol pump from
    which we can start the tour.
Sample Input
    3
    1 5
    10 3
    3 4
Sample Output
    1
Explanation
    We can start the tour from the second petrol pump.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'truckTour' function below.
#
# The function is expected to return an INTEGER.
# The function accepts 2D_INTEGER_ARRAY petrolpumps as parameter.
#
def shiftRight(pp):
    temp = pp[0]
    tt = [[0,0]] * len(pp)
    for i in range(0,len(pp)-1):
        tt[i] = pp[i+1]
    tt[len(pp)-1] = temp
    print(pp)
    print(tt)
    return tt
def truckTour(petrolpumps):
    # Write your code here
    old_petrol = 0
    s = -1
    for i in range(len(petrolpumps)):
        if old_petrol + petrolpumps[i][0] > petrolpumps[i][1]:
            if not old_petrol:
                s = i
            old_petrol = old_petrol + petrolpumps[i][0] - petrolpumps[i][1]
        else:
            old_petrol = 0
    return s
    """
    #Works for all cases not to large to test with custom input
    #(idk what could be wrong other than out of memory arrays and lists)
    truck = 0
    index = 0
    notFound = True
    while(notFound):
        notFound = False
        truck = 0
        for i in range(0,len(petrolpumps)):
            truck += petrolpumps[i][0]
            if(truck < petrolpumps[i][1]):
                notFound = True
                break
            else:
                truck -= petrolpumps[i][1]
                continue
        if(not notFound):
            return index
        else:
            #circle to right one
            petrolpumps = shiftRight(petrolpumps)
            index +=1
        if(index == len(petrolpumps)-1):
            break
    return -1
    """

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    n = int(input().strip())

    petrolpumps = []

    for _ in range(n):
        petrolpumps.append(list(map(int, input().rstrip().split())))

    result = truckTour(petrolpumps)

    fptr.write(str(result) + '\n')

    fptr.close()
