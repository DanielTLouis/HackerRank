/*
Given a tree of N nodes, where each node is uniquely numbered in between [1, N]. Each node
also has a value which is initially 0. You need to perform following two operations in the
tree.
    1. Update Operation
    2. Report Operation
Update Operation
    U r t a b
    Adds ab + (a+1)b + (b+1)a to all nodes in the subtree rooted at t, considering that tree
    is rooted at r (see explanation for more details).
Report Operation
    R r t m
    Output the sum of all nodes in the subtree rooted at t, considering that tree is rooted at
    r. Output the sum modulo m (see explanation for more details).
Input Format
    First line contains N, number of nodes in the tree.
    Next N-1 lines contain two space separated integers x and y which denote that there is an
    edge between node x and node y.
    Next line contains Q, number of queries to follow.
    Next Q lines follow, each line will be either a report operation or an update operation.
Output Format
    For each report query output the answer in a separate line.
Constraints
    1 ≤ N ≤ 100000
    1 ≤ Q ≤ 100000
    1 ≤ m ≤ 101
    1 ≤ r, t, x, y ≤ N
    x ≠ y
    1 ≤ a, b ≤ 1018
Notes
    1. There will be at most one edge between a pair of nodes.
    2. There will be no loop.
    3. Tree will be completely connected.
Sample Input
    4
    1 2
    2 3
    3 4
    4
    U 3 2 2 2
    U 2 3 2 2
    R 1 2 8
    R 4 3 9
Sample Output
    2
    3
Explanation
    Initially Values in each node : [0,0,0,0]
    The first query is U 3 2 2 2. Here, tree is rooted at 3. It looks like
        3(0)
        / \
       /   \
      2(0)  4(0)
      |
      |
      1(0)
    For the sub tree rooted at 2 ( nodes 2 and 1 ), we add ab + (a+1)b + (b+1)a = 22 + 32 +
    32 = 22. After first update operation, nodes 1, 2, 3, and 4 will have values 22, 22, 0 and
    0 respectively.
        3(0)
        / \
       /   \
      2(22) 4(0)
            |
            |
            1(22)
    The second query is U 2 3 2 2. Here, tree is rooted at 2. It looks like
        2(22)
        / \
       /   \
      1(22) 3(0)
            |
            |
            4(0)
    For the sub tree rooted at 3 (nodes 3 and 4), we add ab + (a+1)b + (b+1)a = 22 + 32 + 32
    = 22. After second update operation, nodes 1, 2, 3, and 4 each have values 22,22,22,22
    respectively.
        2(22)
        / \
       /   \
     1(22) 3(22)
           |
           |
           4(22)
    The first report query is R 1 2 8 asks for the sum modulo 8 of the subtree rooted at 2,
    when the tree is rooted at 1. The tree looks like
    1(22)
     \
      \
       2*(22)
       |
       |
       3*(22)
       |
       |
       4*(22)
    The sum of the values of nodes 2, 3 and 4 are
        (22 + 22 + 22) % 8 = 2
    The second report query is R 4 3 9 asks for the sum modulo 9 of the subtree rooted at 3
    when the tree is rooted at 4. The tree looks like
        4(22)
         \
          \
           3*(22)
           |
           |
           2*(22)
           |
           |
           1*(22)
    The sum of the values of nodes 3, 2 and 1 are
        (22 + 22 + 22) % 9 = 3
Time Limits:
    C, C++: 4s | Java and other JVM based languages: 10s | Python, Python3 = 45s | Other
    interpreted Language: 30s | C#, Haskell: 10s | Rest: 3 times of default.
*/
#include<cstdio>
#include<vector>
using namespace std;

const int MAXN = 100000;

vector<int> v[MAXN + 1];
vector<int> child[MAXN + 1];
bool visited[MAXN + 1];
int startTime[MAXN + 1], endTime[MAXN + 1];

int dfs(int now, int start)
{
    startTime[now] = start;
    visited[now] = true;
    int sz = (int)v[now].size();
    for (int i = 0; i < sz; i++)
    {
        if (!visited[v[now][i]])
        {
            child[now].push_back(v[now][i]);
            start = dfs(v[now][i], start + 1);
        }
    }
    endTime[now] = start;
    return start;
}

