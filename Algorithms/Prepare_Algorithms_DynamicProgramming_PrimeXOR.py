"""
Penny has an array of n integers, [a0,a1,...,a(n-1)]. She wants to find the number of unique multisets* she can form using elements from the array such that the bitwise XOR** of all the elements of the multiset is a prime number***. Recall that a multiset is a set which can contain duplicate elements.
* https://en.wikipedia.org/wiki/Multiset *
** https://en.wikipedia.org/wiki/Bitwise_operation#XOR **
*** https://en.wikipedia.org/wiki/Prime_number ***
Given q queries where each query consists of an array of integers, can you help Penny find and print the number of valid multisets for each array? As these values can be quite large, modulo each answer by 10^9 +7 before printing it on a new line.
Input Format
    The first line contains a single integer, q, denoting the number of queries. The 2*q
    subsequent lines describe each query in the following format:
        1. The first line contains a single integer, n, denoting the number of integers in the
        array.
        2. The second line contains n space-separated integers describing the respective
        values of a0,a1,...,a(n-1).
Constraints
    1<=q<=10
    1<=n<=100000
    3500<=ai<=4500
Output Format
    On a new line for each query, print a single integer denoting the number of unique
    multisets Penny can construct using numbers from the array such that the bitwise XOR of
    all the multiset's elements is prime. As this value is quite large, your answer must be
    modulo 10^9 +7.
Sample Input
    1
    3
    3511 3671 4153
Sample Output
    4
Explanation
    The valid multisets are:
        {3511}->3511 is prime.
        {3671}->3671 is prime.
        {4153}->4153 is prime.
        {3511,3671,4153}->3511 ^ 3671 ^ 4153 = 5081, which is prime.
    Because there are four valid multisets, we print the value of 4%(10^9 +7)=4 on a new line.
"""
from collections import Counter
from math import sqrt
import re
import sys
import random
# Complete the primeXor function below.
def middle_out(counts):
    a = ((4096, 4351), (4352, 4500), (3584, 4095), (3500, 3583))
    b = ((256, 0), (512, 0), (512, 4096), (1024, 4096))
    divisor = 0
    count = [0]*4501
    for i,n in counts:
        count[i] = n

    sum = [[0]*8192 for _ in range(2)]
    temp, update = 0, 1
    sum[temp][0] = 1
    divisor = 10**9 + 7
    for i,p in enumerate(a):
        for j,n in enumerate(count[p[0]:p[1]+1]):
            if n:
                temp2 = n//2
                same = 1 + temp2
                change = (n+1)//2
                o = b[i][1]
                for x in range(b[i][0]):
                    y = x^(j+p[0])
                    sum[update][y] = (sum[temp][x]*change + sum[temp][y]*same)
                    sum[update][x] = (sum[temp][y]*change + sum[temp][x]*same)

                    if o:
                        sum[update][y+o] = (sum[temp][x+o]*change + sum[temp][y+o]*same)
                        sum[update][x+o] = (sum[temp][y+o]*change + sum[temp][x+o]*same)

                if sum[update][0] > 100000*divisor:
                    for x in range(len(sum[update])):
                        sum[update][x] %= divisor
                temp, update = update, temp

    p = primes(8191)
    total = 0
    for prime in p:
        total += sum[temp][prime]
    return total % divisor

def primes(n):
    x = [True]*((n-1)//2)
    for i in range(int((sqrt(n)-3)//2)+1):
        if x[i]:
            x[2*i*i+6*i+3::2*i+3] = [False] * int((n-(2*i+3)**2)//(4*i+6)+1)
    return [2] + [2*i+3 for i,v in enumerate(x) if v]
q = int(input())
for _ in range(q):
    n = int(input())
    numbers = Counter(int(x) for x in input().split()).items()
    print(middle_out(numbers))
"""
#!/bin/python3

import math
import os
import random
import re
import sys
from collections import Counter
#
# Complete the 'primeXor' function below.
#
# The function is expected to return an INTEGER.
# The function accepts INTEGER_ARRAY a as parameter.
#
# Complete the primeXor function below.

##Checks if n is a prime number
def isPrime(n):
    if (n > 1):
        # Iterate from 2 to n / 2
        for i in range(2, int(n/2)+1):
            # If n is divisible by any number between
            # 2 and n / 2, it is not prime
            if (n % i) == 0:
                return False
                break
            else:
                return True
    else:
        return False

def primeXor(a):
    # Write your code here
    Xor = a[0]
    amountArePrime = 0
    if(isPrime(a[0])):
            amountArePrime += 1
    for i in range(1,len(a)):
        if(isPrime(a[i])):
            amountArePrime += 1
        Xor += Xor ^ a[i]
    if(isPrime(Xor)):
            amountArePrime += 1
    return amountArePrime


if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    q = int(input().strip())

    for q_itr in range(q):
        n = int(input().strip())

        a = list(map(int, input().rstrip().split()))

        result = primeXor(a)

        fptr.write(str(result) + '\n')

    fptr.close()
"""
