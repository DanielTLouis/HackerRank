/*
This question is designed to help you get a better understanding of basic heap
operations.
There are 3 types of query:
    -"1 v" - Add an element  to the heap.
    -"2 v" - Delete the element  from the heap.
    -"3" - Print the minimum of all the elements in the heap.
NOTE: It is guaranteed that the element to be deleted will be there in the heap. Also,
at any instant, only distinct elements will be in the heap.
Input Format
    The first line contains the number of queries, Q.
    Each of the next Q lines contains one of the  types of query.
Constraints
    1<=Q<=10^5
    -10^9<=v<=10^9
Output Format
    For each query of type 3, print the minimum value on a single line.
Sample Input
    STDIN       Function
    -----       --------
    5           Q = 5
    1 4         insert 4
    1 9         insert 9
    3           print minimum
    2 4         delete 4
    3           print minimum
Sample Output
    4
    9
Explanation
    After the first 2 queries, the heap contains {4,9}. Printing the minimum gives 4
    as the output. Then, the 4th query deletes 4 from the heap, and the 5th query
    gives  as the output.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

#define NN 100000 //Heap size

struct minHeap{
    int n; //number of nodes in heapArr
    int heapArr[NN+1]; //array is 1 based
    minHeap(){ n=0 ;}
    void min_heapify(int index);
    void insert(int k);
    int search(int k);
    void deleteKey(int k);
    int getMin();
};
void minHeap::min_heapify(int i){
        int l = 2*i;
        int r = 2*i+1;
        int min = i;
        if(l<n && heapArr[l]<heapArr[min])
            min = l;
        if(r<n && heapArr[r]<heapArr[min])
            min = r;
        if(min != i){
            swap(heapArr[i],heapArr[min]);
            min_heapify(min);
        }
    }
void minHeap::insert(int k){
        if(n==NN) return;
        n++;
        heapArr[n]= k;
        int p= n;
        while(p>1){
            int pr= p/2;
            if(heapArr[pr]>heapArr[p]){
                swap(heapArr[pr],heapArr[p]);
                p= pr;
            }
            else break;
        }
}
int minHeap::getMin(){
    if(n==0) return -1;
    else return heapArr[1];
}

int minHeap::search(int ele){
    for(int i=1;i<=n;i++){
        if(heapArr[i] == ele)
            return i;
        }
        return -1;
    }

void minHeap::deleteKey(int ele){
        int index = search(ele);
        heapArr[index] = heapArr[n];
        n--;
        min_heapify(index);
    }
int main(){
    minHeap h;
    int q, t, x;
    cin>>q;
    while(q--){
        cin>>t;
        if(t==1){
            cin>>x;
            h.insert(x);
        }
        else if(t==2){
            cin>>x;
            h.deleteKey(x);
        }
        else{
            cout<<h.getMin()<<endl;
        }
    }
    return 0;
}
