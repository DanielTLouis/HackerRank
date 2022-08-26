#Problem
"""
The defaultdict tool is a container in the collections class
of Python. It's similar to the usual dictionary (dict)
container, but the only difference is that a defaultdict will
have a default value if that key has not been set yet. If you
didn't use a defaultdict you'd have to check to see if that
key exists, and if it doesn't, set it to what you want.
    For example:
        from collections import defaultdict
        d = defaultdict(list)
        d['python'].append("awesome")
        d['something-else'].append("not relevant")
        d['python'].append("language")
        for i in d.items():
            print i
    This prints:
        ('python', ['awesome', 'language'])
        ('something-else', ['not relevant'])
In this challenge, you will be given 2 integers, n and m.
There are n words, which might repeat, in word group A. There
are words belonging to word group B. For each m  words, check
whether the word has appeared in group A or not. Print the
indices of each occurrence of  in group A. If it does not
appear, print -1.
Example
    Group A contains 'a', 'b', 'a' Group B contains 'a', 'c'
    For the first word in group B, 'a', it appears at
    positions 1 and 3 in group A. The second word, 'c', does
    not appear in group A, so print -1.
Expected output:
    1 3
    -1
Input Format
    The first line contains integers,  and  separated by a
    space.
    The next n lines contains the words belonging to group A.
    The next m lines contains the words belonging to group B.
Constraints
    1<=n<=10000
    1<=m<=100
    1<=length of each word in the input<=100
Output Format
    Output m lines.
    The ith line should contain the -indexed positions of the
    occurrences of the ith word separated by spaces.
Sample Input
    STDIN   Function
    -----   --------
    5 2     group A size n = 5, group B size m = 2
    a       group A contains 'a', 'a', 'b', 'a', 'b'
    a
    b
    a
    b
    a       group B contains 'a', 'b'
    b
Sample Output
    1 2 4
    3 5
Explanation
    'a' appeared 3 times in positions 1, 2 and 4.
    'b' appeared 2 times in positions 3 and 5.
    In the sample problem, if 'c' also appeared in word group
    B, you would print -1.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
#Works with python2
from collections import defaultdict
d = defaultdict(list)
list1=[]

n, m = map(int,raw_input().split())

for i in range(0,n):
    d[raw_input()].append(i+1)

for i in range(0,m):
    list1=list1+[raw_input()]

for i in list1:
    if i in d:
        print " ".join( map(str,d[i]) )
    else:
        print -1
"""
#Works but not for large inputs
##Python 3 is breaking something (with how input works)
from collections import defaultdict
n,m = map(int, input().split(' '))
A = defaultdict(list)
B = []
for i in range(0, n):
    A[i].append(input())
for i in range(0, m):
    B.append(input())
found = False
for i in range(0, len(B)):
    found = False
    for j in range(0, len(A)):
        if(A[j][0] == B[i]):
            print(j + 1,"", end="")
            found = True
    if(found == False):
        print(-1)
    print()
"""
