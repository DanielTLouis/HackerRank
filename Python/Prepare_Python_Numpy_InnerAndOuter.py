"""
inner

    The inner tool returns the inner product of two arrays.

        import numpy

        A = numpy.array([0, 1])
        B = numpy.array([3, 4])

        print numpy.inner(A, B)     #Output : 4
outer

    The outer tool returns the outer product of two arrays.

        import numpy

        A = numpy.array([0, 1])
        B = numpy.array([3, 4])

        print numpy.outer(A, B)     #Output : [[0 0]
                                    #          [3 4]]
Task

    You are given two arrays: A and B.
    Your task is to compute their inner and outer product.

Input Format

    The first line contains the space separated elements of array A.
    The second line contains the space separated elements of array B.

Output Format

    First, print the inner product.
    Second, print the outer product.

Sample Input

    0 1
    2 3
Sample Output

    3
    [[0 0]
    [2 3]]
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
import numpy

#input integer n and integer m 
#inport the array of arrays to manipluate 
ar = numpy.array([raw_input().split() for _ in range(2)], int)

print numpy.inner(ar[0],ar[1])
print numpy.outer(ar[0],ar[1])