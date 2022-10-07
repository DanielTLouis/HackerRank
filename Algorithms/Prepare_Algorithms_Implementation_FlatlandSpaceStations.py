"""
Flatland is a country with a number of cities, some of which
have space stations. Cities are numbered consecutively and
each has a road of 1km length connecting it to the next city.
It is not a circular route, so the first city doesn't connect
with the last city. Determine the maximum distance from any
city to its nearest space station.
Example
    n=3
    c=[1]
    There are n=3 cities and city 1 has a space station. They
    occur consecutively along a route. City 0 is 1-0=1 unit
    away and city 2 is 2-1=1 units away. City 1 is 0 units
    from its nearest space station as one is located there.
    The maximum distance is 1.
Function Description
    Complete the flatlandSpaceStations function in the editor
    below.
    flatlandSpaceStations has the following parameter(s):
        int n: the number of cities
        int c[m]: the indices of cities with a space station
Returns
    - int: the maximum distance any city is from a space
    station
Input Format
    The first line consists of two space-separated integers,
    n and m.
    The second line contains m space-separated integers, the
    indices of each city that has a space-station. These
    values are unordered and distinct.
Constraints
    1<=n<=10^5
    1<=m<=n
    There will be at least i city with a space station.
    No city has more than one space station.
Output Format
Sample Input 0
    STDIN   Function
    -----   --------
    5 2     n = 5, c[] size m = 2
    0 4     c = [0, 4]
Sample Output 0
    2
Explanation 0
    This sample corresponds to following graphic:
        hreasy(5).png
    The distance to the nearest space station for each city is
    listed below:
       -c[0] has distance 0km, as it contains a space station.
       -c[1] has distance 1km to the space station in c[0].
       -c[2] has distance 2k to the space stations in c[0]
       and c[4].
       -c[3] has distance 1km to the space station in c[4].
       -c[4] has distance 0km, as it contains a space station.
    We then take max(0,1,2,1,0)=2.
Sample Input 1
    6 6
    0 1 2 4 3 5
Sample Output 1
    0
Explanation 1
    In this sample, n=m so every city has space station and we
    print 0 as our answer.
"""

#!/bin/python3

import math
import os
import random
import re
import sys
def minD(i,c):
    minD = 99999999
    for j in c:
        if(abs(i-j) < minD):
            minD = abs(i-j)
    return minD
# Complete the flatlandSpaceStations function below.
def flatlandSpaceStations(n, c):
    d = []
    c.sort(reverse = True)
    max_distance = 0
    for iC, aC in enumerate(c[:-1]):
        current_distance = (aC - c[iC+1])//2
        max_distance = max(max_distance, current_distance)
    # max in span
    d.append(max_distance)
    # left end
    d.append(0 if c[0]==n-1 else n-1 - c[0])
    # right end
    d.append(0 if c[-1]==0 else c[-1] - 0)

    return max(d)
    """
    #to slow for one case
    mindistances = []
    for i in range(n):
        mindis = minD(i, c)
        mindistances.append(mindis)
    return max(mindistances)
    """
if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    nm = input().split()

    n = int(nm[0])

    m = int(nm[1])

    c = list(map(int, input().rstrip().split()))

    result = flatlandSpaceStations(n, c)

    fptr.write(str(result) + '\n')

    fptr.close()
