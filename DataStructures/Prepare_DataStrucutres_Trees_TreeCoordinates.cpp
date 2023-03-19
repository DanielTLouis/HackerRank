/*
We consider metric space* to be a pair, (M,p), where M is a set and p : M X M -> R such that
the following conditions hold:
* https://en.wikipedia.org/wiki/Metric_space *
    * p(x,y)>=0
    * p(x,y) = 0 <-> x = y
    * p(x,y)=p(y,x)
    * p(x,y)<=p(x,z)+p(z,y)
where p(x,y) is the distance between points x and y.
Let's define the product of two metric spaces, (M_1,p_1) X (M_2,p_2), to be (M,p) such that:
    * M = M_1 X M_2
    * p(z_1,z_2)=p_1(x_1,x_2) + p(y_1,y_2), where z_1=(x_1,y_1), z_2=(x_2,y_2).
So, it follows logically that (M,p) is also a metric space. We then define squared metric
space, (M,p)^2, to be the product of a metric space multiplied with itself: (M,p) X (M,p).
For example, (R, abs), where abs(x,y)=|x-y| is a metric space. (R,abs)^2 = (R^2, abs_2),
where abs_2((x_1,y_2),(x_2,Y_2))=|x_1-x_2|+|y_1-y_2|
In this challenge, we need a tree-space. You're given a tree, T=(V,E), where V is the set of
vertices and E is the set of edges. Let the function p: V X V -> Z be the distance between two
vertices in tree T (i.e., p(x,y) is the number of edges on the path between vertices x and y).
Note that (V,p) is a metric space.
You are given a tree, T, with n vertices, as well as m pointfs in (V,)^2. Find and print the
 distance between the two furthest points in this metric space!
Input Format
    The first line contains two space-separated positive integers describing the respective
    values of n (the number of vertices in T) and m (the number of given points).
    Each line i of the n-1 subsequent lines contains two space-separated integers, u_i and v_i,
     describing edge i in T.
    Each line j of the m subsequent lines contains two space-separated integers describing the
    respective values of x_j and y_j for point j.
Constraints
    1<=n<=7.5 * 10^4
    2<=m<=7.5 * 10^4
    1<=u_i,v_i<=n
    1<=x_j,y_j<=n
Scoring
    This challenge uses binary scoring, so you must pass all test cases to earn a positive
    score.
Output Format
    Print a single non-negative integer denoting the maximum distance between two of the given
    points in metric space (T,p)^2.
Sample Input 0
    2 2
    1 2
    1 2
    2 1
Sample Output 0
    2
Explanation 0
    The distance between points (1,2) and (2,1) is p(1,2)+p(2,1)=2.
Sample Input 1
    7 3
    1 2
    2 3
    3 4
    4 5
    5 6
    6 7
    3 6
    4 5
    5 5
Sample Output 1
    3
Explanation 1
    The best points are (3,6) and (5,5), which gives us a distance of p(3,5)+p(6,5)=2+1=3.
*/
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <deque>
#include <string>

#include <algorithm>
#include <numeric>

#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>

#define pb push_back
#define pbk pop_back
#define mp make_pair
#define fs first
#define sc second
#define all(x) (x).begin(), (x).end()
#define foreach(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); ++i)
#define len(a) ((int) (a).size())

#ifdef CUTEBMAING
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long int64;
typedef long double ld;
typedef unsigned long long lint;

const int inf = (1 << 30) - 1;
const int64 linf = (1ll << 62) - 1;
const int N = 1e5 + 100;
const int K = 17;

struct layer {
    int color[N], root[N];
    int dist[N];
    pair<int, int> max1[N], max2[N];

    layer() {
        fill_n(color, N, -1);
        fill_n(root, N, -1);
        fill_n(dist, N, -1);
        fill_n(max1, N, mp(-inf, -inf));
        fill_n(max2, N, mp(-inf, -inf));
    }
};

int n, m;
vector<vector<int>> g, backup;
int reqA[N], reqB[N];

layer st[K];

int comp[N], compLen = 0;
int parent[N], size[N];

inline void update(pair<int, int> &a, pair<int, int> &b, const pair<int, int> &c) {
    if (a.fs < c.fs) {
        if (a.sc != c.sc) {
            b = a;
        }
        a = c;
    } else if (b.fs < c.fs && c.sc != a.sc) {
        b = c;
    }
}

inline void update(int v, int value) {
    for (int i = 0; i < K; i++) {
        layer &layer = st[i];
        int root = layer.root[v];
        if (root == -1) {
            break;
        }
        update(layer.max1[root], layer.max2[root], mp(value + layer.dist[v], layer.color[v]));
    }
}

