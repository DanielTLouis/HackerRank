/*
You are given a square grid with some cells open (.) and some blocked (X). Your
playing piece can move along any row or column until it reaches the edge of the grid
or a blocked cell. Given a grid, a start and a goal, determine the minmum number of
moves to get to the goal.
Example.
    grid=['...','.X.','...']
    startX=0
    startY=0
    goalX=1
    goalY=2
    The grid is shown below:
        ...
        .X.
        ...
    The starting position (startX, startY) = (0,0) so start in the top left corner.
    The goal is (goalX, goalY) = (1,2). The path is (0,0)->(0,2)->(1,2). It takes 2
    moves to reach the goal.
Function Description
    Complete the minimumMoves function in the editor.
    minimumMoves has the following parameter(s):
        -string grid[n]: an array of strings that represent the rows of the grid
        -int startX: starting X coordinate
        -int startY: starting Y coordinate
        -int goalX: ending X coordinate
        -int goalY: ending Y coordinate
Returns
    int: the minimum moves to reach the goal
Input Format
    The first line contains an integer n, the size of the array grid.
    Each of the next n lines contains a string of length n.
    The last line contains four space-separated integers, startX, startY, goalX, goalY
Constraints
    1<=n<=100
    0<=startX,startY,goalX,goalY<n
Sample Input
    STDIN       FUNCTION
    -----       --------
    3           grid[] size n = 3
    .X.         grid = ['.X.','.X.', '...']
    .X.
    ...
    0 0 0 2     startX = 0, startY = 0, goalX = 0, goalY = 2
Sample Output
    3
Explanation
    Here is a path that one could follow in order to reach the destination in 3 steps:
    (0,0)->(2,0)->(2,2)->(0,2).
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */
 typedef pair<int, int> Node;
struct NodeDistance
{
    Node node;
    int distance;
};

const int DIR_X[] = {0, 1,  0, -1};
const int DIR_Y[] = {1, 0, -1,  0};

int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
    Node start(startX,startY), end(goalX,goalY);

    int grid_size = int(grid.size());
    vector<vector<bool>> visited(grid_size, vector<bool>(grid_size));

    queue<NodeDistance> q_distances;

    q_distances.push({start, 0});
    visited[start.first][start.second] = true;

    while (!q_distances.empty())
    {
        NodeDistance cnd = q_distances.front();
        q_distances.pop();

        if (cnd.node == end)
            return cnd.distance;

        int x = cnd.node.first;
        int y = cnd.node.second;

        for (int dir = 0; dir < 4; dir++)
        {
            int dx = DIR_X[dir], dy = DIR_Y[dir];

            for (int i = x + dx, j = y + dy;
                 i < grid_size && i >= 0 && j < grid_size && j >= 0 && grid[i][j] == '.';
                 i = i + dx, j = j + dy)
            {
                if (!visited[i][j]) {
                    visited[i][j] = true;
                    q_distances.push({{i, j}, cnd.distance + 1});
                }
            }
        }
    }
    return -1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int startX = stoi(first_multiple_input[0]);

    int startY = stoi(first_multiple_input[1]);

    int goalX = stoi(first_multiple_input[2]);

    int goalY = stoi(first_multiple_input[3]);

    int result = minimumMoves(grid, startX, startY, goalX, goalY);

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
