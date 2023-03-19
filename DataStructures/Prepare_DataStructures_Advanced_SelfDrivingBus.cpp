/*
reeland is a country with n cities and n-1 roads. There is exactly one path between any two
cities.
The ruler of Treeland wants to implement a self-driving bus system and asks tree-loving Alex
to plan the bus routes. Alex decides that each route must contain a subset of connected cities;
a subset of cities is connected if the following two conditions are true:
    1. There is a path between every pair of cities which belongs to the subset.
    2. Every city in the path must belong to the subset.
        tree.png
In the figure above, {2,3,4,5} is a connected subset, but {6,7,9} is not (for the second
condition to be true, 8 would need to be part of the subset).
Each self-driving bus will operate within a connected segment of Treeland. A connected segment
[L,R] where 1<=L<=R<=n is defined by the connected subset of cities S={x|x isAnElementOf(Z and
L <= x <=R)}.
In the figure above, [2,5] is a connected segment that represents the subset {2,3,4,5}. Note
that a single city can be a segment too.
Help Alex to find number of connected segments in Treeland.
Input Format
    The first line contains a single positive integer, n. The n-1 subsequent lines each
    contain two positive space-separated integers, ai and bi, describe an edge connecting two
    nodes in tree T.
Constraints
    1<=n<=2X10^5
    1<=ai,bi<=n
Subtasks
    For 25% score: 1<=n<=2X10^3
    For 50% score: 1<=n<=10^4
Output Format
    Print a single integer: the number of segments [L,R], which are connected in tree T.
Sample Input
    3
    1 3
    3 2
Sample Output
    5
Explanation
    The connected segments for our test case are: [1,1], [2,2], [3,3], [2,3], and [1,3]. These
    segments can be represented by the respective subsets: {1}, {2}, {3}, {2,3}, and {1,2,3}.
        tree4.png
    Note: [1,2] is not a connected segment. It represents the subset {1,2} and the path
    between 1 and 2 goes through 3 which is not a member of the subset.
*/
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<vector>
#include<string>
#include<cstring>
#include<unordered_map>
#include<cassert>
#include<cmath>

#define dri(X) int (X); scanf("%d", &X)
#define drii(X, Y) int X, Y; scanf("%d%d", &X, &Y)
#define driii(X, Y, Z) int X, Y, Z; scanf("%d%d%d", &X, &Y, &Z)
#define pb push_back
#define mp make_pair
#define rep(i, s, t) for ( int i=(s) ; i <(t) ; i++)
#define fill(x, v) memset (x, v, sizeof(x))
#define all(x) (x).begin(), (x).end()
#define why(d) cerr << (d) << "!\n"
#define whisp(X, Y) cerr << (X) << " " << (Y) << "#\n"
#define exclam cerr << "!!\n"
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
#define mid ((l + r) >> 1)
typedef long long ll;
using namespace std;
typedef pair<int, int> pii;
const ll inf = (ll)1e9 + 70;
const ll mod = 1e9 + 7;
const int maxn = 2e5 + 1000;
vector<int> adj [maxn];

bool used[maxn];
int sz[maxn];//subtree sizes

int mark[maxn];
int tt = 0;

int maax[maxn];
int miin[maxn];
int goright[maxn];
int goleft[maxn];

int val[maxn];
int ST[4 * maxn];// an all-purpose ST: min, max, and sum!!
int query(int p, int l, int r, int i, int j){//sum query
    if (l > j || r < i) return 0;
    if (i <= l && r <= j){
        return ST[p];
    }
    return query(left(p), l, mid, i, j) + query(right(p), mid + 1, r, i, j);
}
void update(int p, int l, int r, int i, int delta){
    if (l > i || r < i) return;
    if (l == r){
        ST[p] += delta;
        return;
    }
    update(left(p), l, mid, i, delta);
    update(right(p), mid + 1, r, i, delta);
    ST[p] = ST[left(p)] + ST[right(p)];
}
void buildtree(int p, int l, int r, bool m){
    if (l == r){
        ST[p] = val[l];
        return;
    }
    buildtree(left(p), l, mid, m);
    buildtree(right(p), mid + 1, r, m);
    if (m) ST[p] = min(ST[left(p)], ST[right(p)]);
    else ST[p] = max(ST[left(p)], ST[right(p)]);
}
vector<pair<int, pii>> blocks;
void decompose(int p, int l, int r, int i){
    if (r < i) return;
    if (l >= i){
        blocks.push_back(mp(p, pii(l, r)));
        return;
    }
    decompose(left(p), l, mid, i);
    decompose(right(p), mid + 1, r, i);
}
void decompose2(int p, int l, int r, int i){
    if (l > i) return;
    if (r <= i){
        blocks.push_back(mp(p, pii(l, r)));
        return;
    }
    decompose2(left(p), l, mid, i);
    decompose2(right(p), mid + 1, r, i);
}

