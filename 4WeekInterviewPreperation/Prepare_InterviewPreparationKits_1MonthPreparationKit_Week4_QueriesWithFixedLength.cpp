/*
Consider an n-integer sequence, A={a_0,a_1,a_2,...,a_n-1}. We perform a query on A by using an integer, d, to calculate the result of the following expression:
        min(max(a_j))
        0<=i<=n-d ; i<=j<i+d
In other words, if we let m_i=max(a_i,a_i+1,a_i+2,...,a_i+d-1), then you need to calculate min(m_0,m_1,m_2,...,m_n-d).
Given arr and q queries, return a list of answers to each query.
Example
    arr=[2,3,4,5,6]
    queries =[2,3]
    The first query uses all of the subarrays of length 2: [2,3],[3,4],
    [4,5],[5,6]. The maxima of the subarrays are [3,4,5,6]. The 
    minimum of these is 3.
    The second query uses all of the subarrays of length 3: [2,3,4],
    [3,4,5],[4,5,6]. The maxima of the subarrays are [4,5,6]. The 
    minimum of these is 4.
    Return [3,4].
Function Description
    Complete the solve function below.
    solve has the following parameter(s):
        -int arr[n]: an array of integers
        -int queries[q]: the lengths of subarrays to query
Returns
    int[q]: the answers to each query
Input Format
    The first line consists of two space-separated integers, n and q.
    The second line consists of n space-separated integers, the 
    elements of arr.
    Each of the q subsequent lines contains a single integer denoting 
    the value of q for that query.

Constraints
    1<=n<=10^5
    0<=arr[i]<10^6
    1<=q<=100
    1<=d<=n
Sample Input
    5 5
    1 2 3 4 5
    1
    2
    3
    4
    5
Sample Output
    1
    2
    3
    4
    5
Explanation
    Each prefix has the least maximum value among the consecutive 
    subsequences of the same size.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

struct customPQ {
    priority_queue<int> pq;
    unordered_map<int, int> m;  // map to track removed elements inside pq
    
    int top() {
        while (m.find(pq.top()) != m.end()) {
            m[pq.top()] -= 1;
            if (m[pq.top()] == 0)
                m.erase(pq.top());
            pq.pop();
        }
        return pq.top();
    }
    
    void push(int x) {
        pq.push(x);
    }
    
    void remove(int x) {
        if (x == pq.top())
            pq.pop();
        else
            m[x] += 1;
    }
};

int helper(vector<int>& arr, int d) {
    customPQ* pq = new customPQ();
    for (int i = 0;i < d;i++) {
        pq->push(arr[i]);
    }
    
    int res = INT_MAX;
    for (int i = d;i < arr.size();i++) {
        res = min(res, pq->top());
        pq->remove(arr[i-d]);
        pq->push(arr[i]);
    }
    return min(res, pq->top());
}
/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY arr
 *  2. INTEGER_ARRAY queries
 */
vector<int> solve(vector<int> arr, vector<int> queries) {
    vector<int> res(queries.size());
    for (int i = 0;i < queries.size();i++) {
        res[i] = helper(arr, queries[i]);
    }
    
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<int> queries(q);

    for (int i = 0; i < q; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<int> result = solve(arr, queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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