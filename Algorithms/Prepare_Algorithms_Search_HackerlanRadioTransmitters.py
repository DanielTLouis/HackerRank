"""
Hackerland is a one-dimensional city with houses aligned at integral locations along a road.
The Mayor wants to install radio transmitters on the roofs of the city's houses. Each
transmitter has a fixed range meaning it can transmit a signal to all houses within that
number of units distance away.
Given a map of Hackerland and the transmission range, determine the minimum number of
transmitters so that every house is within range of at least one transmitter. Each transmitter
must be installed on top of an existing house.
Example
    x=[1,2,3,5,9]
    k=1
    3 antennae at houses 2 and 5 and 9 provide complete coverage. There is no house at
    location 7 to cover both 5 and 9. Ranges of coverage, are [1,2,3], [5], and [9].
Function Description
    Complete the hackerlandRadioTransmitters function in the editor below.
    hackerlandRadioTransmitters has the following parameter(s):
        int x[n]: the locations of houses
        int k: the effective range of a transmitter
Returns
    int: the minimum number of transmitters to install
Input Format
    The first line contains two space-separated integers n and k, the number of houses in
    Hackerland and the range of each transmitter.
    The second line contains n space-separated integers describing the respective locations of
    each house x[i].
Constraints
    1<=n,k<=10^5
    1<=x[i]<=10^5
    There may be more than one house at the same location.
Subtasks
    1<=n<=1000 for 50% of the maximum score.
Output Format
    Print a single integer denoting the minimum number of transmitters needed to cover all of
    the houses.
Sample Input 0
    STDIN       Function
    -----       --------
    5 1         x[] size n = 5, k = 1
    1 2 3 4 5   x = [1, 2, 3, 4, 5]
Sample Output 0
    2
Explanation 0
    The diagram below depicts our map of Hackerland:
        k-nearest(2).png
    We can cover the entire city by installing 2 transmitters on houses at locations 2 and 4.
Sample Input 1
    8 2
    7 2 4 6 5 9 12 11
Sample Output 1
    3
Explanation 1
    The diagram below depicts our map of Hackerland:
        k-nearest2(2).png
    We can cover the entire city by installing 3 transmitters on houses at locations 4, 9,
    and 12.
"""

#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'hackerlandRadioTransmitters' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER_ARRAY x
#  2. INTEGER k
#

def hackerlandRadioTransmitters(x, k):
    # Write your code here
    """
    1. Sort the array (in increasing order preferrably).
    2. Put the pivot at the start and move towards the right and determine the max
    transmission distance. For e.g., Max transmission from 1 (i.e., x[0]) is
    max_tr =x[0]+2 =3. Put transmitter here.
    3. Use Binary search to check whether 3 exists in the array and get its index. If
    not (which is in our case), get the number and its index just lesser than 3
    (i.e., x[1]=2 in our example). Find max_tr = x[1]+2=4.
    4. Use binary search to see if 4 exists. If yes, put the pivot here and repeat step
    2. If 4 doesn't exist, find the next larger no. and put the pivot there and repeat
    step 2.
    """
    #pivot = 0
    x.sort()
    """
    fullRoadLayout = x[len(x)-1] * [0]
    for i in x:
        fullRoadLayout[i-1] = 1
    #1 has tower, 0 does not(need number +1 for indexing stars a 0 but home address starts at 1)
    """
    """
    #time limit exceeded (Dont know if works as all)
    sz = len(x)

    tot = 0
    i = 0

    while (i < sz):
        fh = x[i]
        ++i
        while ((i < sz) and (fh + k) >= x[i]):
            ++i
        --i
        ++tot
        loc = x[i]
        ++i
        while (i < sz and (loc + k) >= x[i]):
            ++i;
    print(tot)
    """
    start = 0
    i = 0
    towers = 1
    n = len(x)
    while i < n:
        if x[i] <= x[start] + k:
            i = i + 1
            continue
        else:
            s = i-1
            while i < n and x[s] + k >= x[i]:
                i += 1
            start = i
            if i < n:
                towers += 1
    return towers
    #print(fullRoadLayout)


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    k = int(first_multiple_input[1])

    x = list(map(int, input().rstrip().split()))

    result = hackerlandRadioTransmitters(x, k)

    fptr.write(str(result) + '\n')

    fptr.close()
