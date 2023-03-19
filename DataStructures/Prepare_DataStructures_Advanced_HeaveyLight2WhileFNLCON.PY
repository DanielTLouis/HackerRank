/*
White Falcon was amazed by what she can do with heavy-light decomposition on trees. As a
resut, she wants to improve her expertise on heavy-light decomposition. Her teacher gave
her an another assignment which requires path updates. As always, White Falcon needs
your help with the assignment.
You are given a tree with N nodes and each node's value vali is initially 0.
Let's denote the path from node u to node v like this: p1,p2,3....,pk where p1=u and
pk=v, and pi and pi+1 are connected.
The problem asks you to operate the following two types of queries on the tree:
"1 u v x" Add x to val_pi, 2x to val_p2,  to , ...,  kx to val_pk.
"2 u v" print the sum of the nodes' values on the path between u and v at modulo
10^9 + 7.
Input Format
    First line cosists of two integers N and Q seperated by a space.
    Following N-1 lines contains two integers which denote the undirectional edges of
    the tree.
    Following Q lines contains one of the query types described above.
    Note: Nodes are numbered by using 0-based indexing.
Constraints
    1<=N,Q<=50000
    0<=x<=10^9 + 7
Output Format
    For every query of second type print a single integer.
Sample Input
    3 2
    0 1
    1 2
    1 0 2 1
    2 1 2
Sample Output
    5
Explanation
    After the first type of query, val0=1, val1=2, val2=3. Hence the answer of the
    second query is 2+3=5.
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const long long mod = 1000000007ll;
const long long inv2 = 500000004ll;
const int N = 50010;

long long calc(long long _n, long long _a, long long _d){
    long long ans = (_a + _a + (_n - 1) * _d) % mod;
    ans = (ans * _n) % mod;
    ans = (ans * inv2) % mod;
    return ans;
}

class node {
  public:
    int l, r;
    long long sum, a, d;
    node *left, *right;

    void propagate(void){
        if(a == 0 and d == 0) return;
        int mid = (l + r) / 2;
        left->update(l, mid, a, d);
        long long nw_a = (a + (mid - l + 1) * d) % mod;
        right->update(mid+1, r, nw_a, d);
        sum = (left->sum + right->sum) % mod;
        a = d = 0ll;
    }

    void update(int x, int y, long long _a, long long _d){
        if(y < l or r < x) return;
        if(x <= l and r <= y){
            sum = (sum + calc(r - l + 1, _a, _d)) % mod;
            a = (a + _a) % mod;
            d = (d + _d) % mod;
            return;
        }
        propagate();
        int mid = (l + r) / 2;
        if(y <= mid){
            left->update(x, y, _a, _d);
        } else if(mid < x){
            right->update(x, y, _a, _d);
        } else {
            left->update(x, mid, _a, _d);
            long long nw_a = (_a + (mid - x + 1) * _d) % mod;
            right->update(mid+1, y, nw_a, _d);
        }
        sum = (left->sum + right->sum) % mod;
    }

    long long query(int x, int y){
        if(y < l or r < x) return 0ll;
        if(x <= l and r <= y) return sum;
        propagate();
        return (left->query(x, y) + right->query(x, y)) % mod;
    }
    node(int _l, int _r) : l(_l), r(_r), sum(0ll), a(0ll), d(0ll){}
};

node* init(int l, int r){
    node *p = new node(l, r);
    if(l < r){
        int mid = (l + r) / 2;
        p->left = init(l, mid);
        p->right = init(mid+1, r);
    }
    return p;
}

vector<int> adj[N];
int n, q;
vector<int> Path[N];
node* head[N];
int G[N], H[N], P[N], pos[N], sz[N];

void dfs_init(int u, int p, int h){
    H[u] = h;
    P[u] = p;
    sz[u] = 1;
    for(int v : adj[u]){
        if(v == p) continue;
        dfs_init(v, u, h+1);
        sz[u] += sz[v];
    }
}

void dfs_HLD(int u){
    Path[u].push_back(u);
    for(int i = 0;i < Path[u].size();i++){
        int v = Path[u][i];
        G[v] = u;
        pos[v] = i;
        for(int vv : adj[v]){
            if(vv == P[v]) continue;
            if(2*sz[vv] >= sz[v]){
                Path[u].push_back(vv);
            }else {
                dfs_HLD(vv);
            }
        }
    }
    head[G[u]] = init(0, Path[u].size() - 1);
}

int lca(int u, int v){
    while(G[u] != G[v]){
        if(H[G[u]] < H[G[v]]) swap(u, v);
        u = P[G[u]];
    }
    return pos[u] < pos[v] ? u : v;
}

void update(int u, int v, long long a, long long d){
    int l = lca(u, v);
    while(G[u] != G[l]){
        a = (a + (pos[u] + 1) * d) % mod;
        head[G[u]]->update(0, pos[u], (a-d+mod) % mod, mod-d);
        u = P[G[u]];
    }
    if(pos[l] + 1 <= pos[u]){
        a = (a + (pos[u] - pos[l]) * d) % mod;
        head[G[u]]->update(pos[l]+1, pos[u], (a-d+mod) % mod, mod-d);
    }
    long long nw_a = (a + (H[v] - H[l]) * d) % mod, nw_d = mod - d;
    while(G[v] != G[l]){
        nw_a = (nw_a + (pos[v] + 1) * nw_d) % mod;
        head[G[v]]->update(0, pos[v], (nw_a + d) % mod, d);
        v = P[G[v]];
    }
    head[G[v]]->update(pos[l], pos[v], a, d);
    nw_a = (nw_a + (pos[v] - pos[l]) * nw_d) % mod;
    assert(a == nw_a);
}

long long query(int u, int v){
    long long ans = 0ll;
    while(G[u] != G[v]){
        if(H[G[u]] < H[G[v]]){
            swap(u, v);
        }
        ans = (ans + head[G[u]]->query(0, pos[u])) % mod;
        u = P[G[u]];
    }
    if(pos[u] > pos[v]) swap(u, v);
    ans = (ans + head[G[u]]->query(pos[u], pos[v])) % mod;
    ans = (ans + mod) % mod;
    return ans;
}

int main(){
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ios::sync_with_stdio(false);
    cin >> n >> q;
    for(int i = 0;i < n-1;i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_init(0, 0, 0);
    dfs_HLD(0);
    for(int i = 0;i < q;i++){
        int type;
        cin >> type;
        if(type == 1){
            int u, v;
            long long x;
            cin >> u >> v >> x;
            update(u, v, x, x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << query(u, v) << "\n";
        }
    }
    return 0;
}
