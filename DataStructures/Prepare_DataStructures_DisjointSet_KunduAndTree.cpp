/*
Kundu is true tree lover. Tree is a connected graph having N vertices and N-1 edges.
Today when he got a tree, he colored each edge with one of either red(r) or black(b)
color. He is interested in knowing how many triplets(a,b,c) of vertices are there , such
that, there is atleast one edge having red color on all the three paths i.e. from vertex
a to b, vertex b to c and vertex c to a . Note that (a,b,c), (b,a,c) and all such
permutations will be considered as the same triplet.
If the answer is greater than 10^9 + 7, print the answer modulo (%) 10^9 + 7.
Input Format
    The first line contains an integer N, i.e., the number of vertices in tree.
    The next N-1 lines represent edges: 2 space separated integers denoting an edge
    followed by a color of the edge. A color of an edge is denoted by a small letter of
    English alphabet, and it can be either red(r) or black(b).
Output Format
    Print a single number i.e. the number of triplets.
Constraints
    1 ≤ N ≤ 105
    A node is numbered between 1 to N.
Sample Input
    5
    1 2 b
    2 3 r
    3 4 r
    4 5 b
Sample Output
    4
Explanation
    Given tree is something like this.
        image
    (2,3,4) is one such triplet because on all paths i.e 2 to 3, 3 to 4 and 2 to 4 there
    is atleast one edge having red color.
    (2,3,5), (1,3,4) and (1,3,5) are other such triplets.
    Note that (1,2,3) is NOT a triplet, because the path from 1 to 2 does not have an
    edge with red color.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include<stack>
#include <iostream>
#include <algorithm>
using namespace std;
long long int parent(long long int i, long long int* arr){
    while(arr[i]>0)
        i=arr[i];
    return i;
}
long long int bin(long long int a){
    if(a<3)
        return 0;
    return ((a)*(a-1)*(a-2))/6;
}
int main() {
    long long int n;
    cin>>n;
    long long int parentarr[n+1];
    for(long long int i=0;i<n+1;i++)
        parentarr[i]=-1;
    for(long long int i=1;i<n;i++){
        long long int j,k;
        char col;
        cin>>j>>k>>col;
        long long int x=parent(j,parentarr);
        long long int y=parent(k,parentarr);
        if(x!=y&&col=='b'){
                long long int c=parentarr[x]<=parentarr[y]?x:y;
                long long int d=parentarr[x]>parentarr[y]?x:y;
                parentarr[c]+=parentarr[d];
                parentarr[d]=c;
        }
    }
    long long int total_triplets=bin(n);
    long long int to_subtract=0;
    for(long long int i=1;i<n+1;i++){
        if(parentarr[i]>=-1)
            continue;
        long long int z=abs(parentarr[i]);
        to_subtract+=bin(z)+(n-z)*((z*(z-1))/2);
    }
    long long int sums=total_triplets-to_subtract;
    cout<<sums%(1000000007)<<endl;
    return 0;
}
s
