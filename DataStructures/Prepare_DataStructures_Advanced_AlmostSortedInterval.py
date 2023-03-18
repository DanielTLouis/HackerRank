"""
Shik loves sorted intervals. But currently he does not have enough time to sort all the
numbers. So he decided to use Almost sorted intervals. An Almost sorted interval is a
consecutive subsequence in a sequence which satisfies the following property:
    1. The first number is the smallest.
    2. The last number is the largest.
Please help him count the number of almost sorted intervals in this permutation.
Note: Two intervals are different if at least one of the starting or ending indices are
different.
Input Format
    The first line contains an integer N.
    The second line contains a permutation from 1 to N.
Output Format
    Output the number of almost sorted intervals.
Constraints
    1 ≤ N ≤ 10^6
Sample Input
    5
    3 1 2 5 4
Sample Output
    8
Explanation
    The subsequences [3], [1], [1 2], [1 2 5], [2], [2 5], [5], [4] are almost sorted
    intervals.
"""
import sys

def permute(l):
    l = l[:1] + l[:]
    n = len(l)
    nn = n + 12
    left = [0] * n
    right = [n] * n
    stack = left[:]
    arr = [0] * (nn)
    r = [[] for _ in range(n)]  # create 2d list with deep copy
    # after testcase 6 find left[],right[] take a round 3s
    top = 0
    for i in range(1, n):
        val = l[i]
        while top > 0 and val > l[stack[top - 1]]:
            top -= 1
        if top:
            left[i] = stack[top - 1]
        stack[top] = i
        top += 1
    top = 0
    for i in range(n - 1, 0, -1):
        val = l[i]
        while top > 0 and val < l[stack[top - 1]]:
            top -= 1
        if top:
            right[i] = stack[top - 1]
        stack[top] = i
        top += 1
    # big neck bottle
    ans = 0
    for i in range(n - 1, 0, -1):
        for j in r[i]:
            while j <= nn:
                arr[j] += -1
                j += (j & (-j))
        j = i
        while j <= nn:
            arr[j] += 1
            j += (j & (-j))
        r[left[i]].append(i)
        v = 0
        x = right[i] - 1
        while x > 0:
            v += arr[x]
            x -= (x & (-x))
        ans += v
    return ans

if __name__ == '__main__':
    n = sys.stdin.readline().split()
    l = tuple(map(int, sys.stdin.readline().split()))
    print(permute(l))
