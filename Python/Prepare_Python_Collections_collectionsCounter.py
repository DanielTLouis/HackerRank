#Problem
"""
collections.Counter()*
    * https://docs.python.org/2/library/collections.html#collections.Counter *
    A counter is a container that stores elements as dictionary
    keys, and their counts are stored as dictionary values.
    Sample Code
        >>> from collections import Counter
        >>>
        >>> myList = [1,1,2,3,4,5,3,2,3,4,2,1,2,3]
        >>> print Counter(myList)
        Counter({2: 4, 3: 4, 1: 3, 4: 2, 5: 1})
        >>>
        >>> print Counter(myList).items()
        [(1, 3), (2, 4), (3, 4), (4, 2), (5, 1)]
        >>>
        >>> print Counter(myList).keys()
        [1, 2, 3, 4, 5]
        >>>
        >>> print Counter(myList).values()
        [3, 4, 4, 2, 1]
Task
    Raghu is a shoe shop owner. His shop has X number of shoes.
    He has a list containing the size of each shoe he has in his
    shop.
    There are N number of customers who are willing to pay x_i
    amount of money only if they get the shoe of their desired
    size.
    Your task is to compute how much money Raghu earned.
Input Format
    The first line contains X, the number of shoes.
    The second line contains the space separated list of all the
    shoe sizes in the shop.
    The third line contains N, the number of customers.
    The next N lines contain the space separated values of the
     desired by the customer and x_i, the price of the shoe.
Constraints
    0 < X < 10^3
    0 < N < <= 10^3
    20 < x_i < 100
    2 < shoe size < 20
Output Format
    Print the amount of money earned by Raghu.
Sample Input
    10
    2 3 4 5 6 8 7 6 5 18
    6
    6 55
    6 45
    6 55
    4 40
    18 60
    10 50
Sample Output
    200
Explanation
    Customer 1: Purchased size 6 shoe for $55.
    Customer 2: Purchased size 6 shoe for $45.
    Customer 3: Size 6 no longer available, so no purchase.
    Customer 4: Purchased size 4 shoe for $40.
    Customer 5: Purchased size 18 shoe for $60.
    Customer 6: Size 10 not available, so no purchase.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
#Counter is not an element of the standard python lib
X = int(input())
shoes = list(map(int, input().split(' ')))
N = int(input())
cussize = []
cuzmoney = []
for i in range(0, N):
    tempsize, tempmoney  = input().split(' ')
    cussize.append(int(tempsize))
    cuzmoney.append(int(tempmoney))
total = 0
for i in range(0, N):
    for j in range(0, len(shoes)):
        if(cussize[i] == shoes[j]):
            total += cuzmoney[i]
            shoes.remove(shoes[j])
            break
print(total)
