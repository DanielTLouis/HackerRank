/*
Louise and Richard have developed a numbers game. They pick a number and check to see
if it is a power of 2. If it is, they divide it by 2. If not, they reduce it by the
next lower number which is a power of 2. Whoever reduces the number to 1 wins the
game. Louise always starts.
Given an initial value, determine who wins the game.
Example
    n=132
    It's Louise's turn first. She determines that 132 is not a power of 2. The next
    lower power of 2 is 128, so she subtracts that from 132 and passes 4 to Richard. 4
     is a power of 2, so Richard divides it by 2 and passes 2 to Louise. Likewise, 2
     is a power so she divides it by and reaches 1. She wins the game.
    Update If they initially set counter to 1, Richard wins. Louise cannot make a move
    so she loses.
Function Description
    Complete the counterGame function in the editor below.
    counterGame has the following parameter(s):
        -int n: the initial game counter value
Returns
    string: either Richard or Louise
Input Format
    The first line contains an integer t, the number of testcases.
    Each of the next t lines contains an integer n, the initial value for each game.
Constraints
    1<=t<=10
    1<=n<=2^64 - 1
Sample Input
    1
    6
Sample Output
    Richard
Explanation
    As 6 is not a power of 2, Louise reduces the largest power of 2 less than 6 i.e.,
    4, and hence the counter reduces to 2.
    As 2 is a power of 2, Richard reduces the counter by half of 2 i.e., 1. Hence the
    counter reduces to 1.
    As we reach the terminating condition with N==1, Richard wins the game.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'counterGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts LONG_INTEGER n as parameter.
 */

string counterGame(long n) {
    int cnt = 0;
    long mask = (1L << 62);
    while(n!=1)
    {
        while(mask > n)
        {
            mask >>= 1;//bitwise masking
                        // if mask > "n" , means mask should be smaller => shift right
        }
        if(mask==n) n >>=1; // rule 2
        else if(n > mask) n-=mask; // rule 1
        cnt++;
    }
    return (cnt&1)?"Louise":"Richard";
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        long n = stol(ltrim(rtrim(n_temp)));

        string result = counterGame(n);

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
