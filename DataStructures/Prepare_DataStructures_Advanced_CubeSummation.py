"""
Chinese Version * https://hr-testcases.s3.amazonaws.com/1058/1058-chinese.md *
Russian Version ** https://hr-testcases.s3.amazonaws.com/1058/1058_rus.md **
Define a 3-D Matrix in which each block contains 0 initially. The first block is defined by
the coordinates (1,1,1) and the last block is defined by the coordinates (n,n,n). There are
two types of queries.
    UPDATE x y z W
Update the value of block (x,y,z) to W.
    QUERY x1 y1 z1 x2 y2 z2
Calculate the sum of the values of blocks whose x coordinate is between x1 and x2 (inclusive),
y coordinate between y1 and y2 (inclusive) and z coordinate between z1 and z2 (inclusive).
Function Description
    Complete the cubeSum function in the editor below.
    cubeSum has the following parameters: - *int n: the dimensions of the 3-d matrix - string
    operations[m]: the operations to perform
Returns
    - int[]: the results of each QUERY operation
Input Format
    The first line contains an integer T, the number of test-cases. T testcases follow.
    For each test case, the first line contains two space-separated integers, n and m. n
    defines the nXnXn matrix.
    m defines the number of operations.
    The next m lines will contain an operation either of these forms:
        1. UPDATE x y z W
        2. QUERY  x1 y1 z1 x2 y2 z2
Constraints
    1<=T<=50
    1<=n<=100
    1<=m<=1000
    1<=x1<=x2<=n
    1<=y1<=y2<=n
    1<=z1<=z2<=n
    1<=x,y,z<=n
    -10^9 \le W \le 10^9
Sample Input
    2
    4 5
    UPDATE 2 2 2 4
    QUERY 1 1 1 3 3 3
    UPDATE 1 1 1 23
    QUERY 2 2 2 4 4 4
    QUERY 1 1 1 3 3 3
    2 4
    UPDATE 2 2 2 1
    QUERY 1 1 1 1 1 1
    QUERY 1 1 1 2 2 2
    QUERY 2 2 2 2 2 2
Sample Output
    4
    4
    27
    0
    1
    1
Explanation
    In the first test case, there is a cube of 4 * 4 * 4 and there are 5 queries. Initially
    all the cells (1,1,1) to (4,4,4) are 0.
    UPDATE 2 2 2 4 makes the cell (2,2,2) = 4
    QUERY 1 1 1 3 3 3. As (2,2,2) is updated to 4 and the rest are all 0. The answer to this
    query is 4.
    UPDATE 1 1 1 23. updates the cell (1,1,1) to 23. QUERY 2 2 2 4 4 4. Only the cell (1,1,1)
    and (2,2,2) are non-zero and (1,1,1) is not between (2,2,2) and (4,4,4). So, the answer
    is 4.
    QUERY 1 1 1 3 3 3. 2 cells are non-zero and their sum is 23+4 = 27.
"""
import os
import sys

def cubeSum(cmds):
    cube={}
    for i in cmds:
        if(i[0]=="UPDATE"):
            x=cube.get(i[1], dict())
            y=x.get(i[2], dict())
            y[i[3]]=i[4]
            x[i[2]]=y
            cube[i[1]]=x
        else:
            sums=0
            for j in cube:
                if(j>=i[1] and j<=i[4]):
                    for k in cube[j]:
                        if(k>=i[2] and k<=i[5]):
                            for l in cube[j][k]:
                                if(l>=i[3] and l<=i[6]):
                                    sums+=cube[j][k][l]
            print(sums)

if __name__ == '__main__':
    tests=int(input())
    for i in range(tests):
        [N, M]=[int(var) for var in input().split()]
        cmds=[]
        for j in range(M):
            ip=input().split()
            for k in range(1, len(ip)):
                ip[k]=int(ip[k])
            cmds.append(ip)
        cubeSum(cmds)
