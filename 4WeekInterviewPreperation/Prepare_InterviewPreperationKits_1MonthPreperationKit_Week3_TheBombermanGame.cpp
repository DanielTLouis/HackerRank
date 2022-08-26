/*
Bomberman lives in a rectangular grid. Each cell in the grid either contains a bomb or
nothing at all.
Each bomb can be planted in any cell of the grid but once planted, it will detonate
after exactly 3 seconds. Once a bomb detonates, it's destroyed — along with anything
in its four neighboring cells. This means that if a bomb detonates in cell , any valid
cells and  are cleared. If there is a bomb in a neighboring cell, the neighboring bomb
is destroyed without detonating, so there's no chain reaction.
Bomberman is immune to bombs, so he can move freely throughout the grid. Here's what
he does:
    1.Initially, Bomberman arbitrarily plants bombs in some of the cells, the initial
    state.
    2.After one second, Bomberman does nothing.
    3.After one more second, Bomberman plants bombs in all cells without bombs, thus
    filling the whole grid with bombs. No bombs detonate at this point.
    4.After one more second, any bombs planted exactly three seconds ago will
    detonate. Here, Bomberman stands back and observes.
    5.Bomberman then repeats steps 3 and 4 indefinitely.
Note that during every second Bomberman plants bombs, the bombs are planted
simultaneously (i.e., at the exact same moment), and any bombs planted at the same
time will detonate at the same time.
Given the initial configuration of the grid with the locations of Bomberman's first
batch of planted bombs, determine the state of the grid after  seconds.
For example, if the initial grid looks like:
    ...
    .O.
    ...
it looks the same after the first second. After the second second, Bomberman has
placed all his charges:
    OOO
    OOO
    OOO
At the third second, the bomb in the middle blows up, emptying all surrounding cells:
    O.O
    ...
    O.O
Function Description
    Complete the bomberMan function in the editory below.
    bomberMan has the following parameter(s):
        -int n: the number of seconds to simulate
        -string grid[r]: an array of strings that represents the grid
Returns
    string[r]: n array of strings that represent the grid in its final state
Input Format
    The first line contains three space-separated integers , , and , The number of
    rows, columns and seconds to simulate.
    Each of the next  lines contains a row of the matrix as a single string of
    characters. The . character denotes an empty cell, and the O character (ascii 79)
    denotes a bomb.
Constraints
    1<=r,c<=200
    1<=n<=10^9
Subtask
    1<=n<=200 for 40% of the maximum score.
Sample Input
    STDIN           Function
    -----           --------
    6 7 3           r = 6, c = 7, n = 3
    .......         grid =['.......', '...O...', '....O..',\
    ...O...                '.......', 'OO.....', 'OO.....']
    ....O..
    .......
    OO.....
    OO.....
Sample Output
    OOO.OOO
    OO...OO
    OOO...O
    ..OO.OO
    ...OOOO
    ...OOOO
Explanation
    The initial state of the grid is:
        .......
        ...O...
        ....O..
        .......
        OO.....
        OO.....
    Bomberman spends the first second doing nothing, so this is the state after 1
    second:
        .......
        ...O...
        ....O..
        .......
        OO.....
        OO.....
    Bomberman plants bombs in all the empty cells during his second second, so this is
    the state after 2 seconds:
        OOOOOOO
        OOOOOOO
        OOOOOOO
        OOOOOOO
        OOOOOOO
        OOOOOOO
    In his third second, Bomberman sits back and watches all the bombs he planted 3
    seconds ago detonate. This is the final state after 3 seconds:
        OOO.OOO
        OO...OO
        OOO...O
        ..OO.OO
        ...OOOO
        ...OOOO
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

vector<string> funct1(vector<string> _grid){
    vector<string> grid(_grid.size(),(string(_grid[0].size(),'O')));
    int n = _grid.size();
    int k = _grid[0].length();
    for(int i =0; i<_grid.size(); i++) {
        for (int j=0; j<_grid[0].length(); j++) {
            bool is = (i>0 && _grid[i-1][j]=='O')||(i+1<n && _grid[i+1][j]=='O')||(j>0 && _grid[i][j-1]=='O')||(j+1<k && _grid[i][j+1]=='O')||_grid[i][j]=='O';
            if(is==true){
                grid[i][j]='.';
            }
        }
    }
    return grid;
}
vector<string> funct2(vector<string> _grid){
        return funct1(funct1(_grid));
}
vector<string> funct3(vector<string> _grid){
    return funct1(funct2(_grid));
}


vector<string> bomberMan(int n, vector<string> grid) {
    int m;
if(n%2==0){
    for (int i =0; i<grid.size(); i++) {
        for (int j=0; j<grid[0].length(); j++) {
             grid[i][j]='O';
        }
    }
}
else {
    if(n==1){
        return grid;
    }
    m = ((n-1)/2)%2;
    if(m==1){
            return funct3(grid);
    }
    else {
            return funct2(grid);
    }
}
return grid;
}
/* idk whats wrong here
*
 * Funciton blow
 *
 *Takes vector of vector representing the grid as argument and the position
 *of the blown part, returns the new grid with empty spaces where bombs blew
 *
vector<vector<int>> blow(vector<vector<int>> &grid, int i, int j)
{


    if(i == 0)
    {
        if(j == 0)
        {
            grid[i][j] = 0;
            grid[i+1][j] = 0;
            grid[i][j+1] = 0;
        }
        else
        {
            grid[i][j] = 0;
            grid[i+1][j] = 0;
            grid[i][j+1] = 0;
            grid[i][j-1] = 0;
        }
    }
    else if(i == grid.size() - 1)
    {
        if(j == grid[i].size() - 1)
        {
            grid[i][j] = 0;
            grid[i-1][j] = 0;
            grid[i][j-1] = 0;
        }
        else
        {
            grid[i][j] = 0;
            grid[i-1][j] = 0;
            grid[i][j-1] = 0;
            grid[i][j+1] = 0;
        }
    }
    else
    {
        grid[i][j] = 0;
        grid[i+1][j] = 0;
        grid[i-1][j] = 0;
        grid[i][j+1] = 0;
        grid[i][j-1] = 0;

    }
    return grid;
}
//funciton sub seconds
vector<vector<int>> subSeconds(vector<vector<int>> &grid)
{
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j] != 0)
            {
                grid[i][j] -= 1;
                if(grid[i][j] == 1)
                {
                    blow(grid, i, j);
                    continue;
                }
            }
        }
    }
    return grid;
}
//function move one
vector<vector<int>> moveOne(vector<vector<int>> &grid)
{
    return grid;
}
//function move two
vector<vector<int>> moveTwo(vector<vector<int>> &grid)
{
    subSeconds(grid);
    return grid;
}
//function move three
vector<vector<int>> moveThree(vector<vector<int>> &grid)
{
    //subSeconds(grid);
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[i].size(); j++)
        {
            if(grid[i][j] == 0)
            {
                grid[i][j] = 4;
            }
        }
    }
    subSeconds(grid);
    return grid;
}
//funciton move four
vector<vector<int>> moveFour(vector<vector<int>> &grid)
{
    subSeconds(grid);
    return grid;
}
*
 * Complete the 'bomberMan' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. STRING_ARRAY grid
 *
vector<string> bomberMan(int n, vector<string> grid) {
    vector<vector<int>> nGrid;
    for(int i = 0; i < grid.size(); i++)
    {
        vector<int> temp;
        for(int j = 0; j < grid[i].length(); j++)
        {
            if(grid[i][j] == 'O')
            {
                temp.push_back(4);
            }
            else
            {
                temp.push_back(0);
            }
        }
        nGrid.push_back(temp);
    }
    cout << "n Startig " << n << endl;
    for(int i = 1; i <= n; i++)
    {
        if(i == 1)
        {
            //call function move one
            cout << "one\n";
            moveOne(nGrid);
        }
        else if(i == 2){
            //call funciton move two
            cout << "two\n";
            moveTwo(nGrid);
        }
        else if(i % 2 == 0)
        {
            //call function move four
            cout << "four\n";
            moveFour(nGrid);
        }
        else {
            //call function move three
            cout << "three\n";
            moveThree(nGrid);
        }
    }
    //need to rebuild grid from nGrid back to grid
    for(int i = 0; i < nGrid.size(); i++)
    {
        for(int j = 0; j < nGrid[i].size(); j++)
        {
            cout << nGrid[i][j];
        }
        cout << endl;
    }
    return grid;
}
*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int r = stoi(first_multiple_input[0]);

    int c = stoi(first_multiple_input[1]);

    int n = stoi(first_multiple_input[2]);

    vector<string> grid(r);

    for (int i = 0; i < r; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    vector<string> result = bomberMan(n, grid);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
