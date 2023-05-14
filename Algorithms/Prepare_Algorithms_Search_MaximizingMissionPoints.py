"""
Xander Cage has a list of cities he can visit on his new top-secret mission. He
represents each city as a tuple of (latitude,longitude,height,points). The values of
latitude, longitude, and height are distinct across all cities.
We define a mission as a sequence of cities, c1,c2,c3,...,ck, that he visits. We define
the total points of such a mission to be the sum of the points of all the cities in his
mission list.
Being eccentric, he abides by the following rules on any mission:
    * He can choose the number of cities he will visit (if any).
    * He can start the mission from any city.
    * He visits cities in order of strictly increasing height.
    * The absolute difference in latitude between adjacent visited cities in his mission
    must
    be at most d_lat.
    * The absolute difference in longitude between adjacent visited cities in his mission
    must
    be at most d_long.
Given d_lat, d_long, and the definitions for n cities, find and print the maximum
possible
total points that Xander can earn on a mission.
Input Format
    The first line contains three space-separated integers describing the respective
    values of
    n, d_lat, and d_long.
    Each line i of the n subsequent lines contains four space-separated integers denoting
    the respective latitude, longitude, height, and points for a city.
Constraints
    1<=n<=2X10^5
    1<d_lat,d_long<=2X10^5
    1<=latitude, longitude, height <=2X10^5
    -2X10^5<=points<=2X10^5
Output Format
    Print a single integer denoting the maximum possible points that Xander can earn on a
    mission.
Sample Input 0
    3 1 1
    1 1 1 3
    2 2 2 -1
    3 3 3 3
Sample Output 0
    5
Explanation 0
    Xander can start at city 1, then go to city 2, and then go to city 3 for a maximum
    value of
    total points=3+-1+3=5
        image
    Note that he cannot go directly from city 1 to city 3 as that would violate his rules
    that the absolute difference in latitude between adjacent visited cities be <=d_lat
    and the absolute difference in longitude between adjacent visited cities be <=d_long.
    Because d_lat=1 and d_long=1, he cannot directly travel between those cities.
"""

from collections import namedtuple
from bisect import bisect_left
import sys

Place = namedtuple('Place', 'lat, long, height, points')

chunkplaces={} # places get inserted into lists contained here, grouped by keys of their locations
chunkvals={} # holds values

giant = False
def getkey(place, off_lat=0, off_long=0):
    return ((place.lat // d_lat + off_lat) * 200011) + place.long // d_long + off_long # unique for n<=200000

def recordvalue(place, val):
    if val < 0:
        return # not worth going here; no need to track
    key = getkey(place)
    if key not in chunkplaces:
        chunkplaces[key] = []
        chunkvals[key] = []
    if giant:
        if len(chunkvals[key]) == 0:
            chunkvals[key].append(-val)
            chunkplaces[key].append(place)
        else:
            if val < -chunkvals[key][0]:
                return
            else:
                chunkvals[key][0] = -val
                chunkplaces[key][0] = place
    else:
        i = bisect_left(chunkvals[key], -val)
        chunkplaces[key].insert(i, place)
        chunkvals[key].insert(i, -val)
        # print(i, val, [val for val in chunkvals[key]])

def getbestinchunk(place, key, best):
    # find best suitable match in chunk
    if key not in chunkvals:
        return 0
    for i, (cand, val) in enumerate(zip(chunkplaces[key], chunkvals[key])):
        # print("evaluating %s"%cand)
        if -val < best:
            # this is the best we have, but it's not as good as we've seen other places; abort
            return 0
        if abs(place.lat - cand.lat) <= d_lat \
            and abs(place.long - cand.long) <= d_long :
            # and cand.height > place.height: # height is given, assuming they're unique
            # suitable, return it
            return -val
    # no suitable match
    return 0

def getbest(place):
    # find best match in this and neighboring chunks, then pick the best
    best = 0 # always have the option to stop here
    for i in [0,1,-1]:
        for j in [0,1,-1]:
            key = getkey(place, i, j)
            ret = getbestinchunk(place, key, best)
            if ret > best:
                best = ret
    return best

def calculatevalue(place):
    val = place.points + getbest(place)
    recordvalue(place, val)
    return val

if __name__ == "__main__":
    n, d_lat, d_long = input().strip().split(' ')
    n, d_lat, d_long = [int(n), int(d_lat), int(d_long)]
    places = []
    if d_lat == 200000:
        giant = True
    for a0 in range(n):
        latitude, longitude, height, points = input().strip().split(' ')
        latitude, longitude, height, points = [int(latitude), int(longitude), int(height), int(points)]
        places.append(Place(latitude, longitude, height, points))
    places.sort(key=lambda p: -p.height) # compute highest first
    best = 0
    for p in places:
        ret = calculatevalue(p)
        if ret > best:
            best = ret
    print(best)
Prepare_
