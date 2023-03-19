/*
Given a rooted tree of N nodes, where each node is uniquely numbered in between [1..N]. The
node 1 is the root of the tree. Each node has an integer value which is initially 0.
You need to perform the following two kinds of queries on the tree:
    * add t value: Add value to all nodes in subtree rooted at t
    * max a b: Report maximum value on the path from a to b
Input Format
    First line contains N, number of nodes in the tree. Next N-1 lines contain two space
    separated integers x and y which denote that there is an edge between node x and node y.
    Next line contains Q, the number of queries to process.
    Next Q lines follow with either add or max query per line.
Constraints
    1<=N<=10^5
    1<=Q<=10^5
    1<=t,a,b,x,y<=N
    x != y
    -10^4 <= value <= 10^4
Output Format
    For each max query output the answer in a separate line.
Sample Input
    5
    1 2
    2 3
    2 4
    5 1
    6
    add 4 30
    add 5 20
    max 4 5
    add 2 -20
    max 4 5
    max 3 4
Sample Output
    30
    20
    10
Explanation
    In the test case we have the following tree:
        tree.png
    Initially all node values are zero.
    Queries are performed in the following way:
    add 4 30 // add 30 to node 4
    add 5 20 // add 20 to node 5
    max 4 5 // maximum of nodes 4,2,1,5 is 30
    add 2 -20 // subtract 20 from nodes 2,3,4
    max 4 5 // maximum of nodes 4,2,1,5 is 20
    max 3 4 // maximum of nodes 3,2,4 is 10
*/
#include <bits/stdc++.h>
using namespace std;

#define repu(i, a, b) for (int i = (a); i < (b); ++i)
#define repd(i, a, b) for (int i = (a); i > (b); --i)
#define mem(a, x) memset(a, x, sizeof(a))
#define all(a) a.begin(), a.end()
#define uni(a) a.erase(unique(all(a)), a.end())
#define count_bits(x) __builtin_popcount(x)
#define count_bitsll(x) __builtin_popcountll(x)
#define least_bits(x) __builtin_ffs(x)
#define least_bitsll(x) __builtin_ffsll(x)
#define most_bits(x) 32 - __builtin_clz(x)
#define most_bitsll(x) 64 - __builtin_clz(x)

vector<string> split(const string &s, char c) {
    vector<string> v;
    stringstream ss(s);
    string x;
    while (getline(ss, x, c)) v.push_back(x);
    return v;
}

#define error(args...) { vector<string> _v = split(#args, ','); err(_v.begin(), args); }

void err(vector<string>::iterator it) {}

template<typename T, typename... Args>
void err(vector<string>::iterator it, T a, Args... args) {
    cerr << it -> substr((*it)[0] == ' ', it -> length()) << " = " << a << '\n';
    err(++it, args...);
}

typedef long long ll;
const int MOD = 1000000007;

template<class T> inline T tmin(T a, T b) {return (a < b) ? a : b;}
template<class T> inline T tmax(T a, T b) {return (a > b) ? a : b;}
template<class T> inline void amax(T &a, T b) {if (b > a) a = b;}
template<class T> inline void amin(T &a, T b) {if (b < a) a = b;}
template<class T> inline T tabs(T a) {return (a > 0) ? a : -a;}
template<class T> T gcd(T a, T b) {while (b != 0) {T c = a; a = b; b = c % b;} return a;}

#define MAX_LOG 19
#define MAXN 100005

int n;
vector<int> G[MAXN];

/* HLD */
int chain_head[MAXN], pos_base[MAXN], chain_index[MAXN], end_sub[MAXN];
int ptr, num_chain;
/* LCA */
int par[MAX_LOG][MAXN], depth[MAXN], subtree[MAXN];
/* ST */
struct node {
    int maxi, lazy;
} st[MAXN * 4];



/* LCA */
void dfs(int v, int p, int d) {
    par[0][v] = p;
    depth[v] = d;
    subtree[v] = 1;
    repu(i, 0, G[v].size()) {
        if (G[v][i] != p) {
            dfs(G[v][i], v, d + 1);
            subtree[v] += subtree[G[v][i]];
        }
    }
}

void init() {
    dfs(1, -1, 0);
    for (int k = 0; k + 1 < MAX_LOG; ++k) {
        for (int v = 1; v <= n; ++v) {
            if (par[k][v] < 0) par[k + 1][v] = -1;
            else par[k + 1][v] = par[k][par[k][v]];
        }
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int k = 0; k < MAX_LOG; ++k) {
        if ((depth[u] - depth[v]) >> k & 1) {
            v = par[k][v];
        }
    }
    if (u == v) return u;
    for (int k = MAX_LOG - 1; k >= 0; --k) {
        if (par[k][u] != par[k][v]) {
            u = par[k][u];
            v = par[k][v];
        }
    }
    return par[0][u];
}

