"""
mean

    The mean tool computes the arithmetic mean along the specified         axis.

        import numpy

        my_array = numpy.array([ [1, 2], [3, 4] ])

        print numpy.mean(my_array, axis = 0)        #Output : [ 2.  3.]
        print numpy.mean(my_array, axis = 1)        #Output : [ 1.5            3.5]
        print numpy.mean(my_array, axis = None)     #Output : 2.5
        print numpy.mean(my_array)                  #Output : 2.5
    By default, the axis is None. Therefore, it computes the mean of       the flattened array.

var

    The var tool computes the arithmetic variance along the specified      axis.

        import numpy

        my_array = numpy.array([ [1, 2], [3, 4] ])

        print numpy.var(my_array, axis = 0)         #Output : [ 1.  1.]
        print numpy.var(my_array, axis = 1)         #Output : [ 0.25           0.25]
        print numpy.var(my_array, axis = None)      #Output : 1.25
        print numpy.var(my_array)                   #Output : 1.25
    By default, the axis is None. Therefore, it computes the variance      of the flattened array.

std

    The std tool computes the arithmetic standard deviation along the      specified axis.

        import numpy

        my_array = numpy.array([ [1, 2], [3, 4] ])

        print numpy.std(my_array, axis = 0)         #Output : [ 1.  1.]
        print numpy.std(my_array, axis = 1)         #Output : [ 0.5            0.5]
        print numpy.std(my_array, axis = None)      #Output :                  1.11803398875
        print numpy.std(my_array)                   #Output :                  1.11803398875
    By default, the axis is None. Therefore, it computes the standard      deviation of the flattened array.

Task

    You are given a 2-D array of size NXM.
    Your task is to find:

    The mean along axis 1
    The var along axis 0
    The std along axis None
Input Format

    The first line contains the space separated values of N and M.
    The next N lines contains M space separated integers.

Output Format

    First, print the mean.
    Second, print the var.
    Third, print the std.

Sample Input

    2 2
    1 2
    3 4
Sample Output

    [ 1.5  3.5]
    [ 1.  1.]
    1.11803398875
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
import numpy
#output for problem is set to legacy output so needs to be set 
##numpy.set_printoptions(legacy='1.13')
##numpy.set_printoptions(sign=' ')
###these still did not work

#input integer n and integer m 
n, m = map(int,raw_input().split())
#inport the array of arrays to manipluate 
ar = numpy.array([raw_input().split() for _ in range(n)], int)

print numpy.mean(ar,axis = 1) 
print numpy.var(ar,axis = 0)
#print numpy.std(ar,axis = None)
##use numpy aroudn to fix the rounding 
print numpy.around(numpy.std(ar, axis = None), decimals=11)
