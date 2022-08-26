/*
Given a square grid of characters in the range ascii[a-z], rearrange elements of each
row alphabetically, ascending. Determine if the columns are also in ascending
alphabetical order, top to bottom. Return YES if they are or NO if they are not.
Example
    grid=['abc','ade','efg']
    The grid is illustrated below.
        a b c
        a d e
        e f g
    The rows are already in alphabetical order. The columns a a e, b d f and c e g are
    also in alphabetical order, so the answer would be YES. Only elements within the
    same row can be rearranged. They cannot be moved to a different row.
Function Description
    Complete the gridChallenge function in the editor below.
    gridChallenge has the following parameter(s):
        -string grid[n]: an array of strings
Returns
    string: either YES or NO
Input Format
    The first line contains t, the number of testcases.
    Each of the next t sets of lines are described as follows:
        - The first line contains , the number of rows and columns in the grid.
        - The next  lines contains a string of length n
Constraints
    1<=t<=100
    1<=n<=100
    Each string consists of lowercase letters in the range ascii[a-z]
Output Format
    For each test case, on a separate line print YES if it is possible to rearrange
    the grid alphabetically ascending in both its rows and columns, or NO otherwise.
Sample Input
    STDIN   Function
    -----   --------
    1       t = 1
    5       n = 5
    ebacd   grid = ['ebacd', 'fghij', 'olmkn', 'trpqs', 'xywuv']
    fghij
    olmkn
    trpqs
    xywuv
Sample Output
    YES
Explanation
    The 5x5 grid in the 1 test case can be reordered to
        abcde
        fghij
        klmno
        pqrst
        uvwxy
    This fulfills the condition since the rows 1, 2, ..., 5 and the columns 1, 2, ...,
    5 are all alphabetically sorted.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'gridChallenge' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING_ARRAY grid as parameter.
 */

string gridChallenge(vector<string> grid) {
    for(int i = 0; i < grid.size(); i++)
    {
        sort(grid[i].begin(), grid[i].end());
    }
    for(int i = 0; i < grid.size()-1; i++)
    {
        for(int j = 0; j < grid.size(); j++)
        {
            cout << grid[i][j] << ">" << grid[i+1][j] << endl;
            if(grid[i][j] > grid[i+1][j])
            {
                cout << "NO\n";
                return "NO";
            }
        }
    }
    return "YES";
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

        vector<string> grid(n);

        for (int i = 0; i < n; i++) {
            string grid_item;
            getline(cin, grid_item);

            grid[i] = grid_item;
        }

        string result = gridChallenge(grid);

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
