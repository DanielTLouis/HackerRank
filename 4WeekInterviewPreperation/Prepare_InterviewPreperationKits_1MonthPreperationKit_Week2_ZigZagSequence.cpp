/*
In this challenge, the task is to debug the existing code to successfully execute all
provided test files.
Given an array of  distinct integers, transform the array into a zig zag sequence by
permuting the array elements. A sequence will be called a zig zag sequence if the k
first elements in the sequence are in increasing order and the last k elements are in
decreasing order, where k=(n+1)/2. You need to find the lexicographically smallest zig
zag sequence of the given array.
Example.
    a=[2,3,5,1,4]
    Now if we permute the array as [1,4,5,3,2], the result is a zig zag sequence.
    Debug the given function findZigZagSequence to return the appropriate zig zag
    sequence for the given input array.
    Note: You can modify at most three lines in the given code. You cannot add or
    remove lines of code.
    To restore the original code, click on the icon to the right of the language
    selector.
Input Format
    The first line contains t the number of test cases. The first line of each test
    case contains an integer n, denoting the number of array elements. The next line
    of the test case contains n elements of array a.
Constraints
    1<=t<=20
    1<=n<=100000 (n is always odd)
    1<=a_i<=10^9
Output Format
    For each test cases, print the elements of the transformed zig zag sequence in a
    single line.
*/

#include <bits/stdc++.h>
using namespace std;

void findZigZagSequence(vector < int > a, int n){
    sort(a.begin(), a.end());
    int mid = (n - 1)/2;
    swap(a[mid], a[n-1]);

    int st = mid + 1;
    int ed = n - 2;
    while(st <= ed){
        swap(a[st], a[ed]);
        st = st + 1;
        ed = ed - 1;
    }
    for(int i = 0; i < n; i++){
        if(i > 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
}

int main() {
    int n, x;
    int test_cases;
    cin >> test_cases;

    for(int cs = 1; cs <= test_cases; cs++){
        cin >> n;
        vector < int > a;
        for(int i = 0; i < n; i++){
            cin >> x;
            a.push_back(x);
        }
        findZigZagSequence(a, n);
    }
}
