#Problem
"""
any()
* https://docs.python.org/2/library/functions.html#any *
This expression returns True if any element of the iterable is true.
If the iterable is empty, it will return False.
    Code
        >>> any([1>0,1==0,1<0])
        True
        >>> any([1<0,2<1,3<2])
        False
all()
** https://docs.python.org/2/library/functions.html#all **
This expression returns True if all of the elements of the iterable are true. If the iterable is empty, it will return True.
    Code
        >>> all(['a'<'b','b'<'c'])
        True
        >>> all(['a'<'b','c'<'b'])
        False
Task
    You are given a space separated list of integers. If all
    the integers are positive, then you need to check if any
    integer is a palindromic integer***.
    *** https://en.wikipedia.org/wiki/Palindromic_number ***
Input Format
    The first line contains an integer N. N is the total
    number of integers in the list.
    The second line contains the space separated list of N
    integers.
Constraints
    0<N<100
Output Format
    Print True if all the conditions of the problem statement
    are satisfied. Otherwise, print False.
Sample Input
    5
    12 9 61 5 14
Sample Output
    True
Explanation
    Condition 1: All the integers in the list are positive.
    Condition 2: 5 is a palindromic integer.
    Hence, the output is True.
    Can you solve this challenge in 3 lines of code or less?
    There is no penalty for solutions that are correct but
    have more than 3 lines.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
def isPan(num):
    s = str(num)
    for i in range(0,len(s)):
        if(s[i] != s[len(s) - i - 1]):
            return False
    return True

N = int(input())
A = list(map(int, input().split(' ')))
if(all(i > 0 for i in A)):
    if(any(isPan(i) for i in A)):
        print(True)
    else:
        print(False)
else:
    print(False)  
