"""
dot

    The dot tool returns the dot product of two arrays.

        import numpy

        A = numpy.array([ 1, 2 ])
        B = numpy.array([ 3, 4 ])

        print numpy.dot(A, B)       #Output : 11
cross

    The cross tool returns the cross product of two arrays.

        import numpy

        A = numpy.array([ 1, 2 ])
        B = numpy.array([ 3, 4 ])

        print numpy.cross(A, B)     #Output : -2
Task

    You are given two arrays A and B. Both have dimensions of NXN.
    Your task is to compute their matrix product.(https://e/               n.wikipedia.org/wiki/                                                  Matrix_multiplication#Matrix_product_.28two_matrices.29)

Input Format

    The first line contains the integer N.
    The next N lines contains N space separated integers of array A.
    The following N lines contains N space separated integers of array     B.

Output Format

    Print the matrix multiplication of  and .

Sample Input

    2
    1 2
    3 4
    1 2
    3 4
Sample Output

    [[ 7 10]
    [15 22]]
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
import numpy

#input integer n and integer m 
n = int(raw_input())
#inport the array of arrays to manipluate 
ar = numpy.array([raw_input().split() for _ in range(n)], int)
#2 arrays are set both the same size 
ar2 = numpy.array([raw_input().split() for _ in range(n)], int)

print(numpy.dot(ar,ar2))