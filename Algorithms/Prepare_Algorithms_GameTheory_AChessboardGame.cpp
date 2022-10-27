/*
Two players are playing a game on a 15X15 chessboard. The rules of the game are
as follows:
    -The game starts with a single coin located at some x,y coordinates. The
    coordinates of the upper left cell are (1,1), and of the lower right cell
    are (15,15).
    -In each move, a player must move the coin from cell (x,y) to one of the
    following locations:
        1.(x-2,y+1)
        2.(x-2,y-1)
        3.(x+1,y-2)
        4.(x-1,y-2)
Note: The coin must remain inside the confines of the board.
    -Beginning with player 1, the players alternate turns. The first player who
    is unable to make a move loses the game.
The figure below shows all four possible moves using an 8X8 board for
illustration:
    chess(1)
Given the initial coordinates of the players' coins, assuming optimal play,
determine which player will win the game.
Function Description
    Complete the chessboardGame function in the editor below. It should return
    a string, either First or Second.
    chessboardGame has the following parameter(s):
        x: an integer that represents the starting column position
        y: an integer that represents the starting row position
Input Format
    The first line contains an integer t, the number of test cases.
    Each of the next t lines contains 2 space-separated integers x and y.
Constraints
    1<=t<=225
    1<=x[i],y[i]<=15
Output Format
    On a new line for each test case, print First if the first player is the
    winner. Otherwise, print Second.
Sample Input
    3
    5 2
    5 3
    8 8
Sample Output
    Second
    First
    First
Explanation
    In the first case, player1 starts at the red square and can move to any of
    the blue squares. Regardless of which one is chosen, the player 2 can move
    to one of the green squares to win the game.
        image
    In the second case, player 1 starts at the red square and can move to any
    of the blue squares or the purple one. Moving to the purple one limits
    player 2 to the yellow square. From the yellow square, player 1 moves to
    the green square and wins.
        image
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'chessboardGame' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER x
 *  2. INTEGER y
 */

string chessboardGame(int x, int y) {
        x-=1;
        y-=1;
        if((x/2)%2==0 && (y/2)%2==0)
        {
            return "Second";
        }
        return "First";
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

        int x = stoi(first_multiple_input[0]);

        int y = stoi(first_multiple_input[1]);

        string result = chessboardGame(x, y);

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
