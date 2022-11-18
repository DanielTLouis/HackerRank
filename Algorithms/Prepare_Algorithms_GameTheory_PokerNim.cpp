/*
Poker Nim is another 2-player game that's a simple variation on a
Nim game. The rules of the games are as follows:
    -The game starts with  piles of chips indexed from 0 to n-1.
    Each pile i (where 0<=i<n) has c_i chips.
    -The players move in alternating turns. During each move, the
    current player must perform either of the following actions:
        -Remove one or more chips from a single pile.
        -Add one or more chips to a single pile.
    -At least 1 chip must be added or removed during each turn.
    -To ensure that the game ends in finite time, a player cannot
    add chips to any pile i more than k times.
    -The player who removes the last chip wins the game.
Given the values of n, k, and the numbers of chips in each of the
n piles, determine whether the person who wins the game is the
first or second person to move. Assume both players move optimally.
Input Format
    The first line contains an integer, T, denoting the number of
    test cases.
    Each of the 2T subsequent lines defines a test case. Each test
    case is described over the following two lines:
        1.Two space-separated integers, n (the number of piles)
        and k (the maximum number of times an individual player
        can add chips to some pile i), respectively.
        2.n space-separated integers, c_0,c-1,...c_n-1, where each
        c_i describes the number of chips at pile i.
Constraints
    1<=T<=100
    1<=n,k<=100
    1<=c_i<=10^9
Output Format
    For each test case, print the name of the winner on a new line
    (i.e., either First or Second).
Sample Input
    2
    2 5
    1 2
    3 5
    2 1 3
Sample Output
    First
    Second
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'pokerNim' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY c
 */

string pokerNim(int k, vector<int> c) {
    int a = 0;
    for(int i = 0; i < c.size(); i++)
    {
        a ^= c[i];
    }
    if (a)
    {
        return "First";
    }
    return "Second";
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

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        string c_temp_temp;
        getline(cin, c_temp_temp);

        vector<string> c_temp = split(rtrim(c_temp_temp));

        vector<int> c(n);

        for (int i = 0; i < n; i++) {
            int c_item = stoi(c_temp[i]);

            c[i] = c_item;
        }

        string result = pokerNim(k, c);

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
