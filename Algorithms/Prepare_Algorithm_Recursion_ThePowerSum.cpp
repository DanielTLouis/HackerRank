/*
    Find the number of ways that a given integer, X, can be expressed as the sum 
    of the Nth powers of unique, natural numbers.
    For example, if X=13 and N=2, we have to find all combinations of unique 
    squares adding up to 13. The only solution is 2^2 + 3^2.
Function Description
    Complete the powerSum function in the editor below. It should return an 
    integer that represents the number of possible combinations.
    powerSum has the following parameter(s):
        X: the integer to sum to
        N: the integer power to raise numbers to
Input Format
    The first line contains an integer X.
    The second line contains an integer N.
Constraints
    1<=X<=1000
    2<=N<=10
Output Format
    Output a single integer, the number of possible combinations caclulated.
Sample Input 0
    10
    2
Sample Output 0
    1
Explanation 0
    If X=10 and N=2, we need to find the number of ways that  can be represented 
    as the sum of squares of unique numbers.
    10=1^2 + 3^2
    This is the only way in which 10 can be expressed as the sum of unique 
    squares.
Sample Input 1
    100
    2
Sample Output 1
    3
Explanation 1
    100=(10^2)=(6^2 + 8^2)=(1^2 + 3^2 + 4^2 + 5^2 + 7^2)
Sample Input 2
    100
    3
Sample Output 2
    1
Explanation 2
    100 can be expressed as the sum of the cubes of 1,2,3,4.
    (1+8+27+64=100). There is no other way to express 100 as the sum of cubes.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'powerSum' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER X
 *  2. INTEGER N
 */

void cntWays(int x, int n, int& cnt , int i){
    if(x == 0){
        cnt++;
        return ;
    }
    if(x < 0 || x < int(pow(i, n))) return;

    cntWays(x, n, cnt,i + 1);
    cntWays(x - int(pow(i, n)), n, cnt, i + 1);
}

int powerSum(int X, int N) {
    int cnt = 0;
    cntWays(X, N, cnt, 1);
    return cnt;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string X_temp;
    getline(cin, X_temp);

    int X = stoi(ltrim(rtrim(X_temp)));

    string N_temp;
    getline(cin, N_temp);

    int N = stoi(ltrim(rtrim(N_temp)));

    int result = powerSum(X, N);

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
