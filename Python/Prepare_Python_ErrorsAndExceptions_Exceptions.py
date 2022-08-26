#problem 
"""
Errors detected during execution are called exceptions.

Examples:

ZeroDivisionError
This error is raised when the second argument of a division or modulo operation is zero.

>>> a = '1'
>>> b = '0'
>>> print int(a) / int(b)
>>> ZeroDivisionError: integer division or modulo by zero
ValueError
This error is raised when a built-in operation or function receives an argument that has the right type but an inappropriate value.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
n = int(raw_input())
#for loop to iterate through number pairs to validate 
for i in range(0, n):
    inp = raw_input()
    a, b = inp.split()
    #check if b is not a number
    if not b.isdigit():
        print("Error Code: invalid literal for int() with base 10: '"+ b + "'")
    #check if a is not a number
    elif not a.isdigit():
        print("Error Code: invalid literal for int() with base 10: '"+ a + "'")
    #check if denominator is 0
    elif int(b) == 0:
        print("Error Code: integer division or modulo by zero")
    #else do the division 
    else:
         a = int(a)
         b = int(b)
         print(a/b)