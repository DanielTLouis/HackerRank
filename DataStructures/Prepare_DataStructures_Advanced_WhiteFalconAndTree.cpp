/*
White Falcon has a tree with N nodes. Each node contains a linear function. Let's denote
by f_u(x) the linear function contained in the node u.
Let's denote the path from node u to node u like this: p1,p2,p3,...,pk, where p1=u and
pk=v, and pi and p(i+1) are connected.
White Falcon also has Q queries. They are in the following format:
    1.1uvab. Assign ax+b as the function of all the nodes on the path from u to v, i.e.,
    f_pi(x) is changed to ax+b where p1,p2,p3,...,pk is the path from u to v.
    2. 2uvx. Calculate f_pk(f_(pk-1)(f_(pk-2)(...f_p1(x)))) modulo (10^9 + 7)
Input Format
    The first line contains N, the number of nodes. The following N lines each contain
    two integers a and b that describe the function ax+b.
    Following N-1 lines contain edges of the tree.
    The next line contains Q, the number of queries. Each subsequent line contains one
    of the queries described above.
Output Format
    For every query of the second kind, print one line containing an integer, the answer
    for that query.
Constraints
    1<=N<=50000(Number of nodes)
    1<=Q<=50000(Number of queries)
    0<=a,b,x<10^9 + 7
Sample Input
    2
    1 1
    1 2
    1 2
    2
    1 2 2 1 1
    2 1 2 1
Sample Output
    3
Explanation
    f_1(1)=2
    f_2(2)=3
*/

#include <bits/stdc++.h>

using namespace std;

#define mod 1000000007
#define vi vector<int>
#define pb push_back
#define N 50005

int a[N], b[N], sz[N], top[N], ch[N], f[N], st[N], w[N], p[N][18], d[N], cnt, n;
vi g[N];

void dfs(int u, int fa){
    sz[u] = 1;
    for(int i = 0; i < g[u].size(); i++){
        int j = g[u][i];
        if(j == fa) continue;
        dfs(j, u);
        sz[u] += sz[j];
        if(ch[u] == 0 || sz[ch[u]] < sz[j]) ch[u]=j;
    }
}

void go(int u, int fa, int p){
    st[u] = ++cnt; w[cnt] = u; top[u] = p; f[u] = fa; d[u] = d[fa] + 1;
    if(ch[u] == 0) {return;}
    go(ch[u], u, p);
    for(int i = 0; i < g[u].size(); i++){
        int j = g[u][i];
        if(j == fa || j == ch[u]) continue;
        go(j, u, j);
    }
}

int lca(int a, int b){
    if(d[a] < d[b]) swap(a, b);
    int h = d[a] - d[b];
    for(int i = 17; i >= 0; i--)
        if(h >> i & 1) a = p[a][i];
    if(a == b) return a;
    for(int i = 17; i >= 0; i--)
        if(p[a][i] != p[b][i]) a = p[a][i], b = p[b][i];
    return p[a][0];
}

int pow(int a, int b){
    int ans = 1;
    while(b){
        if(b & 1) ans = 1LL * ans * a % mod;
        b >>= 1; a = 1LL * a * a % mod;
    }
    return ans;
}

struct node{
    int a, b1, b2, ca, cb;
} t[N << 2];

void up(int p){
    t[p].a = 1LL * t[p << 1].a * t[p << 1 | 1].a % mod;
    t[p].b1 = (1LL * t[p << 1].a * t[p << 1 | 1].b1 % mod + t[p << 1].b1) % mod;
    t[p].b2 = (1LL * t[p << 1 | 1].a * t[p << 1].b2 % mod + t[p << 1 | 1].b2) % mod;
}

void build(int p, int l, int r){
    t[p].ca = t[p].cb = -1;
    if(l == r){
        t[p].a = a[w[l]];
        t[p].b1 = t[p].b2 = b[w[l]];
        return;
    }
    int m = (l + r) >> 1;
    build(p << 1, l, m);
    build(p << 1 | 1, m + 1, r);
    up(p);
}

void cal(int p, int l, int r, int a, int b){
    t[p].a = pow(a, r - l + 1);
    if(a == 1){
        int v = 1LL * b * (r - l + 1) % mod;
        t[p].b1 = t[p].b2 = v;
    }
    else{
        int v = t[p].a - 1;
        if(v < 0) v += mod;
        int w = a - 1;
        if(w < 0) w += mod;
        w = pow(w, mod - 2);
        v = 1LL * v * w % mod * b % mod;
        t[p].b1 = t[p].b2 = v;
    }
    t[p].ca = a, t[p].cb = b;
}

