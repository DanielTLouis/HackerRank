"""
A border of a string is a proper prefix of it that is also a suffix. For example:
    * a and abra are borders of abracadabra,
    * kan and kankan are borders of kankankan.
    * de is a border of decode.
Note that decode is not a border of decode because it's not proper.
A palindromic border is a border that is palindromic. For example,
    * a and ana are palindromic borders of anabanana,
    * l, lol and lolol are palindromic borders of lololol.
Let's define P(s) as the number of palindromic borders of string . For example, if  lololol,
then P(s)=3.
Now, a string of length N has exactly N(N+1)/2 non-empty substrings (we count substrings as
distinct if they are of different lengths or are in different positions, even if they are the
same string). Given a string s, consisting only of the first 8 lowercase letters of the
English alphabet, your task is to find the sum of P(s') for all the non-empty substrings s' of
s. In other words, you need to find:
    sumation(P(i...j))for(1<=i<=j<=N)
where  is the substring of  starting at position  and ending at position .
Since the answer can be very large, output the answer modulo .
Input Format
    The first line contains a string consisting of N characters.
Output Format
    Print a single integer: the remainder of the division of the resulting number by 10^9 + 7.
Constraints
    1<=N<=10^5
    All characters in the string can be any of the first 8 lowercase letters of the English
    alphabet (abcdefgh).
Sample Input 1
    ababa
Sample Output 1
    5
Sample Input 2
    aaaa
Sample Output 2
    10
Sample Input 3
    abcacb
Sample Output 3
    3
Explanation
    s=ababa has 15 substrings but only 4 substrings have palindromic borders.
    s_1..3=aba->P(s_1..3)=1
    s_1...5=ababa->P(s_1...5)=2
    s_2...4=bab->P(s_2...4)=1
    s_3...5=aba->P(s_3..5)=1
"""
def mod(x):
    return x % 1000000007

class trie(object):
    def __init__(self, depth=0, parent=None, data=None):
        self.count = 0
        self.depth = depth
        self.parent = parent
        self.data = data
        self.next = {}

    def get(self, char):
        if char in self.next:
            return self.next[char]
        ans = trie(self.depth + 2, self, char)
        self.next[char] = ans
        return ans

    def children(self):
        return self.next.values()

def dfs(node):
    ans = 0
    stack = []
    stack.append((node, True))
    while len(stack) > 0:
        node, extend = stack.pop()
        if extend:
            stack.append((node, False))
            for child in node.children():
                stack.append((child, True))
        else:
            for child in node.children():
                node.count += child.count
            if node.depth > 0:
                ans = mod(ans + mod(node.count * (node.count - 1) // 2))
    return ans

def pr(node):
    print(' ' * node.depth + '%s (%d:%d)' % (chr(node.data) if node.data else ' ', node.depth, node.count))
    for child in node.children():
        pr(child)

def score(string):
    # ascii values
    string = list(map(ord, string))
    N = len(string)*2 + 1
    c = [0] * N
    c[1::2] = string
    # initialize trie pointers
    odd = trie(depth = -1)
    even = trie()
    center, radius = 0, 0
    left, right = 0, 0
    # manacher's algorithm
    node = [even]
    span = [0]
    for i in range(1, N):
        if i > radius:
            node.append(odd.get(c[i]) if (i & 1) else even)
            span.append(0)
            left = i - 1
            right = i + 1
        else:
            mirror = center * 2 - i
            if span[mirror] < radius - i:
                span.append(span[mirror])
                node.append(node[mirror])
                left = -1
            else:
                span.append(radius - i)
                node.append(node[mirror])
                while node[i].depth > radius - i:
                    node[i] = node[i].parent
                right = radius + 1
                left = i * 2 - right
        while left >= 0 and right < N and c[left] == c[right]:
            if c[right]:
                node[i] = node[i].get(c[right])
            span[i] += 1
            left -= 1
            right += 1
        node[i].count += 1
        if i + span[i] > radius:
            center = i
            radius = i + span[i]
    # accumulate count
    return mod(dfs(odd) + dfs(even))

print(score(str(input())))
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'palindromicBorder' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING s as parameter.
#
#Time Limite Exceeded
def testPan(s):
    for i in range(0, len(s)):
        if(s[i] != s[len(s)-1-i]):
            return False
    return True
def palindromicBorder(s):
    # Write your code here
    numOfPan = 0
    stringFront = ''
    stringBack = ''
    length = len(s)
    #get num of substrings:
    for i in range(0, length+1):
        for j in range(i+1, length+1):
            sub = s[i : j]
            sublength = len(sub)
            if(sublength <= 1):
                continue
            else:
                print("next sub:", sub)
                for k in range(0, sublength):
                    for l in range(k+1, sublength):
                        stringFront = sub[k:l]
                        stringBack = sub[sublength-l: sublength]
                        if(stringFront == stringBack):
                            if(testPan(stringFront)):
                                print(stringFront, sub, stringBack)
                                numOfPan += 1
    return numOfPan

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    s = input()

    result = palindromicBorder(s)

    fptr.write(str(result) + '\n')

    fptr.close()
"""