/* Segment tree */
inline void lazy_eval(int ind, int len) {
    if (st[ind].lazy != 0) {
        st[ind].maxi += st[ind].lazy;
        if (len > 1) {
            int c1 = ind << 1, c2 = c1 | 1;
            st[c1].lazy += st[ind].lazy;
            st[c2].lazy += st[ind].lazy;
        }
        st[ind].lazy = 0;
    }
}

void build_tree(int ind, int s, int e) {
    if(s == e - 1) {
        st[ind].maxi = st[ind].lazy = 0;
        return;
    }
    int c1 = ind << 1, c2 = c1 | 1, m = (s + e) >> 1;
    build_tree(c1, s, m);
    build_tree(c2, m, e);
    st[ind].maxi = tmax(st[c1].maxi, st[c2].maxi);
    st[ind].lazy = 0;
}

void update_tree(int ind, int s, int e, int ss, int ee, int val) {
    lazy_eval(ind, e - s);
    if (s >= ee || e <= ss) return;
    if (s >= ss && e <= ee) {
        st[ind].lazy += val;
        lazy_eval(ind, e - s);
        return;
    }
    int c1 = ind << 1, c2 = c1 | 1, m = (s + e) >> 1;
    update_tree(c1, s, m, ss, ee, val);
    update_tree(c2, m, e, ss, ee, val);
    st[ind].maxi = tmax(st[c1].maxi, st[c2].maxi);
}

int query_tree(int ind, int s, int e, int ss, int ee) {
    lazy_eval(ind, e - s);
    if (s >= ee || e <= ss) return INT_MIN;
    if (s >= ss && e <= ee) return st[ind].maxi;
    int c1 = ind << 1, c2 = c1 | 1, m = (s + e) >> 1;
    int vl = query_tree(c1, s, m, ss, ee);
    int vr = query_tree(c2, m, e, ss, ee);
    st[ind].maxi = tmax(st[c1].maxi, st[c2].maxi);
    return tmax(vl, vr);
}

/* Heavy light decomposition */
void build_hld(int u) {
    if(chain_head[num_chain] == -1) chain_head[num_chain] = u;
    chain_index[u] = num_chain;
    pos_base[u] = ptr++;

    int most = 0, dem = -1;
    repu(i, 0, G[u].size()) {
        int v = G[u][i];
        if (v != par[0][u]) {
            if (subtree[v] > most) {
                most = subtree[v];
                dem = v;
            }
        }
    }
    if (dem != -1) build_hld(dem);
    repu(i, 0, G[u].size()) {
        int v = G[u][i];
        if (v != par[0][u] && v != dem) {
            ++num_chain;
            build_hld(v);
        }
    }
    end_sub[u] = ptr;
}

/* query on path u -> v */
int query_hld(int u, int v) {
    int ans = INT_MIN;
    int uchain, vchain = chain_index[v];
    /* interval [x, y) */
    while (1) {
        uchain = chain_index[u];
        if (uchain != vchain) {
            int tmp = query_tree(1, 0, ptr, pos_base[chain_head[uchain]], pos_base[u] + 1);
            /* process something here */
            amax(ans, tmp);
            u = chain_head[uchain];
            u = par[0][u];
        }
        else {
            int tmp = query_tree(1, 0, ptr, pos_base[v], pos_base[u] + 1);
            /* process something here */
            amax(ans, tmp);
            break;
        }
    }
    return ans;
}

/* update value on path u -> v */
void update_hld(int v, int val) {
    int s = pos_base[v], e = end_sub[v];
    update_tree(1, 0, ptr, s, e, val);
}


int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    int q, a, b;
    string op;

    mem(chain_head, -1);
    ptr = num_chain = 0;

    cin >> n;
    repu(i, 1, n) {
        cin >> a >> b;
        G[a].push_back(b); G[b].push_back(a);
    }

    init();
    build_hld(1);
    build_tree(1, 0, n);

    cin >> q;
    repu(i, 0, q) {
        cin >> op >> a >> b;
        if (op[0] == 'a') update_hld(a, b);
        else {
            int p = lca(a, b);
            int res = query_hld(a, p);
            amax(res, query_hld(b, p));
            printf("%d\n", res);
        }
    }

    return 0;
}
