#Problem
"""
Mr. Vincent works in a door mat manufacturing company. One day,
he designed a new door mat with the following specifications:
    -Mat size must be NXM. (N is an odd natural number, and M
    is 3 times N.)
    -The design should have 'WELCOME' written in the center.
    -The design pattern should only use |, . and - characters.
Sample Designs
    Size: 7 x 21
    ---------.|.---------
    ------.|..|..|.------
    ---.|..|..|..|..|.---
    -------WELCOME-------
    ---.|..|..|..|..|.---
    ------.|..|..|.------
    ---------.|.---------

    Size: 11 x 33
    ---------------.|.---------------
    ------------.|..|..|.------------
    ---------.|..|..|..|..|.---------
    ------.|..|..|..|..|..|..|.------
    ---.|..|..|..|..|..|..|..|..|.---
    -------------WELCOME-------------
    ---.|..|..|..|..|..|..|..|..|.---
    ------.|..|..|..|..|..|..|.------
    ---------.|..|..|..|..|.---------
    ------------.|..|..|.------------
    ---------------.|.---------------
Input Format
    A single line containing the space separated values of N
    and M.
Constraints
    5<N<101
    15<M<303
Output Format
    Output the design pattern.
Sample Input
    9 27
Sample Output
    ------------.|.------------
    ---------.|..|..|.---------
    ------.|..|..|..|..|.------
    ---.|..|..|..|..|..|..|.---
    ----------WELCOME----------
    ---.|..|..|..|..|..|..|.---
    ------.|..|..|..|..|.------
    ---------.|..|..|.---------
    ------------.|.------------
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
n, m = input().split(" ")
n = int(n)
m = int(m)
j = 1
for i in range(1, n+1):
    if(i <= int(n /2)):
        print("-"*(int(m/2 - (j*3)/2)) + ".|."*(j) + "-"*((int(m/2 - (j*3)/2))))
        j += 2
    elif(i == int(n/2)+1):
        print("-"*(int(m/2) - 3) + "WELCOME" + "-"*(int(m/2) - 3))
        j -= 2
    else:
        print("-"*(int(m/2 - (j*3)/2))  + ".|."*(j) + "-"*(int(m/2 - (j*3)/2)) )
        j -= 2 
