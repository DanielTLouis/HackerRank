/*
You are given a tree* with N nodes and each has a value associated with it. You are given Q
queries, each of which is either an update or a retrieval operation.
* https://en.wikipedia.org/wiki/Tree_%28graph_theory%29 *
Initially all node values are zero.
The update query is of the format
    a1 d1 a2 d2 A B
This means you'd have to add (a1+z*d1)*(a1+z*d2)*R^z in all nodes in the path from A to B
where z is the distance
between the node and A.
The retrieval query is of the format
    i j
You need to return the sum of the node values lying in the path from node i to node j modulo
1000000007.
Note:
    1. First all update queries are given and then all retrieval queries.
    2. Distance between 2 nodes is the shortest path length between them taking each edge
    weight as 1.
Input Format
    The first line contains two integers (N and R respectively) separated by a space.
    In the next N-1 lines, the ith line describes the ith edge: a line with two integers x y
    separated by a single space denotes an edge between nodes x and y.
    The next line contains 2 space separated integers (U and Q respectively) representing the
    number of Update and Query operations to follow.
    U lines follow. Each of the next U lines contains 6 space separated integers
    (a1,d1,a2,d2,A and B respectively).
    Each of the next Q lines contains 2 space separated integers, i and j respectively.
Output Format
    It contains exactly Q lines and each line containing the answer of the ith query.
Constraints
    2 <= N <= 105
    2 <= R <= 109
    1 <= U <= 105
    1 <= Q <= 105
    1 <= a1,a2,d1,d2 <= 108
    1 <= x, y, i, j, A, B <= N
Note
    For the update operation, x can be equal to y and for the query operation, i can be equal
    to j.
Sample Input
    7 2
    1 2
    1 3
    2 4
    2 6
    4 5
    6 7
    1 4
    1 1 1 1 4 6
    4 5
    2 7
    4 7
    5 3
Sample Output
    1
    44
    45
    9
Explanation
    The node values after updation becomes :
        0 8 0 1 0 36 0
    Answer to Query #1: 1+0 = 1
    Answer to Query #2: 8+36+0 = 44
    Answer to Query #3: 1+8+36+0 = 45
    Answer to Query #4: 0+1+8+0+0 = 9
*/

#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for(int i = (a); i <= (b); i++)
typedef long long int ll;

const int mod = 1000000007;
vector<int> myvector[100001];
int N, parent[100001], depth[100001], Q, U;
ll R, Rinv, Rp[100001], sum[100001];
int store[100001], Root[100001][18];

struct node{
    ll S, D, B, factD, factB, addB;
    node(ll a = 0, ll b = 0, ll c = 0, ll d = 0, ll e = 0, ll f = 0){
        S = a, D = b, B = c;
        factD = d;
        factB = e;
        addB = f;
    }

    node operator + (const node &x) const{
        ll a, b, c, d, e, f;
        a = (x.S + S);
        b = (x.D + D);
        c = (x.B + B);
        d = (x.factD + factD);
        e = (x.factB + factB);
        f = (x.addB + addB);
        a = (a > mod) ? (a - mod) : a;
        b = (b > mod) ? (b - mod) : b;
        c = (c > mod) ? (c - mod) : c;
        d = (d > mod) ? (d - mod) : d;
        e = (e > mod) ? (e - mod) : e;
        f = (f > mod) ? (f - mod) : f;
        return node(a, b, c, d, e, f);
    }

} fwd[100001], bck[100001], A, B;

ll inverse(ll a, ll b){
    ll Remainder, p0 = 0, p1 = 1, pcurr = 1, q, m = b;
    while(a != 0){
        Remainder = b % a;
        q = b / a;
        if(Remainder != 0){
            pcurr = p0 - (p1 * q) % m;
            if(pcurr < 0)
                pcurr += m;
            p0 = p1;
            p1 = pcurr;
        }
        b = a;
        a = Remainder;
    }
    return pcurr;
}

void dfs_pre(int root){
    for(vector<int>::iterator it = myvector[root].begin(); it != myvector[root].end(); it++){
        if(parent[root] == *it) continue;
        parent[*it] = root;
        depth[*it] = depth[root] + 1;
        dfs_pre(*it);
    }
}

void dfs_cal(int root){
    for(vector<int>::iterator it = myvector[root].begin(); it != myvector[root].end(); it++){
        if(parent[root]==*it) continue;
        dfs_cal(*it);
        fwd[root].S = (fwd[root].S + fwd[*it].S * R) % mod;
        fwd[root].D = (fwd[root].D + (fwd[*it].D + fwd[*it].factD) * R) % mod;
        fwd[root].factD = (fwd[root].factD + fwd[*it].factD * R) % mod;
        fwd[root].B = (fwd[root].B +  (fwd[*it].B + fwd[*it].factB) * R) % mod;
        fwd[root].factB = (fwd[root].factB + (fwd[*it].factB + fwd[*it].addB) * R) % mod;
        fwd[root].addB = (fwd[root].addB + fwd[*it].addB * R) % mod;
        bck[root].S = (bck[*it].S * Rinv + bck[root].S) % mod;
        bck[root].D = (bck[root].D + (bck[*it].D - bck[*it].factD) * Rinv) % mod;
        if(bck[root].D < 0) bck[root].D += mod;
        bck[root].factD = (bck[root].factD + bck[*it].factD * Rinv) % mod;
        bck[root].B = (bck[root].B + (bck[*it].B - bck[*it].factB) * Rinv) % mod;
        if(bck[root].B<0) bck[root].B += mod;
        bck[root].factB = (bck[root].factB + (bck[*it].factB - bck[*it].addB) * Rinv) % mod;
        if(bck[root].factB<0) bck[root].factB += mod;
        bck[root].addB = (bck[root].addB + bck[*it].addB * Rinv) % mod;
    }
    sum[root] = (sum[root] + fwd[root].S + fwd[root].D + fwd[root].B + bck[root].S + bck[root].D + bck[root].B) % mod;
}

