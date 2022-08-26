/*
This question is designed to help you get a better understanding of basic heap
operations.
There are 3 types of query:
    "1v " - Add an element  to the heap.
    "2v " - Delete the element  from the heap.
    "3" - Print the minimum of all the elements in the heap.
NOTE: It is guaranteed that the element to be deleted will be there in the heap. Also,
 at any instant, only distinct elements will be in the heap.
Input Format
    The first line contains the number of queries, Q.
    Each of the next Q lines contains one of the 3 types of query.
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
    gives 9 as the output.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>//Added
using namespace std;

void heapifyUp(vector<int> & qheap){
    int n = qheap.size() - 1;

    while (n > 0) {
        if (qheap[(n - 1) / 2] > qheap[n]) {
            int temp = qheap[n];
            qheap[n] = qheap[(n - 1) / 2];
            qheap[(n - 1) / 2] = temp;
        }
        n = (n - 1) / 2;
    }
}

void heapifyDown(vector<int> & qheap, int n){

    while (true) {
        int smallIndex = 2 * n + 1;

        if (smallIndex + 1 < qheap.size()) {

            if (qheap[smallIndex] > qheap[smallIndex + 1]) {
                smallIndex += 1;
            }

            if (qheap[n] > qheap[smallIndex]) {
                swap(qheap[n], qheap[smallIndex]);
                n = smallIndex;
                continue;
            }
            break;
        }

        if (smallIndex < qheap.size()) {
            if (qheap[n] > qheap[smallIndex]) {
                swap(qheap[n], qheap[smallIndex]);
                n = smallIndex;
                continue;
            }
            break;
        }

        break;
    }
}

int findIndex(vector<int> &qheap, int val){
    int index = 0;

    for (int i = 0; i < qheap.size(); i++) {
        if (qheap[i] == val) {
            index = i;
            break;
        }
    }

    return index;
}


int main() {

    int t;
    cin >> t;
    vector<int> qheap;

    for (int i = 0; i < t; i++) {
        int qtype;
        cin >> qtype;

        if (qtype == 1) {
            int n;
            cin >> n;

            qheap.push_back(n);
            heapifyUp(qheap);
        }

        else if (qtype == 2) {
            int n;
            cin >> n;

            int index = findIndex(qheap, n);

            if (qheap.size() > 0) {
                qheap[index] = qheap.back();
                qheap.pop_back();
                heapifyDown(qheap, index);
            }
        }

        else if (qtype == 3) {
            if (qheap.size() > 0) {
                cout << qheap[0] << endl;
            }
        }
    }

    return 0;
}
//too slow but otherwise works (C++ heap to slow it seems needs heapify)
/*
int main() {
    // Enter your code here. Read input from STDIN. Print output to STDOUT
    int q = 0;
    cin >> q;
    vector<int> heap;

    //make heap
    std::make_heap(heap.begin(),heap.begin());
    for(int i = 0; i < q; i++)
    {
        int instruction = 0;
        cin >> instruction;
        if(instruction == 1)
        {
            int num = 0;
            cin >> num;
            heap.push_back(num); std::push_heap (heap.begin(),heap.end());
        }
        else if(instruction == 3)
        {
            std::sort_heap(heap.begin(),heap.end());sort(heap.begin(), heap.end());
            cout << heap.front()<<"\n";
        }
        else if(instruction == 2)
        {
            int num2 = 0;
            cin >> num2;
            int index = 0;
            for(int j = 0; j < heap.size(); j++)
            {
                if(heap[j] == num2)
                {
                    index = j;
                    break;
                }
            }
            //std::pop_heap (heap.begin(),heap.begin()+index+1);
            heap.erase(std::next(heap.begin()+index-1));
        }
        else {
            cout << "instruction not found.\n";
        }
    }
    return 0;
}
*/
