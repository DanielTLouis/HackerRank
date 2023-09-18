"""
Prof. Twotwo as the name suggests is very fond powers of 2. Moreover he also has special affinity
to number 800. He is known for carrying quirky experiments on powers of 2.
One day he played a game in his class. He brought some number plates on each of which a digit from
0 to 9 is written. He made students stand in a row and gave a number plate to each of the student.
Now turn by turn, he called for some students who are standing continuously in the row say from
index i to index j (i<=j) and asked them to find their strength.
The strength of the group of students from i to j is defined as:
    strength(i , j)
    {
        if a[i] = 0
            return 0; //If first child has value 0 in the group, strength of group is zero
        value = 0;
        for k from i to j
            value = value*10 + a[k]
        return value;
    }
Prof called for all possible combinations of i and j and noted down the strength of each group.
Now being interested in powers of 2, he wants to find out how many strengths are powers of two.
Now its your responsibility to get the answer for prof.
Input Format
    First line contains number of test cases T
    Next T line contains the numbers of number plates the students were having when standing in
    the row in the form of a string A.
Constraints
    1 ≤ T ≤ 100
    1 ≤ len(A) ≤ 105
    0 ≤ A[i] ≤ 9
Output Format
    Output the total number of strengths of the form 2x such that 0 ≤ x ≤ 800.
Sample Input 0
    5
    2222222
    24256
    65536
    023223
    33579
Sample Output 0
    7
    4
    1
    4
    0
Explanation 0
    In following explanations group i-j is group of student from index i to index j
    (1-based indexing)
        In first case only 2 is of form power of two. It is present seven times for groups 1-1,2-2,
        3-3,4-4,5-5,6-6,7-7
        In second case 2,4 and 256 are of required form. 2 is strength of group 1-1 and 3-3, 4 is
        strength of group 2-2 and 256 is strength of group 3-5.
        In third case 65536 is only number in required form. It is strength of group 1-5
        In fourth case 2 and 32 are of forms power of 2. Group 1-2 has values 0,2 but its strength
        is 0, as first value is 0.
        In fifth case, None of the group has strength of required form.
"""

import os
import sys

MAX_EXP = 800

def make_two_power_set():
    return {1 << i for i in range(MAX_EXP+1)}

def count_matches(digits, powers):
    return sum(digits.count(str(power)) for power in powers)

if __name__ == '__main__':
    two_power_set = make_two_power_set()
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(sys.stdin.readline().rstrip())

    for t_itr in range(t):
        a = sys.stdin.readline().rstrip()

        result = count_matches(a, two_power_set)

        fptr.write(str(result) + '\n')

    fptr.close()
"""
#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'twoTwo' function below.
#
# The function is expected to return an INTEGER.
# The function accepts STRING a as parameter.
#

# Function to check
# Log base 2
def Log2(x):
    if(x == 0):
        return 0
    return (math.log10(x) / math.log10(2));

# Function to check
# if x is power of 2
def isPowerOfTwo(n):
    return (math.ceil(Log2(n)) == math.floor(Log2(n)));

def strength(i,j,a):
    if(int(a[i]) == 0):
        return 0
    value = 0
    for k in a[i:j]:
        if(int(k) < len(a[i:j])):
            value = value * 10 + int(a[int(k)-1])
    return value

def twoTwo(a):
    # Write your code here
    #the problem must be here somewhere
    ans = []
    count = 0
    for i in range(0, len(a)):
        count = 0
        for j in range(i+1, len(a)):
            temp = strength(i,j,a)
            if(isPowerOfTwo(int(temp))):
                count += 1
        ans.append(count)
    return ans

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    t = int(input().strip())

    for t_itr in range(t):
        a = input()

        result = twoTwo(a)

        fptr.write(str(result) + '\n')

    fptr.close()
"""
