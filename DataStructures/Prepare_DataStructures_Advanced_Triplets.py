"""
There is an integer array d which does not contain more than two elements of the same value.
How many distinct ascending triples (d[i]<d[j]<d[k],i<j<k) are present?
Input format
    The first line contains an integer, N, denoting the number of elements in the array. This
    is followed by a single line, containing N space-separated integers. Please note that
    there are no leading spaces before the first number, and there are no trailing spaces
    after the last number.
Output format:
    A single integer that denotes the number of distinct ascending triplets present in the
    array.
Constraints:
    N<=10^5
    Every element of the array is present at most twice.
    Every element of the array is a 32-bit non-negative integer.
Sample input:
    6
    1 1 2 2 3 4
Sample output:
    4
Explanation
    The distinct triplets are
        (1,2,3)
        (1,2,4)
        (1,3,4)
        (2,3,4)
    The elements of the array might not be sorted. Make no assumptions of the same.
"""

n = int(input())
num = sorted([(int(x), (i + 1)) for i, x in enumerate(input().split())])
m = n + 1
s = [[0] * (m + 1), [0] * (m + 1), [0] * (m + 1), [0] * (m + 1)]
s[0][0] = 1

def Sum(s, n):
    ret = s[0]
    while n > 0:
        ret += s[n]
        n = n ^ (n & (~n + 1))
    return ret

def Update(s, n, v):
    while n <= m:
        s[n] += v
        n += n & (~n + 1)

for i, (n, id) in enumerate(num):
    if i and num[i - 1][0] == num[i][0]:
        continue
    process = [(n, id)]
    if i + 1 < len(num) and num[i][0] == num[i + 1][0]:
        process.append(num[i + 1])
    for state in (3, 2, 1):
        values = []
        for n, id in process:
            values.append(Sum(s[state - 1], id - 1))
        if len(values) > 1: values[1] -= values[0]
        for j, (n, id) in enumerate(process):
            Update(s[state], id, values[j])
print(Sum(s[3], m - 1))
