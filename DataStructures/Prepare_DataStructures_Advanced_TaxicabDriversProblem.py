"""
Burger Town is a city that consists of N special junctions and N-1 pathways. There is
exactly one shortest path between each pair of junctions. Junction i is located at
(x_i,y_i) and the distance between two junctions i,j is defined by the Taxicab geometry.
Tim has recently afforded a taxicab to work as a taxicab driver. His vehicle was very
cheap, but has a very big flaw. It can only drive H units horizontally and V units
vertically before refueling.
If a customer wants to be brought from a junction  to another junction j, then this car
is only capable of driving the route, iff the sum of horizontal distances and the sum of
vertical distances on this path are less than or equal to H and V respectively.
Also, there is a unique path between any two junctions.
    picture.png
Now he has thoughts about returning the vehicle back to the seller. But he first wants
to know, if it's even worth it. That's why he wants to know the number of unordered
pairs (i,j) such that it is not possible to drive a customer from junction i to
junction j.
Input Format
    On the first line you will be given N, H and V separated by a single space.
    Each of the next N lines contains two space separated integers x_i,y_i, denoting the
    location of junction i. Each of the next N-1 lines contains two space separated
    integers describing a path existing between u_i,v_i, i.e., there is a path between
    u_i and v_i.
Output Format
    Output the number of unordered pairs (i,j) such that it is not possible to drive
    from i to j.
Constraints
    2<=N<=10^5
    0<=H,V<=10^14
    0<=x_i, y_i <=20^9
Sample Input
    3 2 1
    0 0
    1 1
    2 0
    1 2
    2 3
Sample Output
    1
Explanation
    The car is only capable of driving H=2 units horizontally and V=1 unit vertically.
    The horizontal distance between junction 1 and 3(via 2) is equal to 2(0->1->2),
    which fits under the horizontal limit of the car. The vertical distance between 1
    and 3 is also equal to 2(0->1->0), but this is not possible for this car since 2>V.
"""

from collections import namedtuple
import bisect
import sys

DistTuple = namedtuple('distance', ['h', 'v'])

def insort_right(arr, dist, hv):
    x_key = dist.h if hv == 'h' else dist.v
    lo = 0
    hi = len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        a_mid = arr[mid].h if hv == 'h' else arr[mid].v
        if x_key < a_mid:
            hi = mid
        else:
            lo = mid + 1
    arr.insert(lo, dist)

def bisect_right(arr, x_key, hv):
    lo = 0
    hi = len(arr)
    while lo < hi:
        mid = (lo + hi) // 2
        a_mid = arr[mid].h if hv == 'h' else arr[mid].v
        if x_key < a_mid:
            hi = mid
        else:
            lo = mid + 1
    return lo

