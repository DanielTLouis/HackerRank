/*
Consider an undirected graph where each edge weighs 6 units. Each of the nodes
is labeled consecutively from 1 to n.
You will be given a number of queries. For each query, you will be given a list
of edges describing an undirected graph. After you create a representation of
the graph, you must determine and report the shortest distance to each of the
other nodes from a given starting position using the breadth-first search
algorithm (BFS). Return an array of distances from the start node in node number
order. If a node is unreachable, return -1 for that node.
Example
  The following graph is based on the listed inputs:
    image
  n=5 // number of nodes
  m=3 // number of edges
  edges=[1,2],[1,3],[3,4]
  s=1 // starting node
  All distances are from the start node 1. Outputs are calculated for distances
  to nodes 2 through 5: [6,6,12-1]. Each edge is 6 units, and the unreachable
  node 5 has the required return distance of -1.
Function Description
  Complete the bfs function in the editor below. If a node is unreachable, its
  distance is -1.
  bfs has the following parameter(s):
    -int n: the number of nodes
    -int m: the number of edges
    -int edges[m][2]: start and end nodes for edges
    -int s: the node to start traversals from
Returns
  int[n-1]: the distances to nodes in increasing node number order, not
  including the start node (-1 if a node is not reachable)
Input Format
  The first line contains an integer q, the number of queries. Each of the
  following q sets of lines has the following format:
    -The first line contains two space-separated integers n and m, the number of
    nodes and edges in the graph.
    -Each line i of the m subsequent lines contains two space-separated
    integers, u and v, that describe an edge between nodes u and v.
    -The last line contains a single integer, s, the node number to start from.
Constraints
  1<=q<=10
  2<=n<=1000
  1<=m<=(n(n-1))/2
  1<=u,v,s<=n
Sample Input
  2
  4 2
  1 2
  1 3
  1
  3 1
  2 3
  2
Sample Output
  6 6 -1
  -1 6
Explanation
  We perform the following two queries:
  1.The given graph can be represented as:
    image
    where our start node, s, is node 1. The shortest distances from s to the
    other nodes are one edge to node 2, one edge to node 3, and an infinite
    distance to node 4 (which it is not connected to). We then return an array
    of distances from node 1 to nodes 2, 3, and 4 (respectively): [6,6,-1].
  2.The given graph can be represented as:
    image
    where our start node, s, is node 2. There is only one edge here, so node 1
    is unreachable from node 2 and node 3 has one edge connecting it to node 2.
    We then return an array of distances from node 2 to nodes 1, and 3
    (respectively): [-1,6].
  Note: Recall that the actual length of each edge is 6, and we return -1 as the
  distance to any node that is unreachable from s.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'cutTheTree' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY data
 *  2. 2D_INTEGER_ARRAY edges
 */
struct c_node {
    int num, data, sum;
    vector<c_node*> children;
    c_node* parent;
    c_node(int n, int d) {
        num = n;
        data = d;
        sum = d;
        parent = nullptr;
    }
};
int cutTheTree(vector<int> data, vector<vector<int>> edges) {
    int n = (int)data.size();
    map<int, c_node*> nodes;
    c_node* root = nullptr;
    for (vector<int> edge : edges) {
        int p = edge[0], q = edge[1];
        if (nodes.find(p) == nodes.end())
            nodes.insert({p, new c_node(p, data[p - 1])});
        if (nodes.find(q) == nodes.end())
            nodes.insert({q, new c_node(q, data[q - 1])});
        if (root == nullptr)
            root = nodes[p];
        nodes[p]->children.push_back(nodes[q]);
        nodes[q]->children.push_back(nodes[p]);
    }
    vector<c_node*> arr;
    arr.push_back(root);
    int visited[n + 1] = {0};
    visited[root->num]++;
    int i = 0, j = 1;
    while (i < j) {
        for (c_node* child : arr[i]->children) {
            if (!visited[child->num]) {
                visited[child->num]++;
                child->parent = arr[i];
                arr.push_back(child);
                j++;
            }
        }
        i++;
    }
    for (i = n - 1; i >= 0; i--)
        if (arr[i]->parent != nullptr)
            arr[i]->parent->sum += arr[i]->sum;
    int total = 0;
    for (i = 0; i < n; i++)
        total += data[i];
    int diff = INT32_MAX;
    for (i = 0; i < n; i++)
        diff = min(diff, abs((total - arr[i]->sum) - arr[i]->sum));
    return diff;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string data_temp_temp;
    getline(cin, data_temp_temp);

    vector<string> data_temp = split(rtrim(data_temp_temp));

    vector<int> data(n);

    for (int i = 0; i < n; i++) {
        int data_item = stoi(data_temp[i]);

        data[i] = data_item;
    }

    vector<vector<int>> edges(n - 1);

    for (int i = 0; i < n - 1; i++) {
        edges[i].resize(2);

        string edges_row_temp_temp;
        getline(cin, edges_row_temp_temp);

        vector<string> edges_row_temp = split(rtrim(edges_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int edges_row_item = stoi(edges_row_temp[j]);

            edges[i][j] = edges_row_item;
        }
    }

    int result = cutTheTree(data, edges);

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
