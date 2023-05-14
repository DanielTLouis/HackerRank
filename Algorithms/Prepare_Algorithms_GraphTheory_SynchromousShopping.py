"""
Bitville is a seaside city that has a number of shopping centers connected by bidirectional
roads, each of which has a travel time associated with it. Each of the shopping centers may
have a fishmonger who sells one or more kinds of fish. Two cats, Big Cat and Little Cat, are
at shopping center 1 (each of the centers is numbered consecutively from 1 to n). They have a
list of fish they want to purchase, and to save time, they will divide the list between them.
Determine the total travel time for the cats to purchase all of the types of fish, finally
meeting at shopping center n. Their paths may intersect, they may backtrack through shopping
center n, and one may arrive at a different time than the other. The minimum time to determine
is when both have arrived at the destination.
For example, there are n=5 shopping centers selling k=3 types of fish. The following is a
graph that shows a possible layout of the shopping centers connected by m=4 paths. Each of the
centers is labeled center number / fish types offered/cat(s) that visit(s). Here B and L
represent Big Cat and Little Cat, respectively. In this example, both cats take the same path,
i.e. 1->3->5 and arrive at time 15+5=20 having purchased all three types of fish they want.
Neither cat visits shopping centers 2 or 4.
    image
Function Description
    Complete the shop function in the editor below. It should return an integer that
    represents the minimum time required for their shopping.
    shop has the following parameters:
    - n: an integer, the number of shopping centers
    - k: an integer, the number of types of fish
    - centers: an array of strings of space-separated integers where the first integer of each
    element is the number of types of fish sold at a center and the remainder are the types
    sold
    - roads: a 2-dimensional array of integers where the first two values are the shopping
    centers connected by the bi-directional road, and the third is the travel time for that
    road
Input Format
    The first line contains 3 space-separated integers: n (the number of shopping centers), m
    (the number of roads), and k (the number of types of fish sold in Bitville), respectively.
    Each line i of the n subsequent lines (1<=i<=n) describes a shopping center as a line of
    space-separated integers. Each line takes the following form:
        * The first integer, t[i], denotes the number of types of fish that are sold by the
        fishmonger at the ith shopping center.
        * Each of the t[i] subsequent integers on the line describes a type of fish sold by
        that fishmonger, denoted by A[i][z], where 1<=z<=t[i] going forward.
    Each line j of the m subsequent lines (1<=j<=m) contains 3 space-separated integers that
    describe a road. The first two integers, u[j] and v[j], describe the two shopping centers
    it connects. The third integer, w[j], denotes the amount of time it takes to travel the
    road.
Constraints
    2<=n<=10^3
    1<=m<=2X10^3
    1<=k<=10
    0<=t[i]<=k
    1<=A[i][z]<=k
    * All A[i][z] are different for every fixed .
    1<=u[j],v[j]<=N
    1<=w[j]<=10^4
    * Each road connectes 2 distinct shopping centers (i.e., no road connects a shopping
    center to itself).
    * Each pair of shopping centers is directly connected by no more than 1 road.
    * It is possible to get to any shopping center from any other shopping center.
    * Each type of fish is always sold by at least one fishmonger.
Output Format
    Print the minimum amount of time it will take for the cats to collectively purchase all k
    fish and meet up at shopping center n.
Sample Input
    5 5 5
    1 1
    1 2
    1 3
    1 4
    1 5
    1 2 10
    1 3 10
    2 4 10
    3 5 10
    4 5 10
Sample Output
    30
Explanation
        image
    B represents a location Big Cat visits, L represents a location where Little Cat visits.
    Big Cat can travel 1->2->4->5 and buy fish at all of the shopping centers on his way.
    Little Cat can then travel 1->3->5, and buy fish from the fishmonger at the 3rd shopping
    center only.
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'shop' function below.
#
# The function is expected to return an INTEGER.
# The function accepts following parameters:
#  1. INTEGER n
#  2. INTEGER k
#  3. STRING_ARRAY centers
#  4. 2D_INTEGER_ARRAY roads
#

from collections import deque

import heapq


def shop(n, k, centers, roads):

    # Write your code here
    fish_masks = [0]
    all_fishes_mask = 2 ** k - 1
    f = 1
    for _ in range(k):
        fish_masks.append(f)
        f <<= 1

    cities = [0] * (n + 1)
    for idx, c_str in enumerate(centers):
        c_data = list(map(int, c_str.split()))
        if c_data[0] > 0:
            cities[idx + 1] = sum([fish_masks[i] for i in c_data[1:]])

    neighbours = [[] for _ in range(n+1)]
    times = [[0] * (n+1) for _ in range(n+1)]
    for c1, c2, t in roads:
        neighbours[c1].append(c2)
        neighbours[c2].append(c1)
        times[c1][c2] = t
        times[c2][c1] = t

    q = [(1 << 10) + cities[1]]
    seen = [[False] * (all_fishes_mask + 1) for _ in range(n + 1)]
    trip_time = [[None] * (all_fishes_mask + 1) for _ in range(n + 1)]

    fish_mask = 2 ** 10 - 1
    node_mask = fish_mask << 10

    while q:
        data = heapq.heappop(q)
        time = data >> 20
        node = (data & node_mask) >> 10
        f_mask = data & fish_mask
        if seen[node][f_mask]:
            continue
        seen[node][f_mask] = True
        if (node == n) and (f_mask == all_fishes_mask):
            continue
        for nxt in neighbours[node]:
            nxt_mew_mask = cities[nxt] | f_mask
            if seen[nxt][nxt_mew_mask]:
                continue
            nxt_cur_time = trip_time[nxt][nxt_mew_mask]
            nxt_new_time = time + times[node][nxt]
            if (nxt_cur_time is not None) and (nxt_new_time >= nxt_cur_time):
                continue
            trip_time[nxt][nxt_mew_mask] = nxt_new_time
            heapq.heappush(q, (nxt_new_time << 20) + (nxt << 10) + nxt_mew_mask)

    rv = 0
    trip_times = trip_time[n]
    for mask_i, time_i in enumerate(trip_times):
        if not time_i:
            continue
        for data_j, time_j in enumerate(trip_times[mask_i:]):
            if not time_j:
                continue
            mask_j = mask_i + data_j
            mask = mask_i | mask_j
            t_time = max(time_i, time_j)
            if mask != all_fishes_mask:
                continue
            if rv and t_time >= rv:
                continue
            rv = t_time
    return rv


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    first_multiple_input = input().rstrip().split()

    n = int(first_multiple_input[0])

    m = int(first_multiple_input[1])

    k = int(first_multiple_input[2])

    centers = []

    for _ in range(n):
        centers_item = input()
        centers.append(centers_item)

    roads = []

    for _ in range(m):
        roads.append(list(map(int, input().rstrip().split())))

    res = shop(n, k, centers, roads)

    fptr.write(str(res) + '\n')

    fptr.close()
