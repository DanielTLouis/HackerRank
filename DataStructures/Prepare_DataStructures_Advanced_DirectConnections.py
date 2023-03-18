"""
Enter-View (EV) is a linear, street-like country. By linear, we mean all the cities of
the country are placed on a single straight line - the x-axis. Thus every city's
position can be defined by a single coordinate, x_i, the distance from the left
borderline of the country. You can treat all cities as single points.
Unfortunately, the dictator of telecommunication of EV (Mr. S. Treat Jr.) doesn't know
anything about the modern telecom technologies, except for peer-to-peer connections.
Even worse, his thoughts on peer-to-peer connections are extremely faulty: he believes
that, if P_i people are living in city i, there must be at least P_i cables from city
to every other city of EV - this way he can guarantee no congestion will ever occur!
Mr. Treat hires you to find out how much cable they need to implement this
telecommunication system, given the coordination of the cities and their respective
population.
Note that The connections between the cities can be shared. Look at the example for the
detailed explanation.
Input Format
    A number T is given in the first line and then comes T blocks, each representing a
    scenario.
    Each scenario consists of three lines. The first line indicates the number of cities
    (N). The second line indicates the coordinates of the N cities. The third line
    contains the population of each of the cities. The cities needn't be in increasing
    order in the input.
Output Format
    For each scenario of the input, write the length of cable needed in a single line
    modulo 1,000,000,007.
Constraints
    1<=T<=20
    1<=N<=200,000
    P_i<=10,000
    Border to border length of the country <=n1,000,000,000
Sample Input
    2
    3
    1 3 6
    10 20 30
    5
    5 55 555 55555 555555
    3333 333 333 33 35
Sample Output
    280
    463055586
Explanation
    For the first test case, having 3 cities requires 3 sets of cable connections.
    Between city 1 and 2, which has a population of 10 and 20, respectively, Mr. Treat
    believes at least 10 cables should come out of city 1 for this connection, and at
    least 20 cables should come out of city  for this connection. Thus, the connection
    between city 1 and city 2 will require 20 cables, each crossing a distance of 3-1=2
    km. Applying this absurd logic to connection 2,3 and 1,3, we have
        [1,2] => 20 connections X2km=40  km of cable
        [2,3] => 30 connections X3km=90  km of cable
        [1,3] => 30 connections X5km=150  km of cable
    For a total of 280 , Output is 280 km of cable
"""
from collections import defaultdict,deque
import bisect
p=10**9+7

def build(a,pos=1,start=1,end=None):
    end=end or n
    global tree
    if(start==end):
        tree[pos]=a[start-1]
        return
    mid=(start+end)//2
    build(a,2*pos,start,mid)
    build(a,2*pos+1,mid+1,end)
    tree[pos]=tree[2*pos]+tree[2*pos+1]

def query(l,r,pos=1,start=1,end=None):
    end=end or n
    global tree
    if(l>end or r<start):
        return(0)
    if(l<=start and r>=end):
        return(tree[pos])
    mid=(start+end)//2
    return(query(l,r,2*pos,start,mid)+query(l,r,2*pos+1,mid+1,end))

def update(x,val,pos=1,start=1,end=None):
    end=end or n
    global tree
    if(start==end):
        tree[pos]-=val
        return
    mid=(start+end)//2
    if(x<=mid):
        update(x,val,2*pos,start,mid)
    else:
        update(x,val,2*pos+1,mid+1,end)
    tree[pos]=tree[2*pos]+tree[2*pos+1]

t=int(input())
for _ in range(t):
    ans=0
    n=int(input())
    tree=[0]*(4*n+1)

    location=list(map(int,input().split()))
    population=list(map(int,input().split()))
    loc_asc=sorted(location)
    info_dict=defaultdict(lambda: [])

    build(loc_asc)

    for k,v in zip(population,location):
        info_dict[k].append(v)

    pos_dict={v:k for k,v in list(enumerate(loc_asc,1))}
    pop_desc=deque(sorted(list(set(population)),key=None,reverse=True))

    calculated=[]
    while(pop_desc):
        max_pop=pop_desc.popleft()
        while(info_dict[max_pop]):
            loc=info_dict[max_pop].pop()
            index=pos_dict[loc]
            prefix_sum=query(1,index-1)
            suffix_sum=query(index+1,n)
            before=bisect.bisect(calculated,loc)
            after=len(calculated)-before
            ans+=max_pop*(((index-1-before)*loc-prefix_sum) + (suffix_sum-(n-index-after)*loc) )
            update(index,loc)
            bisect.insort(calculated,loc)
    print(ans%p)