const int NMOD = 5;
int MOD[NMOD] = { 11 * 101 * 13 * 97 * 17 * 89, 19 * 83 * 23 * 81 * 25 * 29, 31 * 79 * 37 * 73 * 41, 43 * 47 * 49 * 53 * 59, 61 * 64 * 67 * 71 };
int p[26] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 };

int modidx[102];

int gcd(int a, int b)
{
    return b ? gcd(b, a%b) : a;
}

void init()
{
    for (int i = 1; i <= 101; i++)
    {
        for (int j = 0; j < NMOD; j++)
        {
            if (gcd(i, MOD[j]) != 1)
            {
                modidx[i] = j;
                break;
            }
        }
    }
}

long long tree[NMOD][4 * MAXN], lazy[NMOD][4 * MAXN];

long long ext_euclid(long long a, long long b, long long& x, long long& y)
{
    long long t, d;
    if (b == 0) { x = 1; y = 0; return a; }
    d = ext_euclid(b, a%b, x, y);
    t = x, x = y, y = t - a / b*y;
    return d;
}

/*
long long linear_modular_equation_system(long long B[], long long W[], long long k)
{
    long long d, x, y, m, n = 1;
    long long a = 0;
    for (long long i = 0; i < k; i++)
        n *= W[i];
    for (long long i = 0; i < k; i++)
    {
        m = n / W[i];
        d = ext_euclid(W[i], m, x, y);
        while (y < 0) y += W[i];
        a += y * (m * B[i] % n);
    }
    while (a < 0) a += n;
    return a % n;
}
*/

long long linear_modular_equation_system(long long B[], long long W[], long long k)
{
    long long d, x, y, m, n = 1;
    long long a = 0;
    for (long long i = 0; i < k; i++)
        n *= W[i];
    for (long long i = 0; i < k; i++)
    {
        m = n / W[i];
        d = ext_euclid(W[i], m, x, y);
        a = (a + y*m*B[i]) % n;
    }
    if (a>0) return a;
    else return a + n;
}

void updateTree(long long node, long long a, long long b, long long i, long long j, long long value, long long modidx)
{
    if (lazy[modidx][node] != 0)
    {
        tree[modidx][node] = (tree[modidx][node] + (long long)(b - a + 1) * lazy[modidx][node]) % MOD[modidx];

        if (a != b)
        {
            lazy[modidx][node * 2] = (lazy[modidx][node * 2] + lazy[modidx][node]) % MOD[modidx];
            lazy[modidx][node * 2 + 1] = (lazy[modidx][node * 2 + 1] + lazy[modidx][node]) % MOD[modidx];
        }

        lazy[modidx][node] = 0;
    }

    if (a > b || a > j || b < i) return;

    if (a >= i && b <= j)
    {
        tree[modidx][node] = (tree[modidx][node] + (long long)(b - a + 1) * value) % MOD[modidx];

        if (a != b)
        {
            lazy[modidx][node * 2] = (lazy[modidx][node * 2] + value) % MOD[modidx];
            lazy[modidx][node * 2 + 1] = (lazy[modidx][node * 2 + 1] + value) % MOD[modidx];
        }

        return;
    }

    updateTree(node * 2, a, (a + b) / 2, i, j, value, modidx);
    updateTree(node * 2 + 1, (a + b) / 2 + 1, b, i, j, value, modidx);

    tree[modidx][node] = (tree[modidx][node * 2] + tree[modidx][node * 2 + 1]) % MOD[modidx];
}

long long queryTree(long long node, long long a, long long b, long long i, long long j, long long modidx)
{
    if (a > b || a > j || b < i) return 0;

    if (lazy[modidx][node] != 0)
    {
        tree[modidx][node] = (tree[modidx][node] + (long long)(b - a + 1) * lazy[modidx][node]) % MOD[modidx];
        if (a != b)
        {
            lazy[modidx][node * 2] = (lazy[modidx][node * 2] + lazy[modidx][node]) % MOD[modidx];
            lazy[modidx][node * 2 + 1] = (lazy[modidx][node * 2 + 1] + lazy[modidx][node]) % MOD[modidx];
        }
        lazy[modidx][node] = 0;
    }

    if (a >= i && b <= j) return tree[modidx][node];

    long long q1 = queryTree(node * 2, a, (a + b) / 2, i, j, modidx);
    long long q2 = queryTree(node * 2 + 1, (a + b) / 2 + 1, b, i, j, modidx);
    long long tmp = q1 + q2;
    return tmp % MOD[modidx];
}

