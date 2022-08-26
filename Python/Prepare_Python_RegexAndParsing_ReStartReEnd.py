#Problem
"""
start() & end()
    These expressions return the indices of the start and end
    of the substring matched by the group.
    Code
        >>> import re
        >>> m = re.search(r'\d+','1234')
        >>> m.end()
        4
        >>> m.start()
        0
Task
    You are given a string S.
    Your task is to find the indices of the start and end of
    string k in S.
Input Format
    The first line contains the string S.
    The second line contains the string k.
Constraints
    0<len(S)<100
    0<len(k)<len(S)
Output Format
    Print the tuple in this format: (start _index, end _index).
    If no match is found, print (-1, -1).
Sample Input
    aaadaa
    aa
Sample Output
    (0, 1)
    (1, 2)
    (4, 5)
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
import re

s, k = input(), input()
matches = list(re.finditer(r'(?={})'.format(k), s))
if matches:
    print('\n'.join(str((match.start(),
          match.start() + len(k) - 1)) for match in matches))
else:
    print('(-1, -1)')
