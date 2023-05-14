"""
In this challenge, you will be given an array B and must determine an array A. There is a
special rule: For all i, A[i]<=B[i]. That is, A[i] can be any number you choose such that
1<=A[i]<=B[i]. Your task is to select a series of A[i] given B[i] such that the sum of the
absolute difference of consecutive pairs of A is maximized. This will be the array's cost, and
will be represented by the variable S below.
The equation can be written:
    S = sumation(|A[i] - A[i-1]|) form(i=2 to N)
For example, if the array B=[1,2,3], we know that 1<=A[1]<=1, 1<=A[2]<=2, and 1<=A[3]<=3.
Arrays meeting those guidelines are:
    [1,1,1], [1,1,2], [1,1,3]
    [1,2,1], [1,2,2], [1,2,3]
Our calculations for the arrays are as follows:
    |1-1| + |1-1| = 0    |1-1| + |2-1| = 1    |1-1| + |3-1| = 2
    |2-1| + |1-2| = 2    |2-1| + |2-2| = 1    |2-1| + |3-2| = 2
The maximum value obtained is 2.
Function Description
    Complete the cost function in the editor below. It should return the maximum value that
    can be obtained.
    cost has the following parameter(s):
        * B: an array of integers
Input Format
    The first line contains the integer t, the number of test cases.
    Each of the next t pairs of lines is a test case where:
        - The first line contains an integer n, the length of B
        - The next line contains n space-separated integers B[i]
Constraints
    1<=t<=20
    1<n<=10^5
    1<=B[i]<=100
Output Format
    For each test case, print the maximum sum on a separate line.
Sample Input
    1
    5
    10 1 10 1 10
Sample Output
    36
Explanation
    The maximum sum occurs when A[1]=A[3]=A[5]=10 and A[2]=A[4]=1. That is
    |1-10|+|10-1|+|1-10|+|10-1|=36.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT

def solve(B):

    N = len(B)
    assert 1 <= N <= pow(10,5)
    assert all(1 <= b <= 100 for b in B)

    llen, rlen = 0, 0
    right_pos = B[0]

    for i in range(1,N):

        new_llen = rlen + (right_pos - 1)
        new_right_pos = B[i]
        new_rlen = max(
            llen + (new_right_pos - 1),
            rlen + abs(new_right_pos - right_pos))

        llen, rlen = new_llen, new_rlen
        right_pos = new_right_pos

    return max(llen, rlen)

T = int(input())

for _ in range(T):
    N = int(input())
    B = [ int(X) for X in input().split() ]
    print(solve(B))
