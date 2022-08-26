#Problem
"""
Polar coordinates are an alternative way of representing Cartesian coordinates or Complex Numbers* .
    * https://en.wikipedia.org/wiki/Complex_number *
A complex number z
    z=x+yj
is completely determined by its real part  and imaginary part y.
Here, j is the imaginary unit**.
    ** https://en.wikipedia.org/wiki/Imaginary_unit **
A polar coordinate (r,Phi) Capture.PNG
is completely determined by modulus  and phase angle Phi.

If we convert complex number z to its polar coordinate, we find:
r : Distance from z to origin, i.e., sqrt(x^2+y^2)
Phi : Counter clockwise angle measured from the positive -axis to the line segment that joins z to the origin.
Python's cmath*** module provides access to the mathematical functions for complex numbers.
    *** https://docs.python.org/2/library/cmath.html ***
cmath.phase
    This tool returns the phase of complex number  (also known
    as the argument of z).
        >>> phase(complex(-1.0, 0.0))
        3.1415926535897931
abs
    This tool returns the modulus (absolute value) of complex
    number z.
        >>> abs(complex(-1.0, 0.0))
        1.0
Task
    You are given a complex . Your task is to convert it to
    polar coordinates.
Input Format
    A single line containing the complex number z. Note:
    complex() function can be used in python to convert the
    input as a complex number.
Constraints
    Given number is a valid complex number
Output Format
    Output two lines:
    The first line should contain the value of r.
    The second line should contain the value of Phi.
Sample Input
    1+2j
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
from cmath import phase
z = input()
print(abs(complex(z)))
print(phase(complex(z)))
