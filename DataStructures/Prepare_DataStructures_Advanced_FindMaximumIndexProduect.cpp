/*
You are given a list of N numbers a_1,a_2,...,a_n. For each
element at position i (1<=i<=N), we define Left(i) and Right(i)
as:
    Left(i) = closest index j such that j < i and a_j>a_i. If
    no such j exists then Left(i) = 0.
    Right(i) = closest index k such that k > i and a_k>a_i. If
    no such k exists then Right(i) = 0.
We define  IndexProduct(i)= Left(i) * Right(i). You need to
find out the maximum IndexProduct(i) among all i.
Input Format
    The first line contains an integer N, the number of
    integers. The next line contains the N integers describing
    the list a[1..N].
Constraints
    1<=N<=10^5
    1<-a_i<=10^9
Output Format
    Output the maximum IndexProduct among all indices from 1
    to N.
Sample Input
    5
    5 4 3 4 5
Sample Output
    8
Explanation
    We can compute the following:
        IndexProduct(1)=0
        IndexProduct(2)=1X5=5
        IndexProduct(3)=2X4=8
        IndexProduct(4)=1X5=5
        IndexProduct(5)=0
    The largest of these is 8, so it is the answer.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
 long solve(vector<int> arr) {
    int n=arr.size();
    vector<long> left(n,0),right(n,0);
    stack<int> s;
    int i=0;
    while(i<n)
    {
        if(!s.empty() && arr[s.top()]<arr[i])
            {left[s.top()]=i+1; s.pop();}
        else
            s.push(i++);
    }
    while(!s.empty()) s.pop();
    i=n-1;
    while(i>=0)
    {
        if(!s.empty() && arr[s.top()]<arr[i])
            {right[s.top()]=i+1; s.pop();}
        else
            s.push(i--);
    }
    long res=0;
    for(int i=0;i<n;i++)
        res=max(res,(long)left[i]*right[i]);
    return res;
}
 /*
 //to slow
int findLeft(vector<int>arr, int i)
{
    for(int j = i; j >=0; j--){
        if(arr[j] > arr[i])
        {
            return j+1;
        }
    }
    return 0;
}
int findRight(vector<int>arr, int i)
{
    for(int k = i; k < arr.size(); k++){
        if(arr[k] > arr[i])
        {
            return k+1;
        }
    }
    return 0;
}
int solve(vector<int> arr) {
    int maxInProd = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        int left = 0, right = 0;
        if(i == 0 || i == arr.size()-1)
        {
            continue;
        }
        left = findLeft(arr, i);
        right = findRight(arr,i);
        int temp = left * right;
        if(temp > maxInProd)
        {
            maxInProd = temp;
        }
    }
    return maxInProd;
}
*/
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string arr_count_temp;
    getline(cin, arr_count_temp);

    int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    long result = solve(arr);//needs to be long not int

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
