/*
Two people are playing Nimble! The rules of the game are:
    -The game is played on a line of n squares, indexed from 0 to n-1.
    Each square i (where 0<=i<n) contains c_i coins. For example:
        nimble.png
    -The players move in alternating turns. During each move, the
    current player must remove exactly 1 coin from square i and move
    it to square j if and only if 0<=j<i.
    -The game ends when all coins are in square 0 and nobody can make
    a move. The first player to have no available move loses the game.
Given the value of n and the number of coins in each square, determine
whether the person who wins the game is the first or second person to
move. Assume both players move optimally.
Input Format
    The first line contains an integer, T, denoting the number of test
    cases.
    Each of the 2T subsequent lines defines a test case. Each test
    case is described over the following two lines:
        1.An integer, n, denoting the number of squares.
        2.n space-separated integers, c_0,c_1,...,c_n-1, where each
        c_i describes the number of coins at square .
Constraints
    1<=T<=10^4
    1<=n<=100
    0<=c_i<=10^9
Output Format
    For each test case, print the name of the winner on a new line
    (i.e., either Frist or Second).
Sample Input
    2
    5
    0 2 3 0 6
    4
    0 0 0 0
Sample Output
    First
    Second
Explanation
    Explanation for 1st testcase:
    The first player will shift one coin from square_2 to square_0.
    Hence, the second player is left with the squares [1,2,2,0,6]. Now
    whatever be his/her move is, the first player can always nullify
    the change by shifting a coin to the same square where he/she
    shifted it. Hence the last move is always played by the first
    player, so he wins.
    Exlanation for 2nd testcase:
    There are no coins in any of the squares so the first player
    cannot make any move, hence second player wins.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'nimbleGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER_ARRAY s as parameter.
 */

string nimbleGame(vector<int> s) {
    // refer to: https://en.wikipedia.org/wiki/Nim
    int xr = 0, iter = 0;
    for(auto num : s){
        if(num % 2 == 1){
            xr ^= iter;
        }
        iter++;
    }
    if(xr != 0) return "First";
    return "Second";
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

        int n = stoi(ltrim(rtrim(n_temp)));

        string s_temp_temp;
        getline(cin, s_temp_temp);

        vector<string> s_temp = split(rtrim(s_temp_temp));

        vector<int> s(n);

        for (int i = 0; i < n; i++) {
            int s_item = stoi(s_temp[i]);

            s[i] = s_item;
        }

        string result = nimbleGame(s);

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
