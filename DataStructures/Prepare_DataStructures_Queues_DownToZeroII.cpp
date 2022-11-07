/*
You are given Q queries. Each query consists of a single number N. You can perform any of the 2 operations on N in each move:
    1: If we take 2 integers a and b where N=aXb(a!=1, b!=1),
    then we can change N=max(a,b)
    2: Decrease the value of N by 1.
Determine the minimum number of moves required to reduce the
value of N to 0.
Input Format
    The first line contains the integer Q.
    The next Q lines each contain an integer, N.
Constraints
    1<=Q<=10^3
    0<=N<=10^6
Output Format
    Output Q lines. Each line containing the minimum number of
    moves required to reduce the value of N to 0.
Sample Input
    2
    3
    4
Sample Output
    3
    3
Explanation
    For test case 1, We only have one option that gives the
    minimum number of moves.
    Follow  3->  2->  1-> 0. Hence, 3 moves.
    For the case 2, we can either go 4 -> 3 -> 2 -> 1 -> 0 or
    4 -> 2 -> 1 -> 0. The 2nd option is more optimal. Hence, 3
    moves.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'downToZero' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */
 #define MAX 1000009
long long maxFac[MAX];

void preCompute(){
    // Base Case
    for(int i=0;i<4;i++){
        maxFac[i] = i;
    }

        /*

            dp[N] = min(dp[N], min(dp[N-1], dp[max(a,b)]

        */

    for(long long i=1;i<MAX;i++){
        for(long long j=1;i*j<MAX;j++){
            maxFac[i*j] = min(maxFac[i*j],min(maxFac[max(i,j)],maxFac[i*j - 1])+1);
        }
    }
}


int downToZero(int n) {
    // CallId will run preCompute function only for first query
    static int callId = 0;
    callId++;
    if(callId == 1){
        for(int i=0;i<MAX;i++){
            maxFac[i] = INT_MAX;
        }
        preCompute();
    }

    return maxFac[n];
}
/*
vector<int> maxDivisors(int n)
{
    int div = sqrt(n);
    //int div = n;
    vector<int> divisors;
    while( div >= 2)
    {
        if(n % div >= 0)
        {
            divisors.push_back(int(n/div));
            divisors.push_back(div);
            return divisors;
        }
        div--;
    }
    divisors.push_back(-1);
    return divisors;
}
int downToZero(int n)
{
    int moves = 0;
    while(n > 0)
    {
        if(n > 2)
        {
            vector<int> div = maxDivisors(n);
            if(div[0] == -1)
            {
                n--;
            }
            else
            {
                n = max(div[0], div[1]);
            }
        }
        else
        {
            n--;
        }
        moves++;
    }
    return moves;
}
*/
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        int result = downToZero(n);

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