inline int getValue(int v) {
    int ans = -inf;
    for (int i = 0; i < K; i++) {
        layer &layer = st[i];
        int root = layer.root[v];
        if (root == -1) {
            break;
        }
        if (layer.max1[root].sc != layer.color[v] || layer.max1[root].sc == -1) {
            ans = max(ans, layer.max1[root].fs + layer.dist[v]);
        } else if (layer.max2[root].sc != layer.color[v] || layer.max2[root].sc == -1) {
            ans = max(ans, layer.max2[root].fs + layer.dist[v]);
        }
    }
    return ans;
}

inline int dfsSize(int v, int p = -1) {
    size[v] = 1;
    comp[compLen++] = v;
    parent[v] = p;
    for (int to : g[v]) {
        if (to != p) {
            size[v] += dfsSize(to, v);
        }
    }
    return size[v];
}

inline int findRoot(int v) {
    compLen = 0;
    int total = dfsSize(v);
    for (int i = 0; i < compLen; i++) {
        v = comp[i];
        bool flag = true;
        if ((total - size[v]) * 2 > total) {
            continue;
        }
        for (int j : g[v]) {
            if (j != parent[v] && size[j] * 2 > total) {
                flag = false;
                break;
            }
        }
        if (flag) {
            return v;
        }
    }
    assert(false);
}

inline void dfsColor(layer &layer, int v, int root, int color, int d = 1, int p = -1) {
    layer.color[v] = color;
    layer.root[v] = root;
    layer.dist[v] = d;
    for (int to : g[v]) {
        if (to != p) {
            dfsColor(layer, to, root, color, d + 1, v);
        }
    }
}

inline void buildDivideAndConquer(int x, int v) {
    layer &layer = st[x];
    v = findRoot(v);
    for (int to : g[v]) {
        g[to].erase(find(all(g[to]), v));
    }
    layer.color[v] = -1;
    layer.root[v] = v;
    layer.dist[v] = 0;
    for (int to : g[v]) {
        dfsColor(layer, to, v, to);
    }
    for (int to : g[v]) {
        buildDivideAndConquer(x + 1, to);
    }
}

int ans = -inf;

int color[N], dist[N];

inline void dfsColor2(int v, int c, int d = 1, int p = -1) {
    color[v] = c;
    dist[v] = d;
    for (int to : g[v]) {
        if (to != p) {
            dfsColor2(to, c, d + 1, v);
        }
    }
}

inline void clearUpdate(int v) {
    for (int i = 0; i < K; i++) {
        if (st[i].root[v] == -1) {
            break;
        }
        st[i].max1[st[i].root[v]].fs = -inf;
        st[i].max2[st[i].root[v]].fs = -inf;
    }
}

inline void divideAndConquer(int v, vector<int> requests) {
    v = findRoot(v);
    for (int to : g[v]) {
        g[to].erase(find(all(g[to]), v));
    }
    color[v] = -1, dist[v] = 0;
    for (int i = 0; i < len(g[v]); i++) {
        int to = g[v][i];
        dfsColor2(to, i);
    }
    vector<vector<int>> req(len(g[v]));
    for (int i : requests) {
        if (reqA[i] == v) {
            ans = max(ans, getValue(reqB[i]));
            update(reqB[i], 0);
        } else {
            req[color[reqA[i]]].pb(i);
        }
    }
    for (const auto &subtree : req) {
        for (int j : subtree) {
            ans = max(ans, getValue(reqB[j]) + dist[reqA[j]]);
        }
        for (int j : subtree) {
            update(reqB[j], dist[reqA[j]]);
        }
    }
    for (int i : requests) {
        clearUpdate(reqB[i]);
    }
    for (int i = 0; i < len(g[v]); i++) {
        int to = g[v][i];
        divideAndConquer(to, req[i]);
    }
}

int main() {
    cerr << sizeof(st) / 1024 / 1024 << endl;
    cin >> n >> m;
    g.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; scanf("%d%d", &u, &v), u--, v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    backup = g;
    for (int i = 0; i < m; i++) {
        scanf("%d%d", &reqA[i], &reqB[i]), reqA[i]--, reqB[i]--;
    }
    buildDivideAndConquer(0, 0);
    g = backup;
    vector<int> req(m);
    for (int i = 0; i < m; i++) {
        req[i] = i;
    }
    divideAndConquer(0, req);
    eprintf("ans = %d\n", ans);
    printf("%d\n", ans);
    return 0;
}