int ModExp(long long a, long long b, int mod)
{
    a %= mod;
    long long c = 1, d = a;
    while (b)
    {
        if (b & 1) c = (c*d) % mod;
        d = (d*d) % mod;
        b >>= 1;
    }
    return (int)c;
}

int calc(long long a, long long b, int mod)
{
    long long sum1 = ModExp(a, b, mod);
    long long sum2 = ModExp(a + 1, b, mod);
    long long sum3 = ModExp(b + 1, a, mod);
    return (sum1 + sum2 + sum3) % mod;
}

int binarySearchChild(int root, int st, int en)
{
    int lo = 0, hi = (int)child[root].size(), mid = 0;

    while (lo < hi - 1)
    {
        mid = (lo + hi) / 2;
        int st_mid = startTime[child[root][mid]];
        int en_mid = endTime[child[root][mid]];

        if (st >= st_mid && en <= en_mid) return mid;
        else if (en <= st_mid) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main()
{
    init();

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 1);

    int q;
    scanf("%d", &q);
    getchar();
    while (q--)
    {
        char ch;
        int r, t, m;
        long long a, b;
        ch = getchar();
        if (ch == 'U')
        {
            scanf("%d%d%lld%lld", &r, &t, &a, &b);
            getchar();

            int sr = startTime[r], er = endTime[r];
            int st = startTime[t], et = endTime[t];

            int val[NMOD];

            for (int i = 0; i < NMOD; i++)
                val[i] = calc(a, b, MOD[i]);

            if (sr == st && er == et)
            {
                for (int i = 0; i < NMOD; i++)
                    updateTree(1, startTime[1], endTime[1], startTime[1], endTime[1], val[i], i);
            }
            else if (sr > st && er <= et)
            {
                for (int i = 0; i < NMOD; i++)
                    updateTree(1, startTime[1], endTime[1], startTime[1], endTime[1], val[i], i);
                int childIdx = binarySearchChild(t, sr, er);
                for (int i = 0; i < NMOD; i++)
                    updateTree(1, startTime[1], endTime[1], startTime[child[t][childIdx]], endTime[child[t][childIdx]], MOD[i] - val[i], i);
            }
            else
            {
                for (int i = 0; i < NMOD; i++)
                    updateTree(1, startTime[1], endTime[1], st, et, val[i], i);
            }
        }
        else
        {
            scanf("%d%d%d", &r, &t, &m);
            getchar();

            if (m == 1)
            {
                printf("0\n");
                continue;
            }

            int sr = startTime[r], er = endTime[r];
            int st = startTime[t], et = endTime[t];

            int _m = m;

            long long W[6], B[6], k = 0;
            for (int i = 0; i < 26; i++)
            {
                int tmp = 1;
                bool flag = false;
                while (m % p[i] == 0)
                {
                    flag = true;
                    m /= p[i];
                    tmp *= p[i];
                }
                if (flag)
                    W[k++] = tmp;
            }

            if (sr == st && er == et)
            {
                for (int i = 0; i < k; i++)
                    B[i] = queryTree(1, startTime[1], endTime[1], startTime[1], endTime[1], modidx[W[i]]) % W[i];
                printf("%lld\n", linear_modular_equation_system(B, W, k) % _m);
            }
            else if (sr > st && er <= et)
            {
                int childIdx = binarySearchChild(t, sr, er);
                for (int i = 0; i < k; i++)
                {
                    long long tmp1 = queryTree(1, startTime[1], endTime[1], startTime[1], endTime[1], modidx[W[i]]) % W[i];
                    long long tmp2 = queryTree(1, startTime[1], endTime[1], startTime[child[t][childIdx]], endTime[child[t][childIdx]], modidx[W[i]]) % W[i];
                    B[i] = (tmp1 + W[i] - tmp2) % W[i];
                }
                printf("%lld\n", linear_modular_equation_system(B, W, k) % _m);
            }
            else
            {
                for (int i = 0; i < k; i++)
                    B[i] = queryTree(1, startTime[1], endTime[1], st, et, modidx[W[i]]) % W[i];
                printf("%lld\n", linear_modular_equation_system(B, W, k) % _m);
            }
        }
    }
    return 0;
}
