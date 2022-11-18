/*
You are given two arrays, A and , both containing N integers.
A pair of indices (i,j) is beautiful if the ith element of array A is equal to 
the jth element of array B. In other words, pair (i,j) is beautiful if and only 
if A[i]=B[j]. A set containing beautiful pairs is called a beautiful set.
A beautiful set is called pairwise disjoint if for every pair (l[i],r[i]) 
belonging to the set there is no repetition of either l[i] or r[i] values. For 
instance, if A=[10,11,12,5,14] and B=[8,9,11,11,5] the beautiful set 
[(1,2),(1,3),(3,4)] is not pairwise disjoint as there is a repetition of a, that 
is l[0][0]=l[1][0].
Your task is to change exactly 1 element in B so that the size of the pairwise 
disjoint beautiful set is maximum.
Function Description
    Complete the beautifulPairs function in the editor below. It should return an 
    integer that represents the maximum number of pairwise disjoint beautiful 
    pairs that can be formed.
    beautifulPairs has the following parameters:
        A: an array of integers
        B: an array of integers
Input Format
    The first line contains a single integer n, the number of elements in A and B.
    The second line contains n space-separated integers A[i].
    The third line contains n space-separated integers B[i].
Constraints
    1<=n<=10^3
    1<=A[i],B[i]<=10^3
Output Format
    Determine and print the maximum possible number of pairwise disjoint 
    beautiful pairs.
    Note: You must first change 1 element in B, and your choice of element must 
    be optimal.
Sample Input 0
    4
    1 2 3 4
    1 2 3 3
Sample Output 0
    4
Explanation 0
    You are given A=[1,2,3,4] and B=[1,2,3,3].
    The beautiful set is [(0,0),(1,1),(2,2),(3,3)] and maximum sized pairwise 
    disjoint beautiful set is either [(0,0),(1,1),(2,2)] or [(0,0),(1,1),(2,3)].
    We can do better. We change the 3rd element of array B from 3 to 4. Now new B 
    array is: B=[1,2,4,3] and the pairwise disjoint beautiful set is 
    [(0,0),(1,1),(2,3),(3,2)]. So, the answer is 4.
    Note that we could have also selected index 3 instead of index 2 but it would 
    have yeilded the same result. Any other choice of index is not optimal.
Sample Input 1
    6
    3 5 7 11 5 8
    5 7 11 10 5 8
Sample Output 1
    6
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'beautifulPairs' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY A
 *  2. INTEGER_ARRAY B
 */

int beautifulPairs(vector<int> A, vector<int> B) {
    unordered_multiset<int> set;
    
    for(int e: A) set.insert(e);
    
    int res = 0;
    for(int e: B) {
        if(set.find(e) != set.end()) {
            res++;
            set.erase(set.find(e));
        }
    }
    if(set.size()) return res + 1;
    else return res - 1;
    /*
    vector<pair<int, int>> pairs;
    for(int i = 0; i < A.size(); i++)
    {
        for(int j = 0; j < B.size(); j++)
        {
            if(A[i] == B[j])
            {
                pairs.push_back({i,j});
                B[j] = -1;
            }
        }
    }
    if(pairs.size() < A.size() && pairs.size() < B.size())
    {
        return pairs.size() + 1;
    }
    else{
        return pairs.size() - 1;
    }
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string A_temp_temp;
    getline(cin, A_temp_temp);

    vector<string> A_temp = split(rtrim(A_temp_temp));

    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        int A_item = stoi(A_temp[i]);

        A[i] = A_item;
    }

    string B_temp_temp;
    getline(cin, B_temp_temp);

    vector<string> B_temp = split(rtrim(B_temp_temp));

    vector<int> B(n);

    for (int i = 0; i < n; i++) {
        int B_item = stoi(B_temp[i]);

        B[i] = B_item;
    }

    int result = beautifulPairs(A, B);

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
