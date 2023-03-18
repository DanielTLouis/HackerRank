/*
Given an array, you are asked to perform a number of queries and divide the array into
what are called, beautiful subsequences.
The array A has length n. A function f(A) is defined to be a minimal possible x, such
that it's possible to divide array A into x beautiful subsequences. Note that each
element of an array should belong to exactly one subsequence, and subsequence does not
necessarily need to be consecutive.
A subsequence S with length len is called beautiful if and only if:
    * len=1 or
    * Let S' be a sorted version of S. It must hold that S'_i=S'_(i+1) - 1 for every
    i element of {[1,len-1]}.
For instance, if A=[1,2,3,4,3,5], f(A) would be 2. Because, you can divide A into 2
beautiful subsequences either like [1,2,3] and [4,3,5] or like [1,2,3,4,5] and [3].
You have to answer q queries. Each query is of the type:
    * id val: you need to change a value of A_id to val, i.e. A_id = val. Here id is
    1-indexed.
After each query, for the value of f(A), lets denote that value as ans, where i
indicates the ith query.
You need to find sumation(i X ans_i)fori to q modulo (10^9 + 7).
Input Format
    The first line contains a single integer n, representing the length of array A.
    The next line contains the array A given as space-separated integers.
    The next line contains a single integer q, representing the number of queries.
    Each of the q lines contain two integers id and val, which is described above.
Constraints
    1<=n,q<=3X10^5
    1<=A_i<=1-^9
    1<=id<=n
    1<=val<=10^9
Output Format
    Print the required answer in one line.
Sample Input 0
    5
    2 2 1 1 1
    2
    3 2
    5 5
Sample Output 0
    11
Explanation 0
    The initial array A is [2,2,1,1,1]
        After 1st query the array becomes [2,2,2,1,1] this can be divided into 3
        subsequences as [2,1], [2,1] and [2].
        After 2nd query the array becomes [2,2,2,1,5] this can be divided into 4
        subsequences as [2,1], [2], [2] and [5].
        image
    Hence, calculating sumation(1 X ans_i) we get
        1X3+2X4=11
Sample Input 1
    2
    3 3
    3
    2 4
    1 5
    2 2
Sample Output 1
    9
Explanation 1
    The initial array A is [3,3]
        * After 1st query the array becomes [3,4] this can be divided into 1 subsequence
        as [3,4].
        * After 2nd query the array becomes [5,4] this can be divided into 1 subsequence
        as [5,4].
        * After 3rd query the array becomes [5,2] this can be divided into 2
        subsequences as [5] and [2].
    Hence, calculating  we get
        1X1+2X1+3X2=9
*/

#include <bits/stdc++.h>
using namespace std;
long int mod=1000000007 ;
int main(){
    int n;
    cin>>n;
    multiset<int> set1;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
        set1.insert(arr[i]);
    }
    multiset<int> set2=set1;
    int count=0;
    while(set2.size()){
        count++;
        int cur=*(set2.begin());
        set2.erase(set2.find(cur));
        while((set2.find(cur+1))!=set2.end()){
            cur++;
            set2.erase(set2.find(cur));
        }
    }
   long long int q;
    cin>>q;
    long long int ans=0;
    for(long long int i=0;i<q;i++){
        int id,val;
        cin>>id>>val;
        id--;
        int curr=set1.count(arr[id]);
        int prev=set1.count(arr[id]-1);
          int next=set1.count(arr[id]+1);
          //cout<<'\t'<<curr<<'\t'<<prev<<'\t'<<next<<'\n';
          if(prev==0 && next==0)
          count--;
          else if(curr>max(prev,next))
          count--;
          else if(curr<=min(prev,next))
          count++;
          set1.erase(set1.find(arr[id]));
          arr[id]=val;
          curr=set1.count(arr[id]);
          prev=set1.count(arr[id]-1);
          next=set1.count(arr[id]+1);
          //cout<<'\t'<<curr<<'\t'<<prev<<'\t'<<next<<'\n';
         if(prev==0 && next==0)
          count++;
           else if((curr+1)>max(prev,next))
          count++;
           else if((curr+1)<=min(prev,next))
          count--;
          set1.insert(val);
          ans=(ans+((i+1)*(count))%mod)%mod;
    }
    cout<<ans;
    return 0;
}
