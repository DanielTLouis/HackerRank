"""
Given an array of integers, you must answer a number of queries. Each query consists of a single
integer, x, and is performed as follows:

    1.Add x to each element of the array, permanently modifying it for any future queries.
    2.Find the absolute value of each element in the array and print the sum of the absolute
    values on a new line.
Tip: The Input/Output for this challenge is very large, so you'll have to be creative in your
approach to pass all test cases.
Function Description
    Complete the playingWithNumbers function in the editor below. It should return an array of
    integers that represent the responses to each query.
    playingWithNumbers has the following parameter(s):
        * arr: an array of integers
        * queries: an array of integers
Input Format
    The first line contains an integer n the number of elements in arr.
    The second line contains n space-separated integers arr[i].
    The third line contains an integer q, the number of queries.
    The fourth line contains q space-separated integers x where queries[j]=x.
Constraints
    1<=n<=5X10^5
    1<=q<=5X10^5
    -2000<=arr[i]<=2000, where 0<=i<n.
    -2000<queries[j]<=2000, where 0<=j<q
Output Format
    For each query, print the sum of the absolute values of all the array's elements on a new line.
Sample Input
    3
    -1 2 -3
    3
    1 -2 3
Sample Output
    5
    7
    6
Explanation
    Query 0: x=1
    Array: [-1,2,-3]->[0,3,-2]
    The sum of the absolute values of the updated array's elements is |0|+|3|+|-2|=0+3+2=5.
    Query 1: x=-2
    Array: [0,3,-2]->[-2,1,-4]
    The sum of the absolute values of the updated array's elements is |-2|+|1|+|-4|=2+1+4=7.
    Query 2: x=3
    Array: [-2,1,-4]->[1,4,-1]
    The sum of the absolute values of the updated array's elements is |1|+|4|+|-1|=1+4+1=6.
"""
n = int(input())
arr = list(map(int, input().split()))

q = int(input())
queries = list(map(int, input().split()))

count = [0]*4001
for i in arr:
    count[2000 + i] += 1

sum_num_right = []
sum_num_right.append(n)
for i in range(4000):
    sum_num_right.append(sum_num_right[i] - count[i])

sum_right = [0]*4001
for i in range(4001):
    sum_right[0] += count[i] * i

for i in range(1,4001):
    sum_right[i] = sum_right[i - 1] - sum_num_right[i]

sum_left = [0]*4001
for i in range(4000, -1, -1):
    sum_left[4000] += count[i] * (4000 - i)

for i in range(3999, -1, -1):
    sum_left[i] = sum_left[i + 1] - (n - sum_num_right[i + 1])

acc = 0
for i in queries:
    acc += i
    mid = 2000 - acc
    if mid < 4001 and mid >= 0:
        print(sum_right[mid] + sum_left[mid])
    elif mid < 0:
        print(sum_right[0] + n * abs(mid))
    else:
        print(sum_left[4000] + n * (mid - 4000))