void down(int p, int l, int r){
    if(t[p].ca != -1){
        int m = (l + r) >> 1;
        cal(p << 1, l, m, t[p].ca, t[p].cb);
        cal(p << 1 | 1, m + 1, r, t[p].ca, t[p].cb);
        t[p].ca = -1;
    }
}

void upd(int p, int l, int r, int x, int y, int a, int b){
    if(l >= x && r <= y){
        cal(p, l, r, a, b);
        return;
    }
    int m = (l + r) >> 1;
    down(p, l, r);
    if(x <= m) upd(p << 1, l, m, x, y, a, b);
    if(y > m) upd(p << 1 | 1, m + 1, r, x, y, a, b);
    up(p);
}

void query(int p, int l, int r, int x, int y, int &a, int &b, int k){
    if(l >= x && r <= y){
        a = t[p].a;
        if(k) b = t[p].b1;
        else b = t[p].b2;
        return;
    }
    a = 1; b = 0;
    int m = (l + r) >> 1, a1 = 1, b1 = 0, a2 = 1, b2 = 0;
    down(p, l, r);
    if(x <= m) query(p << 1, l, m, x, y, a1, b1, k);
    if(y > m) query(p << 1 | 1, m + 1, r, x, y, a2, b2, k);
    a = 1LL * a2 * a1 % mod;
    if(k) b = (1LL * a1 * b2 % mod + b1) % mod;
    else b = (1LL * a2 * b1 % mod + b2) % mod;
    up(p);
}

void change(int u, int v, int a, int b){
    while(top[u] != top[v]){
        int x = top[u];
        upd(1, 1, n, st[x], st[u], a, b);
        u = f[x];
    }
    upd(1, 1, n, st[v], st[u], a, b);
}

void query(int u, int v, int &a, int &b, int dir){
    a = 1, b = 0;
    while(top[u] != top[v]){
        int x = top[u], a1, b1;
        query(1, 1, n, st[x], st[u], a1, b1, dir);
        if(dir == 0) b = (1LL * a * b1 % mod + b) % mod;
        else b = (1LL * a1 * b % mod + b1) % mod;
        a = 1LL * a * a1 % mod;
        u = f[x];
    }
    int a1, b1;
    query(1, 1, n, st[v], st[u], a1, b1, dir);
    if(dir == 0) b = (1LL * a * b1 % mod + b) % mod;
    else b = (1LL * a1 * b % mod + b1) % mod;
    a = 1LL * a * a1 % mod;
}

int main(){
    int T, i, j, ca = 0, k, m;
    scanf("%d", &n);
    for(i = 1; i <= n; i++) scanf("%d%d", &a[i], &b[i]);
    for(i = 1; i < n; i++){
        scanf("%d%d", &j, &k);
        g[j].pb(k); g[k].pb(j);
    }
    dfs(1, 0); cnt = 0;
    go(1, 0, 1);
    p[1][0] = 1;
    for(i = 1; i <= n; i++) p[i][0] = f[i];
    for(i = 1; i < 18; i++)
        for(j = 1; j <= n; j++)
            p[j][i] = p[p[j][i - 1]][i - 1];
    build(1, 1, n);
    scanf("%d", &m);
    while(m--){
        int x, y;
        scanf("%d%d%d", &k, &x, &y);
        if(k == 1){
            int a, b; scanf("%d%d", &a, &b);
            int fa = lca(x, y);
            if(x == fa) change(y, x, a, b);
            else if(y == fa) change(x, y, a, b);
            else{
                int h = d[x] - d[fa] - 1;
                int u = x;
                for(i = 17; i >= 0; i--)
                    if(h >> i & 1) u = p[u][i];
                change(x, u, a, b); change(y, fa, a, b);
            }
        }
        else {
            int v; scanf("%d", &v);
            int fa = lca(x, y), a, b;
            if(x == fa) query(y, x, a, b, 0);
            else if(y == fa) query(x, y, a, b, 1);
            else{
                int h = d[x] - d[fa] - 1;
                int u = x, a1, b1;
                for(i = 17; i >= 0; i--)
                    if(h >> i & 1) u = p[u][i];
                query(x, u, a, b, 1); query(y, fa, a1, b1, 0);
                b = (1LL * a1 * b % mod + b1) % mod; a = 1LL * a * a1 % mod;
            }
            printf("%d\n", (1LL * a * v % mod + b) % mod);
        }
    }
    return 0;
}