void dfs_sum(int root)      {
    for(vector<int>::iterator it = myvector[root].begin(); it != myvector[root].end(); it++){
        if(parent[root] == *it) continue;
        sum[*it] = (sum[*it] + sum[root]) % mod;
        dfs_sum(*it);
    }
}

void init(){
    store[0] = 0; store[1] = 0; store[2] = 1;
    int cmp = 4;
    FOR(i, 3, 100000){
        if(cmp > i) store[i] = store[i - 1];
        else{
            store[i] = store[i - 1] + 1;
            cmp <<= 1;
        }
    }
}

void process(int N){
    memset(Root, -1, sizeof(Root));
    for(int i = 1; i <= N; i++) Root[i][0]=parent[i];
    for(int i = 1; (1 << i) <= N; i++)
        for(int j = 1; j <= N; j++)
            if(Root[j][i - 1] != -1)
                Root[j][i] = Root[Root[j][i - 1]][i - 1];
}

int lca(int p, int q){
    int temp;
    if(depth[p] > depth[q]) swap(p, q);
    int steps = store[depth[q]];
    for(int i = steps; i >= 0; i--)
        if(depth[q] - (1 << i) >= depth[p])
            q = Root[q][i];
    if(p == q) return p;
    for(int i = steps; i >= 0; i--){
    if(Root[p][i] != Root[q][i])
        p = Root[p][i], q = Root[q][i];
    }
    return parent[p];
}

void Update_forward(ll S, ll D, ll B1, ll t, int x, int y){
    ll brt;
    A.S = S;
    B.S = mod - (S * Rp[t]) % mod;
    A.factD = D;
    A.D = 0;
    B.factD = mod - (D * Rp[t]) % mod;
    if(B.factD < 0) B.factD += mod;
    B.D = (B.factD * t) % mod;
    brt = B1;
    A.B = 0;
    A.factB = brt;
    if(A.factB < 0) A.factB += mod;
    A.addB = (brt + brt) % mod;
    brt = mod - (B1 * Rp[t]) % mod;
    if(brt < 0) brt += mod;
    B.B = ((ll)((t * t) % mod) * brt) % mod;
    B.factB = ((ll)(2 * t + 1) * brt) % mod;
    B.addB = (brt + brt) % mod;
    fwd[x] = fwd[x] + A;
    if(y != 1) fwd[parent[y]] = fwd[parent[y]] + B;
}

void Update_backward(ll S,ll D,ll B1,ll t,ll g,int y,int x){
    ll brt;
    B.S = (S * Rp[t]) % mod;
    A.S = mod - (S * Rp[g]) % mod;
    B.factD = (D * Rp[t]) % mod;
    B.D = (t * B.factD) % mod;
    A.factD = mod - (D * Rp[g]) % mod;
    A.D = (g * A.factD) % mod;
    brt = (B1 * Rp[t]) % mod;
    B.addB = brt + brt;
    if(B.addB >= mod) B.addB -= mod;
    B.factB = ((ll)(2 * t - 1) * brt) % mod;
    if(B.factB < 0) B.factB += mod;
    B.B = ((ll)((t * t) % mod) * brt) % mod;
    brt = mod - (B1 * Rp[g]) % mod;
    if(brt < 0) brt += mod;
    A.addB = brt + brt;
    if(A.addB >= mod) A.addB -= mod;
    A.factB = ((ll)(2 * g - 1) * brt) % mod;
    if(A.factB < 0) A.factB += mod;
    A.B = ((ll)((g * g) % mod) * brt) % mod;
    bck[y] = bck[y] + B;
    bck[x] = bck[x] + A;
}

void solve(){
    ll S1, D1, B1, ans;
    int Z, anc, x, y, a1, a2, d1, d2;
    scanf("%d%lld", &N, &R);
    Rinv = inverse(R, mod);
    FOR(i, 1, N - 1){
        scanf("%d%d", &x, &y);
        myvector[x].push_back(y);
        myvector[y].push_back(x);
    }
    parent[1] = 1;
    depth[1] = 0;
    dfs_pre(1);
    process(N);
    Rp[0] = 1;
    FOR(i, 1, N) Rp[i] = ((ll)Rp[i - 1] * (ll)R) % mod;
    scanf("%d%d", &U, &Q);
    while(U--){
        scanf("%d%d%d%d%d%d", &a1, &d1, &a2, &d2, &x, &y);
        S1 = ((ll)a1 * (ll)a2) % mod;
        D1 = ((ll)d1 * (ll)a2 + (ll)d2 * (ll)a1) % mod;
        B1 = ((ll)d1 * (ll)d2) % mod;
        anc = lca(x, y);
        Update_forward(S1, D1, B1, depth[x] - depth[anc] + 1, x, anc);
        Update_backward(S1, D1, B1, depth[y] + depth[x] - 2 * depth[anc], depth[x] - depth[anc], y, anc);
    }
    dfs_cal(1);
    dfs_sum(1);
    while(Q--){
        scanf("%d%d", &x, &y);
        anc = lca(x, y);
        if(anc != 1) ans = (sum[x] + sum[y] - sum[anc] - sum[parent[anc]]) % mod;
        else ans = (sum[x] + sum[y] - sum[anc]) % mod;
        if(ans < 0) printf("%lld\n", ans + mod);
        else printf("%lld\n", ans);
    }
}

int main(){
    init();
    solve();
    return 0;
}
