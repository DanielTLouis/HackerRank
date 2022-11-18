/*
A cricket match is going to be held. The field is represented
by a 1D plane. A cricketer, Mr. X has N favorite shots. Each
shot has a particular range. The range of the ith  shot is from
A_i to B_i. That means his favorite shot can be anywhere in
this range. Each player on the opposite team can field only in
a particular range. Player i can field from C_i to D_i. You are
given the N favorite shots of Mr. X and the range of M players.
Si represents the strength of each player i.e. the number of
shots player i can stop.
Your task is to find:
Summantion(Si)For(i=1, m).
Game Rules: A player can stop the ith shot if the range
overlaps with the player's fielding range.
For more clarity about overlapping, study the following figure:
    L.png
Input Format
    The first line consists of two space separated integers, N
    and M.
    Each of the next N lines contains two space separated
    integers. The ith line contains A_i and B_i.
    Each of the next M lines contains two integers. The ith
    line contains integers C_i and D_i.
Output Format
    You need to print the sum of the strengths of all the
    players: Sumation(Si)For(i=1 upperbound m).
Constraints:
    1<=N,M<=10^5
    1<=A_i,B-i,C_i,D_i<=10^9
Sample Input
    4 4
    1 2
    2 3
    4 5
    6 7
    1 5
    2 3
    4 7
    5 7
Sample Output
    9
Explanation
    Player 1 can stop the 1st, 2nd and 3rd shot so the strength
    is 3.
    Player 2 can stop the 1st and 2nd shot so the strength is 2.
    Player 3 can stop the 3rd and 4th shot so the strength is 2.
    Player 4 can stop the 3rd and 4th shot so the strength is 2.
    The sum of the strengths of all the players is 3+2+2+2=9.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY shots
 *  2. 2D_INTEGER_ARRAY players
 */

int solve(vector<vector<int>> shots, vector<vector<int>> players) {
    if (shots.empty() || players.empty())
        return 0;

    std::vector<int> shotsStartingPointList(shots.size(), 0);
    std::vector<int> shotsEndingPointList(shots.size(), 0);

    for (auto idx = 0; idx < shots.size(); ++idx)
    {
        shotsStartingPointList[idx] = shots[idx][0];
        shotsEndingPointList[idx] = shots[idx][1];
    }

    std::sort(shotsStartingPointList.begin(), shotsStartingPointList.end());
    std::sort(shotsEndingPointList.begin(), shotsEndingPointList.end());

    auto savedShorts = 0;
    auto missedShots = 0;

    for (const auto playersRange : players)
    {
        missedShots += static_cast<int>(std::lower_bound(shotsEndingPointList.begin(), shotsEndingPointList.end(), playersRange[0]) - shotsEndingPointList.begin());
        savedShorts += static_cast<int>(std::upper_bound(shotsStartingPointList.begin(), shotsStartingPointList.end(), playersRange[1]) - shotsStartingPointList.begin());
    }
    return (savedShorts - missedShots);
    /*int blocks = 0;
    for(int j = 0; j < players.size(); j++)
    {
        for(int i = 0; i < shots.size(); i++)
        {
            if(players[j][0] < shots[i][0] && players[j][1] > shots[i][1]){
                blocks++;
            }
        }
    }

    return blocks;
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<vector<int>> shots(n);

    for (int i = 0; i < n; i++) {
        shots[i].resize(2);

        string shots_row_temp_temp;
        getline(cin, shots_row_temp_temp);

        vector<string> shots_row_temp = split(rtrim(shots_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int shots_row_item = stoi(shots_row_temp[j]);

            shots[i][j] = shots_row_item;
        }
    }

    vector<vector<int>> players(m);

    for (int i = 0; i < m; i++) {
        players[i].resize(2);

        string players_row_temp_temp;
        getline(cin, players_row_temp_temp);

        vector<string> players_row_temp = split(rtrim(players_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int players_row_item = stoi(players_row_temp[j]);

            players[i][j] = players_row_item;
        }
    }

    int result = solve(shots, players);

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
