"""
The median of M numbers is defined as the middle number after sorting them in order if M
is odd. Or it is the average of the middle two numbers if M is even. You start with an
empty number list. Then, you can add numbers to the list, or remove existing numbers
from it. After each add or remove operation, output the median.
Example:
    For a set of M=5 numbers 9,2,8,4,1 the median is the third number in the sorted set
    1,2,4,8,9, which is 4. Similarly, for a set of M=4 numbers, 5,2,10,4, the median is
    the average of the second and the third element in the sorted set 2,4,5,10, which is
    (4+5)/2=4.5.
Input:
    The first line is an integer, N, that indicates the number of operations. Each of
    the next N lines is either a x or r x. a x indicates that x is added to the set, and
    r x indicates that x is removed from the set.
Output:
    For each operation: If the operation is add, output the median after adding x in a
    single line. If the operation is remove and the number x is not in the list, output
    Wrong! in a single line. If the operation is remove and the number x is in the list,
    output the median after deleting x in a single line. (If the result is an integer DO
    NOT output decimal point. And if the result is a real number, DO NOT output
    trailing 0s.)
Note
    If your median is 3.0, print only 3. And if your median is 3.50, print only 3.5.
    Whenever you need to print the median and the list is empty, print Wrong!
Constraints:
    0<=N<=10^5
    For each a x or r x, x will always be a signed integer (which will fit in 32 bits).
Sample Input:
    7
    r 1
    a 1
    a 2
    a 1
    r 1
    r 2
    r 1
Sample Output:
        Wrong!
        1
        1.5
        1
        1.5
        1
        Wrong!
    Note: As evident from the last line of the input, if after remove operation the list
    becomes empty, you have to print Wrong!.
"""

#!/bin/python
from array import array
def median(a,x):
    def binarySearch(arr,l,h,x):
        if h>=l:
            mid = (h+l)//2
            if arr[mid] == x:
                return mid
            elif arr[mid] > x:
                return binarySearch(arr,l,mid-1,x)
            else:
                return binarySearch(arr,mid+1,h,x)
        else:
            return l

    arr = array('i',[])
    d = {}
    for i in range(len(a)):
        if a[i] == 'r':
            if len(arr) == 0:
                print('Wrong!')
                continue
            else:
                if x[i] not in d.keys():
                    print('Wrong!')
                    continue
                else:
                    arr.remove(x[i])
                    if d[x[i]] == 1:
                        del(d[x[i]])
                    else:
                        d[x[i]]-=1

        else:
            if len(arr) == 0:
                arr.insert(0,x[i])
                d[x[i]] = 1
            else:
                pos = binarySearch(arr,0,len(arr)-1,x[i])
                arr.insert(pos,x[i])
                if x[i] in d.keys():
                    d[x[i]] += 1
                else:
                    d[x[i]] = 1

        if len(arr) == 0:
            print('Wrong!')
        elif len(arr) % 2 == 1:
            print(arr[(len(arr)-1)//2])
        else:
            m = len(arr)//2
            if (arr[m-1]+arr[m])%2 == 0:
                print((arr[m-1]+arr[m])//2)
            else:
                print((arr[m-1]+arr[m])/2)


N = int(input())
s = []
x = []
for i in range(0, N):
   tmp = input().strip().split(' ')
   a, b = [xx for xx in tmp]
   s.append(a)
   x.append(int(b))
median(s,x)