class DistsGroup:
    def __init__(self):
        self.delta_h = 0
        self.delta_v = 0
        dist = DistTuple(0, 0)
        self.dists_h_sorted = [dist]
        self.dists_v_sorted = [dist]

    def append_dist(self, h, v, append=True):
        self.delta_h += h
        self.delta_v += v
        dist = DistTuple(-self.delta_h, -self.delta_v)
        if append:
            insort_right(self.dists_h_sorted, dist, 'h')
            insort_right(self.dists_v_sorted, dist, 'v')
        index_h = bisect_right(self.dists_h_sorted, H_max - self.delta_h, 'h')
        for elem in self.dists_h_sorted[index_h:]:
            self.dists_v_sorted.remove(elem)
        del (self.dists_h_sorted[index_h:])
        index_v = bisect_right(self.dists_v_sorted, V_max - self.delta_v, 'v')
        for elem in self.dists_v_sorted[index_v:]:
            self.dists_h_sorted.remove(elem)
        del (self.dists_v_sorted[index_v:])
        if append:
            paths_count = max(0, len(self.dists_v_sorted) - 1)
            return paths_count

    def append_group(self, other_group, h, v):
        good_cross_paths = 0
        other_group.append_dist(h, v, False)
        dists_h1 = self.dists_h_sorted
        delta_h1 = self.delta_h
        delta_v1 = self.delta_v
        dists_h2 = other_group.dists_h_sorted
        delta_h2 = other_group.delta_h
        delta_v2 = other_group.delta_v
        dists_only_v2 = []
        dist_h2_index = 0
        dist_h2_len = len(dists_h2)
        if len(dists_h1) and len(dists_h2) and dists_h1[-1].h + delta_h1 + dists_h2[-1].h + delta_h2 < H_max and self.dists_v_sorted[-1].v + delta_v1 + other_group.dists_v_sorted[-1].v + delta_v2 < V_max:
            good_cross_paths += len(dists_h1) * len(dists_h2)
        else:
            for dist_h1 in reversed(dists_h1):
                rest_h = H_max - (dist_h1.h + delta_h1)
                rest_v = V_max - (dist_h1.v + delta_v1)
                while dist_h2_index < dist_h2_len:
                    if dists_h2[dist_h2_index].h + delta_h2 <= rest_h:
                        bisect.insort_right(dists_only_v2, dists_h2[dist_h2_index].v + delta_v2)
                        dist_h2_index += 1
                    else:
                        break
                dist_v2_index = bisect.bisect_right(dists_only_v2, rest_v)
                good_cross_paths += dist_v2_index
        for dist_h2 in dists_h2:
            dist_new = DistTuple((dist_h2.h + delta_h2) - delta_h1, (dist_h2.v + delta_v2) - delta_v1)
            self.dists_h_sorted.append(dist_new)
            self.dists_v_sorted.append(dist_new)
        self.dists_h_sorted.sort()
        self.dists_v_sorted.sort(key=lambda k: k.v)
        return good_cross_paths

good_paths = 0

N, H_max, V_max = map(int, sys.stdin.readline().split())
junctions = {}
for i in range(1, N + 1):
    xi, yi = map(int, sys.stdin.readline().rstrip().split())
    junctions[i] = {'x': xi, 'y': yi, 'edges': [], 'dists_group': None}
for i in range(1, N):
    ui, vi = map(int, sys.stdin.readline().rstrip().split())
    dH = abs(junctions[ui]['x'] - junctions[vi]['x'])
    dV = abs(junctions[ui]['y'] - junctions[vi]['y'])
    junctions[ui]['edges'].append({'junction_id': vi, 'dH': dH, 'dV': dV})
    junctions[vi]['edges'].append({'junction_id': ui, 'dH': dH, 'dV': dV})
one_edge_queue = []
for key, value in junctions.items():
    edge_count = len(junctions[key]['edges'])
    junctions[key]['edge_count'] = edge_count
    if edge_count == 1:
        one_edge_queue.append(key)
        junctions[key]['dists_group'] = DistsGroup()
while len(one_edge_queue) > 1:
    junction_id = one_edge_queue[0]
    edge_to_next = junctions[junction_id]['edges'][0]
    next_junction_id = edge_to_next['junction_id']
    if junctions[next_junction_id]['dists_group']:
        paths_added = junctions[next_junction_id]['dists_group'].append_group(junctions[junction_id]['dists_group'], edge_to_next['dH'], edge_to_next['dV'])
        good_paths += paths_added
    else:
        dists_group = junctions[junction_id]['dists_group']
        paths_added = dists_group.append_dist(edge_to_next['dH'], edge_to_next['dV'])
        good_paths += paths_added
        junctions[next_junction_id]['dists_group'] = dists_group
    for edge in junctions[next_junction_id]['edges']:
        if edge['junction_id'] == junction_id:
            junctions[next_junction_id]['edges'].remove(edge)
            break
    if len(junctions[next_junction_id]['edges']) == 1:
        one_edge_queue.append(next_junction_id)
    one_edge_queue.remove(junction_id)
print(int(N * (N - 1) / 2) - good_paths)
