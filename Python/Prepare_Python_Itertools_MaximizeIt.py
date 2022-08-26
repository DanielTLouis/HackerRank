#Problem
"""
You are given a function f(X)=X^2. You are also given K lists. The ith list consists of N_i elements.
You have to pick one element from each list so that the value from the equation below is maximized:
S=(f(X_1)+(f(X_2)+f(X_3)+...+f(X_k))%M
X_i denotes the element picked from the ith list . Find the maximized value S_max obtained.
denotes the modulo operator.
Note that you need to take exactly one element from each list, not necessarily the largest element. You add the squares of the chosen elements and perform the modulo operation. The maximum value that you can obtain, will be the answer to the problem.
Input Format
    The first line contains 2 space separated integers K and
    M.
    The next K lines each contains an integer N_i, denoting
    the number of elements in the ith list, followed by N_i
    space separated integers denoting the elements in the list.
Constraints
    1<=K<=7
    1<=M<=1000
    1<=N_i<=7
    1<=Magnitued of elements in list <=10^9
Output Format
    Output a single integer denoting the value S_max.
Sample Input
    3 1000
    2 5 4
    3 7 8 9
    5 5 7 8 9 10
Sample Output
    206
Explanation
    Picking 5 from the 1st list, 9 from the 2nd list and 10
    from the 3rd list gives the maximum S value equal to (5^2
    + 9^2 + 10^2)%1000= 206.
"""

# Enter your code here. Read input from STDIN. Print output to STDOUT
from itertools import product
k, m = input().split(' ')
ars = []
for i in range(0, int(k)):
    #[1:] we dont want the first num it is how many el in list
    ars.append(list(map(int, input().split(' ')))[1:])
#faster way to get all lists into memeory
#N = (list(map(int, input().split()))[1:] for _ in range(K))

#finds each largest sum by steping through all ars
#lamda is a function by no name remeber
results = map(lambda x: sum(i**2 for i in x)%int(m), product(*ars))
print(max(results))
"""
#Not so right need to keep all results and find the max
##no way to cheat
#my way was to find largest so that i**2%M was largest for
##each N
bestNs = []
temp = 0
for i in range(0, int(k)):
    temp = 0
    for j in range(0, len(ars[i])):
       if((ars[i][j]**2) % int(m) > temp):
           temp = ars[i][j]**2
    bestNs.append(temp)
b = []
for i in range(0, len(bestNs)):
    b.append(math.sqrt(bestNs[i]))
print(b)
print(int(sum(bestNs)) % int(m))
"""
