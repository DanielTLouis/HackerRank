/*
Alice purchased an array of n wooden boxes that she indexed from 0 to n-1. On each box i
 she writes an integer that we'll refer to as box_i.
Alice wants you to perform q operations on the array of boxes. Each operation is in one
of the following forms:
(Note: For each type of operations, l<=i<=r)
   * 1 l r c: Add c to each box_i. Note that  can be negative.
   * 2 l r d: Replace each box_i with [box_i/d].
   * 3 l r: Print the minimum value of any box_i.
   * 4 l r: Print the sum of all box_1.
Recall that [x] is the maximum integer y such that y<=x (e.g., [-2.5]] = -3 and [-7]=-7).
Given n, the value of each b_i, and q operations, can you perform all the operations
efficiently?
Input Format
    The first line contains two space-separated integers denoting the respective values
    of  (the number of boxes) and q (the number of operations).
    The second line contains n space-separated integers describing the respective values
    of box_0,box_1,...,box_n-1 (i.e., the integers written on each box). E   ach of the
    subsequent lines describes an operation in one of the four formats
    defined above.
Constraints
    1<=n,q<=10^5
    -10^9<=box_i<=10^9
    0<=l<=r<=n-1
    -10^4 <-c<=10^4
    2<=d<=29
Output Format
    For each operation of type 3 or type 4, print the answer on a new line.
Sample Input 0
    10 10
    -5 -4 -3 -2 -1 0 1 2 3 4
    1 0 4 1
    1 5 9 1
    2 0 9 3
    3 0 9
    4 0 9
    3 0 1
    4 2 3
    3 4 5
    4 6 7
    3 8 9
Sample Output 0
    -2
    -2
    -2
    -2
    0
    1
    1
*/

#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(2e9) + int(1e8);
const ll infl = ll(2e18) + ll(1e10);

const int base = 1 << 17;

ll func(int p, int q) {
    if (p >= 0)
        return p / q;
    return -((-p + q - 1) / q);
}

int iter;

struct Tree {
    ll sum[base * 2];
    int vmin[base * 2];
    int vmax[base * 2];
    int add[base * 2];

    void update(int u) {
        vmin[u] = min(vmin[u * 2], vmin[u * 2 + 1]);
        vmax[u] = max(vmax[u * 2], vmax[u * 2 + 1]);
        sum[u] = sum[u * 2] + sum[u * 2 + 1];
    }

    void _put(int u, int val, int len) {
        add[u] += val;
        vmin[u] += val;
        vmax[u] += val;
        sum[u] += val * len;
    }

    void push(int u, int cl, int cr) {
        if (add[u]) {
            int len = (cr - cl) / 2;
            _put(u * 2, add[u], len);
            _put(u * 2 + 1, add[u], len);
            add[u] = 0;
        }
    }

    ll getSum(int l, int r, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r)
            return sum[v];
        if (r <= cl || cr <= l)
            return 0;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        return getSum(l, r, v * 2, cl, cc) + getSum(l, r, v * 2 + 1, cc, cr);
    }

    int getMax(int l, int r, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r)
            return vmax[v];
        if (r <= cl || cr <= l)
            return -inf;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        return max(getMax(l, r, v * 2, cl, cc), getMax(l, r, v * 2 + 1, cc, cr));
    }

    int getMin(int l, int r, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r)
            return vmin[v];
        if (r <= cl || cr <= l)
            return inf;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        return min(getMin(l, r, v * 2, cl, cc), getMin(l, r, v * 2 + 1, cc, cr));
    }

    void put(int l, int r, int delta, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r) {
            _put(v, delta, cr - cl);
            return;
        }
        if (r <= cl || cr <= l)
            return;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        put(l, r, delta, v * 2, cl, cc);
        put(l, r, delta, v * 2 + 1, cc, cr);
        update(v);
    }

    void divide(int l, int r, int x, int v = 1, int cl = 0, int cr = base) {
        ++iter;
        if (x == 1)
            return;
        if (l <= cl && cr <= r) {
            int d1 = func(vmin[v], x) - vmin[v];
            int d2 = func(vmax[v], x) - vmax[v];
            if (d1 == d2) {
                _put(v, d1, cr - cl);
                return;
            }
        }
        if (r <= cl || cr <= l)
            return;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        divide(l, r, x, v * 2, cl, cc);
        divide(l, r, x, v * 2 + 1, cc, cr);
        update(v);
    }

    void build(int n) {
        forn (i, 2 * base)
            add[i] = 0;
        for (int i = n + base; i < 2 * base; ++i)
            sum[i] = 0, vmin[i] = inf, vmax[i] = -inf;
        for (int i = base - 1; i > 0; --i)
            update(i);
    }
} t;

int main() {

    //assert(freopen("goodinput/input01.txt", "r", stdin));

    int n, q;
    scanf("%d%d", &n, &q);
    forn (i, n) {
        int a;
        scanf("%d", &a);
        t.sum[i + base] = t.vmin[i + base] = t.vmax[i + base] = a;
    }
    t.build(n);
    forn (i, q) {
        int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        l++;
        r++;
        if (op == 1 || op == 2)
            scanf("%d", &x);
        --l;
        if (op == 1)
            t.put(l, r, x);
        else if (op == 2)
            t.divide(l, r, x);
        else if (op == 3)
            cout << t.getMin(l, r) << '\n';
        else if (op == 4)
            cout << t.getSum(l, r) << '\n';
        else
            assert(false);
    }
    cerr << iter << " iterations\n";
    cerr << "time: " << clock() / 1000 << "ms\n";
}-
