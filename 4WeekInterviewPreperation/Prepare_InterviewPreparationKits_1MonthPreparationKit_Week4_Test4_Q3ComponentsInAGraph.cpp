/*
There are 2XN nodes in an undirected graph, and a number of edges connecting
some nodes. In each edge, the first value will be between 1 and N, inclusive.
The second node will be between N+1 and 2XN, inclusive. Given a list of edges,
determine the size of the smallest and largest connected components that have 2
or more nodes. A node can have any number of connections. The highest node value
will always be connected to at least  other node.
Note Single nodes should not be considered in the answer.
Example
  bg=[[1,5],[1,6],[2,4]]
    image
  The smaller component contains 2 nodes and the larger contains 3. Return the
  array [2,3].
Function Description
  Complete the connectedComponents function in the editor below.
  connectedComponents has the following parameter(s):
    - int bg[n][2]: a 2-d array of integers that represent node ends of graph
    edges
Returns
  - int[2]: an array with 2 integers, the smallest and largest component sizes
Input Format
  The first line contains an integer n, the size of bg.
  Each of the next n lines contain two space-separated integers, bg[i][0] and
  bg[i][1].
Constraints
  1<=numberofnodesN<=15000
  1<=bg[i][0]<=N
  N+1<=bg[i][1]<=2N
Sample Input
  STDIN   Function
  -----   --------
  5       bg[] size n = 5
  1 6     bg = [[1, 6],[2, 7], [3, 8], [4,9], [2, 6]]
  2 7
  3 8
  4 9
  2 6
Sample Output
  2 4
Explanation
    image
  Since the component with node 5 contains only one node, it is not considered.
  The number of vertices in the smallest connected component in the graph is 2
  based on either (3,8) or (4,9).
  The number of vertices in the largest connected component in the graph is 4
  i.e. 1-2-6-7.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'componentsInGraph' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_INTEGER_ARRAY gb as parameter.
 */
int find(vector<int> &v,int n){
    if(v[n] < 0){
        return n;
    }
    else {
        return v[n] = find(v,v[n]);
    }
}
vector<int> componentsInGraph(vector<vector<int>> gb) {
    int n = gb.size();
    int min = INT_MAX;
    int max = INT_MIN;
    vector<int> v(n*2+1,-1);
    for(int i = 0; i < n; i++){
        int x = find(v,gb[i][0]);
        int y = find(v,gb[i][1]);
        if(x == y) continue;

        v[x] += v[y];
        v[y] = x;
    }
    sort(v.begin(),v.end());
    max = abs(v[0]);
    for (int i=0;i<=2*n;i++) {
        if(v[i] < 0){
            int x = abs(v[i]);
            if (x>1 && x<min) min=x;
        }
        else break;
    }
    return {min,max};
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> gb(n);

    for (int i = 0; i < n; i++) {
        gb[i].resize(2);

        string gb_row_temp_temp;
        getline(cin, gb_row_temp_temp);

        vector<string> gb_row_temp = split(rtrim(gb_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int gb_row_item = stoi(gb_row_temp[j]);

            gb[i][j] = gb_row_item;
        }
    }

    vector<int> result = componentsInGraph(gb);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
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
