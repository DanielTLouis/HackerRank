#Problem
"""
ABC is a right triangle, 90 at B.
Therefore, Angle(ABC) = 90.
Point M is the midpoint of hypotenuse AC.
You are given the lengths AB and BC.
Your task is to find  Andgle(MBC)(angle theta, as shown in the figure) in degrees.
Input Format
    The first line contains the length of side AB.
    The second line contains the length of side BC.
Constraints
    0<AB<=100
    0<BC<=100
    Lengths AB and BC are natural numbers.
Output Format
    Output Angle(MBC) in degrees.
    Note: Round the angle to the nearest integer.
Examples:
    If angle is 56.5000001°, then output 57°.
    If angle is 56.5000000°, then output 57°.
    If angle is 56.4999999°, then output 56°.
    0<Thata<90
Sample Input
    10
    10
Sample Output
    45°
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
import math
AB = int(input())
BC = int(input())
AC = math.sqrt(AB**2 + BC**2)
m = AC / 2
adj = BC / 2
print(str(int(round(math.degrees(math.acos(adj/m)))))+"\N{DEGREE SIGN}")
