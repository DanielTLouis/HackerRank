/*
There are two n-element arrays of integers, A and B. Permute them into some A' and
B'such that the relation A'[i]+B'[i]>=k holds for all i where 0<=i<n.
There will be q queries consisting of A, B, and k. For each query, return YES if some
permutation A', B' satisfying the relation exists. Otherwise, return NO.
Example
    A=[0,1]
    B=[0,2]
    k=1
    A valid A',B' is A'=[1,0] and B'=[0,2]: 1+0>=1 and 0+2>=1. Return YES.
Function Description
    Complete the twoArrays function in the editor below. It should return a string,
    either YES or NO.
    twoArrays has the following parameter(s):
        -int k: an integer
        -int A[n]: an array of integers
        -int B[n]: an array of integers
Returns
    - string: either YES or NO
Input Format
    The first line contains an integer q, the number of queries.
    The next q sets of 3 lines are as follows:
        -The first line contains two space-separated integers n and k, the size of
        both arrays A and B, and the relation variable.
        -The second line contains n space-separated integers A[i].
        -The third line contains n space-separated integers B[i].
Constraints
    1<=q<=10
    1<=n<=1000
    1<=k<=10^9
    0<=A[i],B[i]<=10^9
Sample Input
    STDIN       Function
    -----       --------
    2           q = 2
    3 10        A[] and B[] size n = 3, k = 10
    2 1 3       A = [2, 1, 3]
    7 8 9       B = [7, 8, 9]
    4 5         A[] and B[] size n = 4, k = 5
    1 2 2 1     A = [1, 2, 2, 1]
    3 3 3 4     B = [3, 3, 3, 4]
Sample Output
    YES
    NO
Explanation
    There are two queries:
        1. Permute these into A'=[1,2,3] and B'=[9,8,7] so that the following
        statements
        are true:
            >A[0]+B[1]=1+9=10>=k
            >A[1]+B[1]=2+8=10>=k
            >A[2]+B[2]=3+7=10>=k
        2. A=[1,2,2,1], B=[3,3,3,4], and k=5. To permute A and B into a valid A' and
        B', there must be at least three numbers in A that are greater than 1.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'twoArrays' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 *  3. INTEGER_ARRAY B
 */

string twoArrays(int k, vector<int> A, vector<int> B) {
    int i = 0;
    //sort from highest to lowest
    while(i<A.size())
    {
        if(i < A.size()-1 && A[i] < A[i+1])
        {
            int temp = A[i];
            A[i] = A[i+1];
            A[i+1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
    for(int j = 0; j < A.size(); j++)
    {
        cout << A[j] << " ";
    }
    cout << endl;
    i=0;
    //sort lowest to highest
    while(i < B.size())
    {
        if(i < B.size()-1 && B[i] > B[i+1])
        {
            int temp = B[i];
            B[i] = B[i+1];
            B[i+1] = temp;
            i = 0;
            continue;
        }
        i++;
    }
    for(int j = 0; j < B.size(); j++)
    {
        cout << B[j] << " ";
    }
    cout << endl;
    //compair highest of A and lowest of B if they are greater then k we continue
    //*do this for the whole array if all are true then it is true, else if any one
    //*pair fales then no permutation would match to be greater than k
    for(int j = 0; j < A.size(); j++)
    {
        cout << A[j] + B[j] << "<" << k << endl;
        if(A[j] + B[j] < k)
        {
            return "NO";
        }
    }
    return "YES";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

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

        string result = twoArrays(k, A, B);

        fout << result << "\n";
    }

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
