"""
Airports are being built on a straight road according to a new
construction plan. For convenience, imagine a number line on
which at different points airports can be positioned. Because a
plane can't take off and start landing immediately, there will
be flight between two airports in locations x and y if and only
if |x-y|>=d, where d is a constant.
Changing the position of an airport from x to y costs |x-y|. The
cost to fix a certain plan is the minimum total cost of changing
the positions of airports. After the changes, it should be
possible to travel between any pair of airports, possibly taking
flights through some intermediate airports. Note that it's
possible that two airports have the same initial position, and
this can be the case after changes too.
On ith day, a plan to build a new airport with position x is
announced. On each day that a new airport is announced, print
the smallest cost to fix the set of airports announced so far.
Note that you should not change the positions of any airports,
just calculate the cost to do it.
    image
Input Format
    Input contains multiple queries.
    The first line consists of an integer q which is the number
    of queries. Each query is given as follows.
    The first line of each query contains two integers n and d,
    the number of days, and the minimum distance respectively.
    The second line of each test case contains n space-separated
    integers x_i denoting the position of the airport that was
    announced on ith day.
Constraints
    3<=n<=2*10^5
    |x_i|<=10^8
    0<=d<=10^8
    the sum of n over all test cases in a file will not
    exceed 2*10^5
Output Format
    Print one line for each query.
    A line for a query with n airports should have n numbers on
    it where the ith one should be the minimum cost to fix
    airports in positions x1,x2,...,xi.
Sample Input 0
    1
    3 1
    0 0 0
Sample Output 0
    0 1 1
Explanation 0
    The answer for a single airport is always zero. When we have
    many airports in the same position, it's enough to move only
    one of them to satisfy the condition from the statement.
Sample Input 1
    1
    5 4
    1 -1 2 -1 1
Sample Output 1
    0 2 2 3 3
Explanation 1
    image
    For each new day that an airport is inserted, the cheapest
    rearranging of existing airports is shown on the diagram
    above. Note that cost changes for every day and travelling
    between airports can be done possibly flying through some
    intermediate ones. Costs are calculated without changing
    actual positions of the airports.
"""

#!/bin/python3

import math
import os
import random
import re
import sys
from heapq import heappop, heappush, heapify

#
# Complete the 'airports' function below.
#
# The function is expected to return an INTEGER_ARRAY.
# The function accepts following parameters:
#  1. INTEGER d
#  2. INTEGER_ARRAY x
#


def airports(min_dist, airports):
    road = sorted(set(airports))
    len_road = len(road)
    answers = []
    airport_indices = dict()
    for i, a in enumerate(road):
        airport_indices[a] = i
    qty = [0] * len_road
    for a in airports:
        qty[airport_indices[a]] += 1
    safe = []
    near_left = []
    near_right = []
    near_both = []
    for i in range(len_road - 1):
        gap = (i, i + 1)
        safe.append(gap)
    heapify(near_left)
    heapify(near_right)
    heapify(near_both)
    left_airport = 0
    right_airport = len_road - 1
    second_left = 1
    second_right = len_road - 2
    next_airport = list(range(1, len_road)) + ['N']
    prev_airport = ['N'] + list(range(len_road - 1))
    for ap in reversed(airports):
        road_left_airport, road_right_airport = road[left_airport], road[right_airport]
        while safe and (road[safe[-1][1]] - road_left_airport < min_dist or road_right_airport - road[safe[-1][0]] < min_dist):
            gap = safe.pop()
            if road[gap[1]] - road_left_airport < min_dist:
                heappush(near_left,(0 - road[gap[1]],gap))
            else:
                heappush(near_right,(road[gap[0]],gap))
        while near_left and road_right_airport - road[near_left[0][1][0]] < min_dist:
            gap = heappop(near_left)[1]
            heappush(near_both,(road[gap[0]] - road[gap[1]], gap))
        while near_right and road[near_right[0][1][1]] - road_left_airport < min_dist:
            gap = heappop(near_right)[1]
            heappush(near_both,(road[gap[0]] - road[gap[1]], gap))
        while near_both and (near_both[0][1][0] < left_airport or near_both[0][1][1] > right_airport):
            heappop(near_both)
        if safe:
            answers.append(0)
        else:
            possible_answers = [min_dist]
            if left_airport != right_airport:
                if qty[left_airport] == 1:
                    possible_answers.append(min_dist + road_left_airport - road[second_left])
                if qty[right_airport] == 1:
                    possible_answers.append(min_dist + road[second_right] - road_right_airport)
            if near_left:
                possible_answers.append(max(0, min_dist + road_left_airport - road[near_left[0][1][1]]))
            if near_right:
                possible_answers.append(max(0, min_dist + road[near_right[0][1][0]] - road_right_airport))
            if near_both:
                possible_answers.append(0)
                nb = near_both[0][1]
                possible_answers[-1] += max(0,min_dist + road_left_airport - road[nb[1]])
                possible_answers[-1] += max(0,min_dist + road[nb[0]] - road_right_airport)
            answers.append(min(possible_answers))
        ai = airport_indices[ap]
        qty[ai] -= 1
        if qty[ai]:
            continue
        while second_left < len_road - 1 and qty[second_left] == 0:
            second_left += 1
        while second_right > 0 and qty[second_right] == 0:
            second_right -= 1
        if ai == left_airport or ai == right_airport:
            while left_airport < len_road - 1 and qty[left_airport] == 0:
                left_airport += 1
            while right_airport > 0 and qty[right_airport] == 0:
                right_airport -= 1
            second_left = max(second_left, left_airport + 1)
            second_right = min(second_right, right_airport - 1)
            while second_left < len_road - 1 and qty[second_left] == 0:
                second_left += 1
            while second_right > 0 and qty[second_right] == 0:
                second_right -= 1
        else:
            l = prev_airport[ai]
            r = next_airport[ai]
            next_airport[l] = r
            prev_airport[r] = l
            gap = (l, r)
            safe.append(gap)
    answers.reverse()
    answers[0] = 0
    return answers

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')
    q = int(input().strip())
    for q_itr in range(q):
        first_multiple_input = input().rstrip().split()
        n = int(first_multiple_input[0])
        d = int(first_multiple_input[1])
        x = list(map(int, input().rstrip().split()))
        result = airports(d, x)
        fptr.write(' '.join(map(str, result)))
        fptr.write('\n')
    fptr.close()
