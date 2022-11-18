/*
Two people are playing game of Misère Nim. The basic rules
for this game are as follows:
    -The game starts with n piles of stones indexed from 0
    to n-1. Each pile i (where 0<=i<n) has s_i stones.
    -The players move in alternating turns. During each move,
    the current player must remove one or more stones from a
    single pile.
    -The player who removes the last stone loses the game.
Given the value of n and the number of stones in each pile,
determine whether the person who wins the game is the first
or second person to move. If the first player to move wins,
print First on a new line; otherwise, print Second. Assume
both players move optimally.
Example
    s=[1,1,1]
    In this case, player 1 picks a pile, player 2 picks a
    pile and player 1 has to choose the last pile. Player 2
    wins so return Second.
    s=[1,2,2]
    There is no permutation of optimal moves where player 2
    wins. For example, player 1 chooses the first pile. If
    player 2 chooses 1 from another pile, player 1 will
    choose the pile with 2 left. If player 2 chooses a pile
    of 2, player 1 chooses 1 from the remaining pile leaving
    the last stone for player 2. Return First.
Function Description
    Complete the misereNim function in the editor below.
    misereNim has the following parameters:
        int s[n]: the number of stones in each pile
Returns
    string: either First or Second
Input Format
    The first line contains an integer, T, the number of
    test cases.
    Each test case is described over two lines:
    1.An integer, n, the number of piles.
    2.n space-separated integers, s[i], that describe the
    number of stones at pile i.
Constraints
    1<=T<=100
    1<=n<=100
    1<=s[i]<=10^9
Sample Input
    STDIN   Function
    -----   --------
    2       T = 2
    2       s[] size n = 2
    1 1     s = [1, 1]
    3       s[] size n = 3
    2 1 3   s = [2, 1, 3]
Sample Output
    First
    Second
Explanation
    In the first testcase, the first player removes 1 stone
    from the first pile and then the second player has no
    moves other than removing the only stone in the second
    pile. So first wins.
    In the second testcase, the series of moves can be
    depicted as:
        image
    In every possible move of first player we see that the
    last stone is picked by him, so second player wins.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'misereNim' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts INTEGER_ARRAY s as parameter.
 */

string misereNim(vector<int> s) {
    int n = s.size(), xr = 0;
    bool great = false;
    for(auto i :s){
        xr ^= i;
        if(i > 1) great = true;
    }
    // Refer to: https://mathoverflow.net/questions/71802/analysis-of-misere-nim
        // (1) or (2)
    // (1) having some s[i] greater than 1 and xor of all s[i] == 0
    // (2) all s[i] <= 1 (as the constraint "1 <= s[i] <= 10^9" of this problem, then all s[i] == 1) and xor of all s[i] == 1; then second player will win;
    if((xr == 0 && great == true) || (xr == 1 && great == false))
        return "Second";
    return "First";
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

        string result = misereNim(s);

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
