#Problem
"""
itertools.combinations(iterable, r) *
    * https://docs.python.org/2/library/itertools.html#itertools.combinations *
This tool returns the r length subsequences of elements from the input iterable.
Combinations are emitted in lexicographic sorted order. So, if the input iterable is sorted, the combination tuples will be produced in sorted order.
    Sample Code
        >>> from itertools import combinations
        >>>
        >>> print list(combinations('12345',2))
        [('1', '2'), ('1', '3'), ('1', '4'), ('1', '5'), ('2',
         '3'), ('2', '4'), ('2', '5'), ('3', '4'), ('3', '5'),
          ('4', '5')]
        >>>
        >>> A = [1,1,3,3,3]
        >>> print list(combinations(A,4))
        [(1, 1, 3, 3), (1, 1, 3, 3), (1, 1, 3, 3), (1, 3, 3, 3)
        , (1, 3, 3, 3)]
Task
    You are given a string S.
    Your task is to print all possible combinations, up to
    size k, of the string in lexicographic sorted order.
Input Format
    A single line containing the string S and integer value k
    separated by a space.
Constraints
    0<k<=len(S)
    The string contains only UPPERCASE characters.
Output Format
    Print the different combinations of string S on separate
    lines.
Sample Input
    HACK 2
Sample Output
    A
    C
    H
    K
    AC
    AH
    AK
    CH
    CK
    HK
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
from itertools import combinations
S, k = input().split(' ')
for j in range(1, int(k)+1):
    comb = list(combinations(S, int(j)))
    comb.sort()
    s = []
    for i in range(0, len(comb)):
        s.append(''.join(sorted(comb[i])))
        #print(*comb[i], sep="")
    s.sort()
    for i in range(0, len(s)):
        print(s[i])
