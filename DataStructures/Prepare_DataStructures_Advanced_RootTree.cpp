/*
You are given a rooted tree* with N nodes and the root of the tree, R, is also given. Each
node of the tree contains a value, that is initially empty. You have to mantain the tree under
two operations:
    1. Update Operation
    2. Report Operation
* http://en.wikipedia.org/wiki/Tree_(graph_theory) *
Update Operation
    Each Update Operation begins with the character U. Character U is followed by 3 integers T,
    V and K. For every node which is the descendent of the node T, update it's value by adding
    V + d*K, where V and K are the parameters of the query and d is the distance of the node
    from T. Note that V is added to node T.
Report Operation
    Each Report Operation begins with the character Q. Character Q is followed by 2 integers,
    A and B. Output the sum of values of nodes in the path from A to B modulo (109 + 7)
Input Format
    The first Line consists of 3 space separated integers, N E R, where N is the number of
    nodes present, E is the total number of queries (update + report), and R is root of the
    tree.
    Each of the next N-1 lines contains 2 space separated integers, X and Y (X and Y are
    connected by an edge).
    Thereafter, E lines follows: each line can represent either the Update Operation or the
    Report Operation.
        * Update Operation is of the form : U T V K.
        * Report Operation is of the form : Q A B.
Output Format
    Output the answer for every given report operation.
Constraints
    1 ≤ N, E ≤ 105
    1 ≤ E ≤ 105
    1 ≤ R, X, Y, T, A, B ≤ N
    1 ≤ V, K ≤ 109
    X ≠ Y
Sample Input
    7 7 1
    1 2
    2 3
    2 4
    2 5
    5 6
    6 7
    U 5 10 2
    U 4 5 3
    Q 1 7
    U 6 7 4
    Q 2 7
    Q 1 4
    Q 2 4
Sample Output
    36
    54
    5
    5
Explanation
    * Values of Nodes after U 5 10 2: [0 0 0 0 10 12 14].
    * Values of Nodes after U 4 5 3: [0 0 0 5 10 12 14].
    * Sum of the Nodes from 1 to 7: 0 + 0 + 10 + 12 + 14 = 36.
    * Values of Nodes after U 6 7 4: [0 0 0 5 10 19 25].
    * Sum of the Nodes from 2 to 7: 0 + 10 + 19 + 25 = 54.
    * Sum of the Nodes from 1 to 4: 0 + 0 + 5 = 5.
    * Sum of the Nodes from 2 to 4: 0 + 5 = 5.
*/
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < b; i++)
#define S(x) scanf("%d",&x)
#define P(x) printf("%d\n",x)
typedef long long int LL;

const int mod = 1000000007;
const int MAXN = 100005;
vector<int> g[MAXN];
int dep[MAXN];
int P[MAXN];
int _tm;
int tin[2 * MAXN];
int tout[2 * MAXN];
int n;
int L[MAXN][25];
LL bit1[2 * MAXN], bit2[2 * MAXN], bit3[2 * MAXN];

LL _pow(LL a, LL b){
    if(!b) return 1;
    if(b == 1) return a;
    if(b == 2) return (a * a) % mod;
    if(b & 1) return (a * _pow(a, b - 1)) % mod;
    return _pow(_pow(a, b / 2), 2);
}

void dfs(int c, int p, int d){
    P[c] = p;
    dep[c] = d;
    _tm++;
    tin[c] = _tm;
    rep(i, 0, g[c].size()){
        int u = g[c][i];
        if(u != p) dfs(u, c, d + 1);
    }
    _tm++;
    tout[c] = _tm;
}

void processLca(){
    int i, j;
  //we initialize every element in P with -1
    int N = n;
      for(i = 0; i < n; i++)
          for(j = 0; 1 << j < N; j++)
              L[i][j] = -1;
  //the first ancestor of every node i is T[i]
      for(i = 0; i < N; i++)
          L[i][0] = P[i];
  //bottom up dynamic programing
      for(j = 1; 1 << j < N; j++)
         for(i = 0; i < N; i++)
             if (L[i][j - 1] != -1)
                 L[i][j] = L[L[i][j - 1]][j - 1];
}

int lca(int p, int q){
      int tmp, log, i;
  //if p is situated on a higher level than q then we swap them
      if (dep[p] < dep[q])
          tmp = p, p = q, q = tmp;
  //we compute the value of [log(L[p)]
      for(log = 1; 1 << log <= dep[p]; log++);
      log--;
  //we find the ancestor of node p situated on the same level
  //with q using the values in P
      for(i = log; i >= 0; i--)
          if (dep[p] - (1 << i) >= dep[q])
              p = L[p][i];
      if (p == q)
          return p;
  //we compute LCA(p, q) using the values in P
      for(i = log; i >= 0; i--)
          if (L[p][i] != -1 && L[p][i] != L[q][i])
              p = L[p][i], q = L[q][i];
      return P[p];
}

void update(LL *bit, int idx, LL val){
    for(int i = idx; i <= _tm; i += i & -i) bit[i] += val;
}

LL query(LL *bit, int idx){
    LL res = 0;
    for(int i = idx; i; i -= i & -i){
        res += bit[i];
    }
    return res % mod;
}

LL QQQ(int x){
    LL res;
    LL c = dep[x];
    res = (query(bit1, tin[x]) * c) % mod;
    res += (query(bit2, tin[x]) * (((LL)c * c)%mod));
    res %= mod;
    res += query(bit3, tin[x]);
    return res % mod;
}

int main(){
    int e, r;
    scanf("%d%d%d", &n, &e, &r);
    r--;
    rep(i, 0, n - 1){
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(r,-1,0);
    processLca();
    while(e--){
        char s[5];
        scanf("%s", s);
        if(s[0] == 'U'){
            int T, V, K;
            scanf("%d%d%d", &T, &V, &K);
            T--;
            LL k = ((LL)K * _pow(2, mod - 2)) % mod;
            LL p = dep[T];
            LL val;
            val = (V - 2 * p * k + k) % mod;
            val = (val + mod) % mod;
            update(bit1, tin[T], val);
            update(bit1, tout[T] + 1, -val);
            val = k;
            update(bit2, tin[T], val);
            update(bit2, tout[T] + 1, -val);
            val = (p * p) % mod;
            val = (val * k) % mod;
            val -= p * (V + k);
            val %= mod;
            val += mod + V;
            val %= mod;
            update(bit3, tin[T], val);
            update(bit3, tout[T] + 1, -val);
        } else {
            int A, B;
            scanf("%d%d", &A, &B);
            A--; B--;
            LL ans = 0;
            int l = lca(A, B);
            ans = QQQ(A) + QQQ(B) - QQQ(l);
            if(P[l] != -1) ans -= QQQ(P[l]);
            ans %= mod;
            ans += mod;
            ans %= mod;
            printf("%lld\n", ans);
        }
    }
    return 0;
}
