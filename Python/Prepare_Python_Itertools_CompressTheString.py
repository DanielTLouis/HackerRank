#Problem
"""
n this task, we would like for you to appreciate the usefulness
of the groupby() function of itertools . To read more about this
function, Check this out*.
    * https://docs.python.org/2/library/itertools.html#itertools.groupby *
You are given a string S. Suppose a character 'c' occurs
consecutively X times in the string. Replace these consecutive
occurrences of the character 'c' with (X,c) in the string.
For a better understanding of the problem, check the explanation.
Input Format
    A single line of input consisting of the string S.
Output Format
    A single line of output consisting of the modified string.
Constraints
    All the characters of S denote integers between 0 and 9.
    1<=|S|<=10^4
Sample Input
    1222311
Sample Output
    (1, 1) (3, 2) (1, 3) (2, 1)
Explanation
    First, the character 1 occurs only once. It is replaced by
    (1,1). Then the character 2 occurs three times, and it is
    replaced by (3,2) and so on.
    Also, note the single space within each compression and
    between the compressions.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
from itertools import groupby
"""
derefrence pointer with *
create a list[with a tupple inside()]
print the length of the list of the grouped elements
with k as the element
and do so for all k's and c's in groupby(input())
"""
print(*[(len(list(c)), int(k)) for k, c in groupby(input())])
