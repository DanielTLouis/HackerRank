"""
Coolguy gives you a simple problem. Given a 1-indexed array, A, containing N elements,
what will ans be after this pseudocode is implemented and executed? Print
ans % (10^9 + 7).
    //f(a, b) is a function that returns the minimum element in interval [a, b]

    ans = 0

    for a -> [1, n]
        for b -> [a, n]
            for c -> [b + 1, n]
                for d -> [c, n]
                    ans = ans + min(f(a, b), f(c, d))
Input Format
    The first line contains N (the size of array A).
    The second line contains N space-separated integers describing A.
Constraints
    1 ≤ N ≤ 2 X 10^5
    1 ≤ A_i ≤ 10^9
Note: A is 1-indexed (i.e.: A={A_1,A_2,...,A_(N-1), A_N}).
Output Format
    Print the integer result of ans % (10^9 + 7).
Sample Input
    3
    3 2 1
Sample Output
    6
Explanation
    min(f(1,1),f(2,2))=2
    min(f(1,1),f(2,3))=1
    min(f(1,1),f(3,3))=1
    min(f(1,2),f(3,3))=1
    min(f(2,2),f(3,3))=1
    We then sum these numbers (2+1+1+1+1=6) and print 6%(10^9 + 7), which is 6.
"""

# Each number is worth its position within the triangle of segments
#    abc
#   ab bc
#  a b b c
# We can calculate the number of comparisons each would have if it was
# the minimum as the nodes that are not parents of children, which ends
# up being triangular numbers
#        (0, 0)
#    (1, 0) (0, 1)
# (2, 0) (1, 1) (0, 2)
# The value of a minimum at any location is the sum of all weights above it
# (plus the size of all other existing triangles)
# so weight(onleft, onright) = weight(L, R) = (L+1)(sum T_[0..R]) + (R+1)(sum T_[0..L])
# The sum of triangular numbers is n*n+1*n+2/6
import sys

N = int(sys.stdin.readline())
A = map(int, sys.stdin.readline().split())
M = (10 ** 9) + 7

def main():
    # Populate lookups
    ord_to_val = {}
    ord_to_ind = {}
    for o, (i, v) in enumerate(sorted(enumerate(A), key = lambda iv: iv[1])):
        ord_to_val[o] = v
        ord_to_ind[o] = i
    # Segments
    segment_inds = [(0, N - 1)]
    # Traverse min to max
    total = 0
    all_tri = tri(N)
    for ordv in range(N):
        ind = ord_to_ind[ordv]
        segment_index = find_segment(ind, segment_inds)
        first, last = segment_inds[segment_index]
        seg_tri = tri(last - first + 1)
        to_left = ind - first
        to_right = last - ind
        ext_tri = all_tri - seg_tri
        weight = worth(to_left, to_right, ext_tri)
        value = (weight * ord_to_val[ordv]) % M
        total = (total + value) % M
        # Prepare for next
        update_segment_inds(segment_inds, segment_index, first, last, ind)
        all_tri = (all_tri - seg_tri + tri(to_left) + tri(to_right)) % M
    return total

def find_segment(ind, segment_inds):
    # If generating this list is expensive, can maintain both lower and lower-upper
    index = bisect_r(segment_inds, ind) - 1
    return index

def bisect_r(vals, val):
    """ From bisect library, adapted to only search lower bound """
    lo = 0
    hi = len(vals)
    while lo < hi:
        mid = (lo + hi) // 2
        if val < vals[mid][0]: hi = mid
        else: lo = mid + 1
    return lo

def update_segment_inds(segment_inds, segment_index, first, last, ind):
    if ind == first:
        new_segments = [(first + 1, last)]
    elif ind == last:
        new_segments = [(first, last - 1)]
    else:
        new_segments = [(first, ind - 1), (ind + 1, last)]
    segment_inds[segment_index:segment_index + 1] = new_segments

def worth(m, n, ext_tri):
    # Divide by 6 before modding to avoid crazy
    n_sum = ((n * (n + 1) * (n + 2)) // 6) % M
    m_sum = ((m * (m + 1) * (m + 2)) // 6) % M
    # Add external triangles for each member
    e_sum = (ext_tri * (n + 1) * (m + 1)) % M
    return ((n + 1) * m_sum + (m + 1) * n_sum + e_sum) % M

def tri(x):
    return ((x * (x + 1)) // 2) % M

if __name__ == '__main__':
    print(main())
