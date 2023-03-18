/*
Shashank loves trees and math. He has a rooted tree, T, consisting of N nodes uniquely labeled
with integers in the inclusive range [1,N]. The node labeled as 1 is the root node of tree T,
and each node in T is associated with some positive integer value (all values are initially 0).
Let's define Fk as the kth Fibonacci number*. Shashank wants to perform 2 types of operations
over his tree, T:
* https://en.wikipedia.org/wiki/Fibonacci_number *
    1. UXk
        Update the subtree rooted at node X such that the node at level 0 in subtree X (i.e.,
        node X) will have Fk added to it, all the nodes at level 1 will have F(k+1) added to
        them, and so on. More formally, all the nodes at a distance D from node X in the
        subtree of node X will have the (k+D)th Fibonacci number added to them.
    2. QXY
    Find the sum of all values associated with the nodes on the unique path from X to Y. Print
    your sum modulo 10^9 +7 on a new line.
Given the configuration for tree T and a list of M operations, perform all the operations
efficiently.
Note: F1=F2=1.
Input Format
    The first line contains 2 space-separated integers, N (the number of nodes in tree T) and
    M (the number of operations to be processed), respectively.
    Each line i of the N-1 subsequent lines contains an integer, P, denoting the parent of the
    (i+1)th node.
    Each of the M subsequent lines contains one of the two types of operations mentioned in
    the Problem Statement above.
Constraints
    1<=N,M<=10^5
    1<=X,Y<=N
    1<=k<=10^15
Output Format
    For each operation of type 2 (i.e., Q), print the required answer modulo 10^9 +7 on a new
    line.
Sample Input
    5 10
    1
    1
    2
    2
    Q 1 5
    U 1 1
    Q 1 1
    Q 1 2
    Q 1 3
    Q 1 4
    Q 1 5
    U 2 2
    Q 2 3
    Q 4 5
Sample Output
    0
    1
    2
    2
    4
    4
    4
    10
Explanation
    Intially, the tree looks like this:
        fib.png
    After update operation 1 1, it looks like this:
        fib(1).png
    After update operation 2 2, it looks like this:
        fib(2).png
*/

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <cctype>
#include <utility>
#include <queue>
#include <cmath>
#include <complex>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<PII> VPII;
typedef pair<LL, LL> PLL;
typedef pair<int, LL> PIL;
typedef pair<LL, int> PLI;
typedef double DB;

#define pb push_back
#define mset(a, b) memset(a, b, sizeof a)
#define all(x) (x).begin(), (x).end()
#define bit(x) (1 << (x))
#define bitl(x) (1LL << (x))
#define sqr(x) ((x) * (x))
#define sz(x) ((int)(x.size()))
#define cnti(x) (__builtin_popcount(x))
#define cntl(x) (__builtin_popcountll(x))
#define clzi(x) (__builtin_clz(x))
#define clzl(x) (__builtin_clzll(x))
#define ctzi(x) (__builtin_ctz(x))
#define ctzl(x) (__builtin_ctzll(x))

#define X first
#define Y second

#define Error(x) cout << #x << " = " << x << endl

template <typename T, typename U>
inline void chkmax(T& x, U y) {
    if (x < y) x = y;
}

template <typename T, typename U>
inline void chkmin(T& x, U y) {
    if (y < x) x = y;
}

const int MOD = 1e9 + 7;
const int MAXN = 111111;

int n, m;

VI adj[MAXN];
int f[17][MAXN];
int d[MAXN], st[MAXN], en[MAXN];
int b[3][MAXN];
int c[55][2][2];

int T;

void dfs(int u) {
    st[u] = ++T;
    for (int i = 0; i < sz(adj[u]); i++) {
        d[adj[u][i]] = d[u] + 1;
        dfs(adj[u][i]);
    }
    en[u] = T;
}

void add(int p, int id, int x) {
    for (; p <= n; p += p & -p) {
        b[id][p] = (b[id][p] + x) % MOD;
    }
}

int get_sum(int p, int id) {
    int ret = 0;
    for (; p; p -= p & -p) {
        ret = (ret + b[id][p]) % MOD;
    }
    return ret;
}

PII get(LL e) {
    int a[2], _a[2]; a[0] = 1, a[1] = 0;
    for (int i = 50; i >= 0; i--) {
        if (e >> i & 1) {
            for (int j = 0; j < 2; j++) {
                LL s = 0;
                for (int k = 0; k < 2; k++) {
                    s += (LL)a[k] * c[i][j][k];
                }
                _a[j] = s % MOD;
            }
            memcpy(a, _a, sizeof a);
        }
    }
    return make_pair(a[0], a[1]);
}

inline int lca(int u, int v) {
  if (d[u] < d[v]) swap(u, v);
  for (int i = 16; i >= 0; i--) {
    if (d[f[i][u]] < d[v]) continue;
    u = f[i][u];
    if (d[u] == d[v]) break;
  }
  if (u == v) return u;
  for (int i = 16; i >= 0; i--) {
    if (f[i][u] == f[i][v]) continue;
    u = f[i][u], v = f[i][v];
  }
  return f[0][u];
}

void change(int u, LL k) {
    k += 2*(MOD+1);
    PII x = get(k), y = get(k - d[u] + 1);
    add(st[u], 0, MOD-x.first);
    add(st[u], 1, y.first);
    add(st[u], 2, y.second);
    add(en[u]+1, 0, x.first);
    add(en[u]+1, 1, MOD-y.first);
    add(en[u]+1, 2, MOD-y.second);
}

int query(int u) {
    if (!u) {
        return 0;
    }
    PII x = get(d[u]);
    LL s0 = get_sum(st[u], 0), s1 = get_sum(st[u], 1), s2 = get_sum(st[u], 2);
    return (s0 + s1 * x.first + s2 * x.second) % MOD;
}

int main() {

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c[0][i][j] = !(i & j);
        }
    }
    for (int e = 1; e <= 50; e++) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                LL s = 0;
                for (int k = 0; k < 2; k++) {
                    s += (LL)c[e-1][i][k] * c[e-1][k][j];
                }
                c[e][i][j] = s % MOD;
            }
        }
    }
    scanf("%d%d", &n, &m);
    for (int i = 2; i <= n; i++) {
        int x; scanf("%d", &x);
        adj[x].push_back(i), f[0][i] = x;
    }
    d[1] = 1;
    dfs(1);
    for (int i = 1; i <= 16; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i-1][f[i-1][j]];
        }
    }
    memset(b, 0, sizeof b);
    for (int i = 0; i < m; i++) {
        char t[5]; int u;
        scanf("%s%d", t, &u);
        if (t[0] == 'U') {
            LL k; scanf("%lld", &k);
            change(u, k);
        } else {
            int v; scanf("%d", &v);
            int w = lca(u, v), p = f[0][w], ans = 0;
            ans = (query(u)+query(v)) % MOD;
            ans = (ans+MOD-query(w)) % MOD;
            ans = (ans+MOD-query(p)) % MOD;
            printf("%d\n", ans);
        }
    }
    return 0;
}
