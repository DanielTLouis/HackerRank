/*
People connect with each other in a social network. A connection between Person i and
Person j is represented as Mij. When two persons belonging to different communities
connect, the net effect is the merge the communities which i and j belong to.
At the beginning, there are n people representing n communities. Suppose person 1 and 2
connected and later 2 and 3 connected, then 1,2, and 3 will belong to the same community.
There are two types of queries:
    1. Mij -> communities containing persons  and  are merged if they belong to
    different communities.
    2. Qi -> print the size of the community to which person  belongs.
Input Format
    The first line of input contains 2 space-separated integers n and q, the number of
    people and the number of queries.
    The next q lines will contain the queries.
Constraints
    1<=n<=10^5
    1<=q<=2X10^5
Output Format
    The output of the queries.
Sample Input
    STDIN Function ----- -------- 3 6 n = 3, q = 6 Q 1 print the size of the community
    containing person 1 M 1 2 merge the communities containing persons
    1 and 2 ... Q 2 M 2 3 Q 3 Q 2
Sample Output
    1
    2
    3
    3
Explanation
    Initial size of each of the community is 1.
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class UnionFind{
private:
    vector<int> parent;
    vector<int> cnt;
public:
    UnionFind(int size) : parent(size+1), cnt(size+1)
    {
        for (int i = 1; i <= size; ++i) {
            parent[i] = i;
            cnt[i] = 1;
        }
    }

    int find(int node) {
        if(node == parent[node]) return node;
        return parent[node] = find(parent[node]);
    }

    int totalNodesInSet(int node) {
        return cnt[find(node)];
    }

    void Union(int a, int b) {
        a = find(a);
        b = find(b);

        if(a==b) return;

        parent[b] = a;
        cnt[a] += cnt[b];
    }
};

int main() {
    int n, q;
    cin>>n>>q;
    UnionFind uf(n);
    while(q--) {
        char c; cin>>c;
        if(c=='M') {
            int a, b; cin>>a>>b;
            uf.Union(a,b);
        } else {
            int a; cin>>a;
            cout << uf.totalNodesInSet(a) << "\n";
        }
    }
    return 0;
}
