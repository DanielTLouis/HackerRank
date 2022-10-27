/*
You are given a square map as a matrix of integer strings. Each cell of the map 
has a value denoting its depth. We will call a cell of the map a cavity if and 
only if this cell is not on the border of the map and each cell adjacent to it 
has strictly smaller depth. Two cells are adjacent if they have a common side, or 
edge.
Find all the cavities on the map and replace their depths with the uppercase 
character X.
Example
    grid=['989','191','111']
    The grid is rearranged for clarity:
        989
        191
        111
    Return:
        989
        1X1
        111
    The center cell was deeper than those on its edges: [8,1,1,1]. The deep cells 
    in the top two corners do not share an edge with the center cell, and none of 
    the border cells is eligible.
Function Description
    Complete the cavityMap function in the editor below.
    cavityMap has the following parameter(s):
        string grid[n]: each string represents a row of the grid
Returns
    string{n}: the modified grid
Input Format
    The first line contains an integer n, the number of rows and columns in the 
    grid.
    Each of the following n lines (rows) contains n positive digits without 
    spaces (columns) that represent the depth at grid[row, column].
Constraints
    1<=n<=100
Sample Input
    STDIN   Function
    -----   --------
    4       grid[] size n = 4
    1112    grid = ['1112', '1912', '1892', '1234']
    1912
    1892
    1234
Sample Output
    1112
    1X12
    18X2
    1234
Explanation
    The two cells with the depth of 9 are not on the border and are surrounded on 
    all sides by shallower cells. Their values are replaced by X.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'cavityMap' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY grid as parameter.
 */

vector<string> cavityMap(vector<string> grid) {
    for(int i = 1; i < grid.size()-1; i++)
    {
        for(int j = 1; j < grid[i].size()-1; j++){
            if(grid[i][j] > grid[i-1][j] && grid[i][j] > grid[i+1][j] 
                && grid[i][j]>grid[i][j-1] && grid[i][j] > grid[i][j+1]){
                grid[i][j] = 'X'; 
            }
        }
        cout << endl;
    }
    return grid;
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

    vector<string> result = cavityMap(grid);

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