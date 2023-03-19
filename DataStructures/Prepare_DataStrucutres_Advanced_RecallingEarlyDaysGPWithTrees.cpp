/*
Chinese Version*
* https://hr-testcases.s3.amazonaws.com/959/959-chinese.md *
Russian Version **
** https://hr-testcases.s3.amazonaws.com/959/959_rus.md **
You are given a tree with N nodes and each has a value associated with it. You are given
Q queries, each of which is either an update or a retrieval operation.
The update query is of the format
    i j X
This means you'd have to add a GP series to the nodes which lie in the path from node i
to node j (both inclusive) with first term of the GP as X on node i and the common ratio
as R (given in the input)
The retrieval query is of the format
    i j
You need to return the sum of the node values (S) lying in the path from node i to
node j modulo 100711433.
Input Format
    The first line contains two integers (N and R respectively) separated by a space.
    In the next N-1 lines, the ith line describes the ith edge: a line with two integers
    a b separated by a single space denotes an edge between a, b.
    The next line contains 2 space separated integers (U and Q respectively)
    representing the number of Update and Query operations to follow.
    U lines follow. Each of the next U lines contains 3 space separated integers
    (i,j, and X respectively).
    Each of the next Q lines contains 2 space separated integers, i and j respectively.
Output Format
    It contains exactly Q lines and each line containing the answer of the ith query.
Constraints
    2 <= N <= 100000
    2 <= R <= 109
    1 <= U <= 100000
    1 <= Q <= 100000
    1 <= X <= 10
    1 <= a, b, i, j <= N
Sample Input
    6 2
    1 2
    1 4
    2 6
    4 5
    4 3
    2 2
    1 6 3
    5 3 5
    6 4
    5 1
Sample Output
    31
    18
Explanation
    The node values after the first updation becomes :
        3 6 0 0 0 12
    The node values after second updation becomes :
        3 6 20 10 5 12
    Answer to Query #1: 12 + 6 + 3 + 10 = 31
    Answer to Query #2: 5 + 10 +3 = 18
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long

const int MAXN = 111111;
const int MOD = 100711433;
int n;
int tree[MAXN], len[MAXN];//i
int belong[MAXN], idx[MAXN], all;//i
int top[MAXN], son[MAXN];//i i
int parent[MAXN], size[MAXN], dep[MAXN];//i, ,
int tour[MAXN], pos[MAXN], tour_len;//dfs
int R;
int coef[MAXN << 1], rev_coef[MAXN << 1];//coef*[1, r, r^2...], rev_coef*[r^n,r^(n-1)..1]
int sum[MAXN << 1];//value[i]
int pw[MAXN], mod_inv;
vector<int> children[MAXN];
int q[MAXN], vis[MAXN];

int power(int a, int b){
    int ret = 1;
    for(; b; b >>= 1){
        if(b & 1) ret = (ll)ret * a % MOD;
        a = (ll)a * a % MOD;
    }
    return ret;
}

int inv(int x){
    return power(x, MOD - 2);
}

int gp_sum(int n, int a1){
    return (ll)a1 * (pw[n] - 1 + MOD) % MOD * mod_inv % MOD;
}

inline int get_id(int t, int l, int r){
    return tree[t] + ((l + r) | (l != r));
}

void up(int t, int l, int r){
    int id = get_id(t, l, r);
    if(l == r) return;
    int m = (l + r) >> 1;
    int lid = get_id(t, l, m), rid = get_id(t, m + 1, r);
    sum[id] = (sum[lid] + sum[rid]) % MOD;
}

void build(int t, int l, int r){
    int id = get_id(t, l, r);
    coef[id] = rev_coef[id] = sum[id] = 0;
    if(l == r){
        return;
    }
    int m = (l + r) >> 1;
    build(t, l, m);
    build(t, m + 1, r);
    up(t, l, r);
}

void mark(int t, int l, int r, int add, int rev_add){
    int id = get_id(t, l, r);
    coef[id] = (coef[id] + add) % MOD;
    rev_coef[id] = (rev_coef[id] + rev_add) % MOD;
    sum[id] = (sum[id] + gp_sum(r - l + 1, add)) % MOD;
    sum[id] = (sum[id] + gp_sum(r - l + 1, rev_add)) % MOD;
}

void down(int t, int l, int r){
    int id = get_id(t, l, r);
    if(l == r) return;
    int m = (l + r) >> 1;
    mark(t, l, m, coef[id], (ll)rev_coef[id] * pw[r - m] % MOD);
    mark(t, m + 1, r, (ll)coef[id] * pw[m - l + 1] % MOD, rev_coef[id]);
    coef[id] = rev_coef[id] = 0;
}

void cover(int t, int l, int r, int a, int b, int x, int rev_x){
    if(r < a || l > b) return;
    int id = get_id(t, l, r);
    if(coef[id] != 0 || rev_coef[id] != 0){
        down(t, l, r);
    }
    if(a <= l && r <= b){
        mark(t, l, r, (ll)x * pw[l - a] % MOD, (ll)rev_x * pw[b - r] % MOD);
        return;
    }
    int m = (l + r) >> 1;
    cover(t, l, m, a, b, x, rev_x);
    cover(t, m + 1, r, a, b, x, rev_x);
    up(t, l, r);
}

int query(int t, int l, int r, int a, int b){
    if(r < a || l > b) return 0;
    int id = get_id(t, l, r);
    if(coef[id] != 0 || rev_coef[id] != 0){
        down(t, l, r);
    }
    if(a <= l && r <= b){
        return sum[id];
    }
    int m = (l + r) >> 1;
    return (query(t, l, m, a, b) + query(t, m + 1, r, a, b)) % MOD;
}

void heavy_light_decomposition(int root, int n){
    memset(dep, -1, sizeof(dep));
    all = 0;
    int l = 0, r = 1;
    dep[q[l] = root] = 0;
    parent[root] = -1;
    while(l < r){
        int u = q[l++];
        vis[u] = false;
        for(int i = 0; i < children[u].size(); ++i){
            int v = children[u][i];
            if(dep[v] == -1){
                dep[q[r++] = v] = dep[u] + 1;
                parent[v] = u;
            }
        }
    }
    for(int i = n - 1; i >= 0; i--){
        int u = q[i], p = -1;
        size[u] = 1;
        for(int i = 0; i < children[u].size(); ++i){
            int v = children[u][i];
            if(vis[v]){
                size[u] += size[v];
                if(p == -1 || size[v] > size[p]){
                    p = v;
                }
            }
        }
        if(p == -1){
            belong[top[all] = u] = all;
            idx[u] = 0;
            son[u] = u;
            len[all++] = 1;
        } else {
            top[belong[u] = belong[p]] = u;
            idx[u] = len[belong[u]]++;
            son[u] = p;
        }
        vis[u] = true;
    }
    tree[0] = 0;
    for(int i = 1; i < all; i++){//
        tree[i] = tree[i - 1] + 2 * len[i - 1] - 1;
    }
    for(int i = 0; i < all; i++){
        build(i, 0, len[i] - 1);
    }
}

void change(int a, int b, int x){
    vector<int> A, B;
    while(belong[a] != belong[b]){
        if(dep[top[belong[a]]] < dep[top[belong[b]]]){
            B.push_back(b);
            b = parent[top[belong[b]]];
        } else {
            A.push_back(a);
            a = parent[top[belong[a]]];
        }
    }
    if(dep[a] < dep[b]){
        B.push_back(b);
        A.push_back(0);
    } else {
        A.push_back(a);
        B.push_back(0);
    }
    int X = x;
    for(int i = 0; i < A.size(); ++i){
        if(i == A.size() - 1 && dep[a] < dep[b]) continue;
        int from = idx[A[i]], to = (i == A.size() - 1) ? idx[b] : idx[top[belong[A[i]]]];
        cover(belong[A[i]], 0, len[belong[A[i]]] - 1, from, to, X, 0);
        X = (ll)X * pw[to - from + 1] % MOD;
    }
    reverse(B.begin(), B.end());
    for(int i = 0; i < B.size(); ++i){
        if(i == 0 && dep[a] >= dep[b]) continue;
        int from = idx[B[i]], to = (i == 0) ? idx[a] : idx[top[belong[B[i]]]];
        cover(belong[B[i]], 0, len[belong[B[i]]] - 1, from, to, 0, X);
        X = (ll)X * pw[to - from + 1] % MOD;
    }
}

int query(int a, int b){
    int res = 0;
    while(belong[a] != belong[b]){
        if(dep[top[belong[a]]] < dep[top[belong[b]]]){
            int tmp = query(belong[b], 0, len[belong[b]] - 1, idx[b], idx[top[belong[b]]]);
            res = (res + tmp) % MOD;
            b = parent[top[belong[b]]];
        } else {
            int tmp = query(belong[a], 0, len[belong[a]] - 1, idx[a], idx[top[belong[a]]]);
            res = (res + tmp) % MOD;
            a = parent[top[belong[a]]];
        }
    }

    if(dep[a] < dep[b]){
        int tmp = query(belong[a], 0, len[belong[a]] - 1, idx[b], idx[a]);
        res = (res + tmp) % MOD;
    } else {
        int tmp = query(belong[a], 0, len[belong[a]] - 1, idx[a], idx[b]);
        res = (res + tmp) % MOD;
    }
    return res;
}

int main(){
    while(scanf("%d %d", &n, &R) != EOF){
        pw[0] = 1;
        for(int i = 1; i <= n; ++i){
            pw[i] = (ll)pw[i - 1] * R % MOD;
        }
        mod_inv = inv(R - 1);
        for(int i = 0; i < n; ++i){
            children[i].clear();
        }
        int x, y;
        for(int i = 0; i < n - 1; ++i){
            scanf("%d %d", &x, &y);
            --x, --y;
            children[x].push_back(y);
            children[y].push_back(x);
        }
        heavy_light_decomposition(0, n);
        int U, Q;
        scanf("%d %d", &U, &Q);
        for(int i = 0; i < U; ++i){
            int u, v, x;
            scanf("%d %d %d", &u, &v, &x);
            --u, --v;
            change(u, v, x);
        }
        for(int i = 0; i < Q; ++i){
            int u, v;
            scanf("%d %d", &u, &v);
            --u, --v;
            printf("%d\n", query(u, v));
        }
    }
}
