/*Problem*/
/**
Objective
    Welcome to the last day! Today, we're discussing bitwise operations. Check
    out the Tutorial tab for learning materials and an instructional video!
    * https://www.hackerrank.com/challenges/30-bitwise-and/tutorial *
Task
    Given set S={1,2,3,...,N}. Find two integers, A and B (where A<B), from set S
    such that the value of A&B is the maximum possible and also less than a given
    integer, K. In this case, & represents the bitwise AND operator.
Function Description
    Complete the bitwiseAnd function in the editor below.
    bitwiseAnd has the following paramter(s):
        - int N: the maximum integer to consider
        - int K: the limit of the result, inclusive
Returns
    - int: the maximum value of A&B within the limit.
Input Format
    The first line contains an integer, T, the number of test cases.
    Each of the T subsequent lines defines a test case as 2 space-separated
    integers, and K, respectively.
Constraints
    1<=T<=10^3
    2<=N<=10^3
    2<=K<=N
Sample Input
    STDIN   Function
    -----   --------
    3       T = 3
    5 2     N = 5, K = 2
    8 5     N = 8, K = 5
    2 2     N = 8, K = 5
Sample Output
    1
    4
    0
Explanation
    N=5 K=2 S={1,2,3,4,5}
    All possible values of  and  are:
        1. A=1 B=2; A&B=0
        2. A=1 B=3; A&B=1
        3. A=1 B=4; A&B=0
        4. A=1 B=5; A&B=1
        5. A=2 B=3; A&B=2
        6. A=2 B=4; A&B=0
        7. A=2 B=5; A&B=0
        8. A=3 B=4; A&B=0
        9. A=3 B=5; A&B=1
        10 A=4 B=5; A&B=4
    The maximum possible value of A&B that is also < (k=2) is 1, so we print  on
    a new line.
**/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'bitwiseAnd' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER N
 *  2. INTEGER K
 */
//N is includsive but needs to be less than i so i cannot be N but j can
int bitwiseAnd(int N, int K) {
    int min = 0;
    for(int i = 0; i < N; i++)
    {
        for(int j = i+1; j <= N; j++)
        if(min < (i & j) && (i & j) < K)
        {
            min = (i & j);
        }
    }
    return min;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int count = stoi(first_multiple_input[0]);

        int lim = stoi(first_multiple_input[1]);

        int res = bitwiseAnd(count, lim);

        fout << res << "\n";
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