int find(int p, int l, int r, int x){
    assert(ST[p] < x);
    if (l == r) return l;
    if (ST[left(p)] >= x){
        return find(right(p), mid + 1, r, x);
    }
    return find(left(p), l, mid, x);
}

int find2(int p, int l, int r, int x){
    assert(ST[p] > x);
    if (l == r) return l;
    if (ST[right(p)] <= x){
        return find2(left(p), l, mid, x);
    }
    return find2(right(p), mid + 1, r, x);
}

void dfs(int v, int p){
    mark[v] = tt;
    sz[v] = 1;
    if (p == -1){
        maax[v] = v; miin[v] = v;
    }
    else{
        maax[v] = max(maax[p], v);
        miin[v] = min(miin[p], v);
    }

    for (int u : adj[v]){
        if (u == p || used[u]) continue;
        dfs(u, v);
        sz[v] += sz[u];
    }
}

ll perform(int v, int n){
    if (n == 1){
        return 1;
    }
    //first, FIND the centroid.
    dfs(v, -1);
    int g = v; int p = -1;
    while (true){
        int w = -1;
        for (int h : adj[g]){
            if (h == p || used[h]) continue;
            if (w == -1 || sz[h] > sz[w]) w = h;
        }
        assert(w != -1);//g should NOT be a leaf.
        if (2 * sz[w] <= n){
            break;
        }
        p = g; g = w;
    }
    //g is the centroid.
    tt++;
    dfs(g, -1);
    //here comes the HEART OF THE ALGORITHM.
    int m = -800;
    for (int l = g; l > 0; l--){
        if (mark[l] != tt) break;
        m = l;
    }
    int M = -800;
    for (int r = g; r < maxn; r++){
        if (mark[r] != tt) break;
        M = r;
    }
    //Our working interval is m <= i <= M.
    rep(i, m, M + 1){
        val[i] = miin[i];
        //cout << miin[i] << " ";
    }//cout << endl;
    buildtree(1, m, M, true);
    rep(i, m, M + 1){
        if (miin[i] < i){
            goright[i] = -inf;
            continue;
        }
        blocks.clear();
        decompose(1, m, M, i);
        reverse(blocks.begin(), blocks.end());
        while (!blocks.empty() && ST[blocks.back().first] >= i) blocks.pop_back();
        if (blocks.empty()){
            goright[i] = M;
        }
        else{
            auto ee = blocks.back();
            goright[i] = find(ee.first, ee.second.first, ee.second.second, i) - 1;
        }
    }
    //rep(i, m, M + 1)cout << goright[i] << " "; cout << endl;
    //now, goleft!
    rep(i, m, M + 1) val[i] = maax[i];
    //rep(i, m, M + 1) cout << maax[i] << " "; cout << endl;
    buildtree(1, m, M, false);
    rep(i, m, M + 1){
        if (maax[i] > i){
            goleft[i] = inf;
            continue;
        }
        blocks.clear();
        decompose2(1, m, M, i);
        while (!blocks.empty() && ST[blocks.back().first] <= i) blocks.pop_back();
        if (blocks.empty()){
            goleft[i] = m;
        }
        else{
            auto ee = blocks.back();
            goleft[i] = find2(ee.first, ee.second.first, ee.second.second, i) + 1;
        }
    }
    //rep(i, m, M + 1) cout << goleft[i] << " "; cout << endl;
    vector<pii> rs;
    rep(r, m, M + 1){
        if (goleft[r] != inf) rs.push_back(pii(goleft[r], r));
    }
    sort(all(rs)); reverse(all(rs));
    rep(i, m, M + 1) val[i] = 0;
    buildtree(1, m, M, true);//basically: just clear it.
    ll ans = 0;
    for (int l = m; l <= M; l++){
        //whisp(l, goright[l]);
        while (!rs.empty() && rs.back().first == l){
            update(1, m, M, rs.back().second, 1);
            //cout << "update " << rs.back().second << "\n";
            rs.pop_back();
        }
        //cout << query(1, m, M, l, goright[l]) << "\n";
        ans += query(1, m, M, l, goright[l]);
    }
    used[g] = true;
    vector<pii> ls;
    for (int u : adj[g]){
        if (used[u]) continue;
        ls.push_back(pii(u, sz[u]));
    }
    for (pii x : ls){
        ans += perform(x.first, x.second);
    }
    return ans;
}


int main(){
    if (fopen("input.txt", "r")) freopen("input.txt", "r", stdin);
    dri(n);
    rep(i, 1, n){
        drii(a, b);
        adj[a].push_back(b); adj[b].push_back(a);
    }
    cout << perform(1, n) << "\n";
    return 0;
}
