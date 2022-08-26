/*
There is an undirected tree where each vertex is numbered from 1 to n, and each
contains a data value. The sum of a tree is the sum of all its nodes' data
values. If an edge is cut, two smaller trees are formed. The difference between
two trees is the absolute value of the difference in their sums.
Given a tree, determine which edge to cut so that the resulting trees have a
minimal difference between them, then return that difference.
Example
  data=[1,2,3,4,5,6]
  edges=[(1,2),(1,3),(2,6),(3,4),(3,5)]
  In this case, node numbers match their weights for convenience. The graph is
  shown below.
  image
  The values are calculated as follows:
    Edge    Tree 1  Tree 2  Absolute
    Cut     Sum      Sum     Difference
    1        8         13         5
    2        9         12         3
    3        6         15         9
    4        4         17        13
    5        5         16        11
  The minimum absolute difference is 3.
  Note: The given tree is always rooted at vertex ``.
Function Description
  Complete the cutTheTree function in the editor below.
  cutTheTree has the following parameter(s):
    -int data[n]: an array of integers that represent node values
    -int edges[n-1][2]: an 2 dimensional array of integer pairs where each pair
    represents nodes connected by the edge
Returns
int: the minimum achievable absolute difference of tree sums
Input Format
  The first line contains an integer n, the number of vertices in the tree.
  The second line contains n space-separated integers, where each integer u
  denotes the node[u] data value, data[u].
  Each of the n-1 subsequent lines contains two space-separated integers u and v
  that describe edge u<->v in tree t.
Constraints
  3<=n<=10^5
  1<=data[u]<=1001, where 1<=u<=n.
Sample Input
  STDIN                       Function
  -----                       --------
  6                           data[] size n = 6
  100 200 100 500 100 600     data = [100, 200, 100, 500, 100, 600]
  1 2                         edges = [[1, 2], [2, 3], [2, 5], [4, 5], [5, 6]]
  2 3
  2 5
  4 5
  5 6
Sample Output
  400
Explanation
  We can visualize the initial, uncut tree as:
    cut-the-tree.png
  There are n-1=5 edges we can cut:
  Edge 1<->2 results in d_1<->2=1500-100=1400
  Edge 2<->3 results in d_2<->3=1500-100=1400
  Edge 2<->5 results in d_2<->5=1200-400=800
  Edge 4<->5 results in d_4<->5=1100-500=600
  Edge 5<->6 results in d_5<->6=1000-600=400
  The minimum difference is 400.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

vector<int> bfs(int n, int m, vector<vector<int>> edges, int s) {
    //transform edges into adjacency lists
    vector<list<int>> adj_list;
    adj_list.resize(n);
    for(auto edge: edges)
    {
        int u = edge[0];
        int v = edge[1];
        int u_idx = edge[0] - 1;
        int v_idx = edge[1] - 1;
        adj_list[u_idx].push_back(v);
        adj_list[v_idx].push_back(u);
    }

    //initialize two arrays holding
    //1. whether path to node from s has been found
    //2. respective distance from s
    bool found[n];
    vector<int> dist;
    for(int i = 0; i < n; i++)
    {
        found[i] = false;
        dist.push_back(-1);
    }
    int idx_s = s-1;
    found[idx_s] = true;
    dist[idx_s] = 0;

    //initialize queue holding only s in the beginning
    queue<int> q;
    q.push(s);

    //queue q marks boundary between visited and unvisited area.
    //while loop ends when all nodes have been visited
    while(!q.empty())
    {
        int u = q.front();
        int idx_u = u - 1;

        //remove first node from q and add every of its unvisited neighbor to q's end.
        //then mark every neighbor as visited
        //their distance is by 6 bigger than the parent node
        q.pop();
        for(auto v: adj_list[idx_u])
        {
            int idx_v = v - 1;
            if(false == found[idx_v])
            {
                found[idx_v] = true;
                dist[idx_v] = dist[idx_u]+6;
                q.push(v);
            }
        }
    }

    //remove starting node from distance vector to match solution.
    dist.erase(dist.begin() + idx_s);
    return dist;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        vector<vector<int>> edges(m);

        for (int i = 0; i < m; i++) {
            edges[i].resize(2);

            string edges_row_temp_temp;
            getline(cin, edges_row_temp_temp);

            vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int edges_row_item = stoi(edges_row_temp[j]);

                edges[i][j] = edges_row_item;
            }
        }

        string s_temp;
        getline(cin, s_temp);

        int s = stoi(ltrim(rtrim(s_temp)));

        vector<int> result = bfs(n, m, edges, s);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
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
