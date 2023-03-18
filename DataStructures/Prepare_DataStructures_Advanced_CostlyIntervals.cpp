/*
Given an array, your goal is to find, for each element, the largest subarray containing it
whose cost is at least k.
Specifically, let A=[A1,A2,...,An] be an array of length n, and let A_l...r=[Al,...,Ar] be the
subarray from index l to index r. Also,
    * Let MAX(l,r) be the largest number in A_l...r.
    * Let MIN(l,r) be the smallest number in A_l...r.
    * Let OR(l,r) be the bitwise OR** of the elements of A_l...r.
    * Let AND(l,r) be the bitwise AND** of the elements of A_l...r.
* https://en.wikipedia.org/wiki/Bitwise_operation#OR *
** https://en.wikipedia.org/wiki/Bitwise_operation#AND **
The cost of A_l...r, denoted cost(l,r), is defined as
    cost(l,r)=(OR(l,r)-AND(l,r))-(MAX(l,r)-MIN(l,r))
The size of A_l..r is defined as r-l+1.
You are given the array A and and an integer k. For each index i from 1 to n, your goal is to
find the largest size of any subarray A_l...r such that 1<=l<=i<=r<=n and cost(l,r)>=k.
Consider, array A=[2,4,3,1,7] and k=6. The possible sub-arrays and their costs would be as
follows:
    image
Complete the function costlyIntervals which takes two integers n and k as first line of input,
and array A1,A2,...,An in the second line of input. Return an array of n integers, where the
ith element contains the answer for index i of the input array, 1<=i<=n. Every element of the
output array denotes the largest size of a subarray containing i whose cost is at least k, or
-1 if there is no such subarray.
Constraints
    1<=n<=10^5
    0<=A_i<=10^9
    0<=k<=10^9
Subtasks
    For 5% of the maximum score, n<=100.
    For 15% of the maximum score, n<=5X10^3.
Sample Input
    n=5, k=6
    A=[2,4,3,1,7]
Sample Output
    [-1,2,2,-1,-1]
Explanation
    In this example, we have k=6. There is only one subarray whose cost is at least 6, and
    that is A_2...3=[4,3], since cost(2,3)=6. Its size is 2. Thus, for i=2 and i=3, the answer
    is 2, and for the others, -1.
*/

#include <bits/stdc++.h>
using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORd(i, a, b) for (int i = (a) - 1; i >= (b); i--)
#define FORall(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define sz(a) int((a).size())
#define pconent(t, x) (t.find(x) != t.end())
#define all(a) (a).begin(), (a).end()
#define uni(a) (a).erase(unique(all(a)), (a).end())
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define prec(n) fixed<<setprecision(n)
#define bit(n, i) (((n) >> (i)) & 1)
#define bitcount(n) __builtin_popcountll(n)
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pi;
typedef vector<int> vi;
typedef vector<pi> vii;
const int MOD = (int) 1e9 + 7;
const int FFTMOD = 1007681537;
const int INF = (int) 1e9;
const ll LINF = (ll) 1e18;
const ld PI = acos((ld) -1);
const ld EPS = 1e-9;
inline ll gcd(ll a, ll b) {ll r; while (b) {r = a % b; a = b; b = r;} return a;}
inline ll lcm(ll a, ll b) {return a / gcd(a, b) * b;}
inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = n * n % p;} return r;}
template<class T> inline int chkmin(T& a, const T& val) {return val < a ? a = val, 1 : 0;}
template<class T> inline int chkmax(T& a, const T& val) {return a < val ? a = val, 1 : 0;}
inline ll isqrt(ll k) {ll r = sqrt(k) + 1; while (r * r > k) r--; return r;}
inline ll icbrt(ll k) {ll r = cbrt(k) + 1; while (r * r * r > k) r--; return r;}
inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}
inline int inv(int a, int p = MOD) {return fpow(a, p - 2, p);}
inline int sign(ld x) {return x < -EPS ? -1 : x > +EPS;}
inline int sign(ld x, ld y) {return sign(x - y);}
#define db(x) cerr << #x << " = " << (x) << " ";
#define endln cerr << "\n";

template<class T> struct RMQOR {
    int n;
    vector<T> a;
    vector<vector<T> > f;

    T best(T a, T b) {
        return a | b;
    }
    void init(int n) {
        this->n = n;
        int p = 1; while ((1 << p) < n) p++;
        a.resize(n), f.resize(p + 1);
        for (int i = 0; i < (int) f.size(); i++) {
            f[i].resize(n);
        }
    }
    void upd(int u, T x) {
        a[u] = x;
    }
    void build() {
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int l = 0, k; (k = 1 << l) < n; l++) {
            for (int i = 0; i + k < n; i++) {
                f[l + 1][i] = best(f[l][i], f[l][i + k]);
            }
        }
    }
    T query(int a, int b) {
        int l = a == b ? 0 : __lg(b - a);
        return best(f[l][a], f[l][b - (1 << l) + 1]);
    }
};
RMQOR<long long> rmq_or;
template<class T> struct RMQAND {
    int n;
    vector<T> a;
    vector<vector<T> > f;

    T best(T a, T b) {
        return a & b;
    }
    void init(int n) {
        this->n = n;
        int p = 1; while ((1 << p) < n) p++;
        a.resize(n), f.resize(p + 1);
        for (int i = 0; i < (int) f.size(); i++) {
            f[i].resize(n);
        }
    }
    void upd(int u, T x) {
        a[u] = x;
    }
    void build() {
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int l = 0, k; (k = 1 << l) < n; l++) {
            for (int i = 0; i + k < n; i++) {
                f[l + 1][i] = best(f[l][i], f[l][i + k]);
            }
        }
    }
    T query(int a, int b) {
        int l = a == b ? 0 : __lg(b - a);
        return best(f[l][a], f[l][b - (1 << l) + 1]);
    }
};
RMQAND<long long> rmq_and;
template<class T, class cmp = less<T> > struct RMQ2 {
    int n;
    vector<T> a;
    vector<vector<T> > f;

    T best(T a, T b) {
        if (cmp()(a, b)) return a;
        return b;
    }
    void init(int n) {
        this->n = n;
        int p = 1; while ((1 << p) < n) p++;
        a.resize(n), f.resize(p + 1);
        for (int i = 0; i < (int) f.size(); i++) {
            f[i].resize(n);
        }
    }
    void upd(int u, T x) {
        a[u] = x;
    }
    void build() {
        for (int i = 0; i < n; i++) f[0][i] = a[i];
        for (int l = 0, k; (k = 1 << l) < n; l++) {
            for (int i = 0; i + k < n; i++) {
                f[l + 1][i] = best(f[l][i], f[l][i + k]);
            }
        }
    }
    T query(int a, int b) {
        int l = a == b ? 0 : __lg(b - a);
        return best(f[l][a], f[l][b - (1 << l) + 1]);
    }
};
RMQ2<int> rmq_min;
RMQ2<int, greater<int> > rmq_max;

const int maxn = 1e5 + 5;
const int logn = 31;
int n, k;
int a[maxn];
int nxt0[maxn][logn];
int nxt1[maxn][logn];

void solve() {
    cin >> n >> k;
    rmq_or.init(n);
    rmq_and.init(n);
    rmq_min.init(n);
    rmq_max.init(n);
    FOR(i, 0, n) {
        cin >> a[i];
        rmq_or.upd(i, a[i]);
        rmq_and.upd(i, a[i]);
        rmq_min.upd(i, a[i]);
        rmq_max.upd(i, a[i]);
    }
    rmq_or.build();
    rmq_and.build();
    rmq_min.build();
    rmq_max.build();
    static int lst0[logn];
    static int lst1[logn];
    fill_n(lst0, logn, n);
    fill_n(lst1, logn, n);
    FORd(i, n, 0) {
        FOR(j, 0, logn) {
            if (!bit(a[i], j)) {
                lst0[j] = i;
            }
            else {
                lst1[j] = i;
            }
        }
        FOR(j, 0, logn) nxt0[i][j] = lst0[j];
        FOR(j, 0, logn) nxt1[i][j] = lst1[j];
    }
    vector<pi> events;
    FOR(i, 0, n) {
        int mx = -1;
        long long cost = 0, sor = a[i], sand = a[i];
        int ptr = i;
        if (cost >= k) {
            mx = i;
        }
        while (ptr < n - 1) {
            int nptr = n;
            FOR(j, 0, logn) {
                if (bit(sand, j)) {
                    chkmin(nptr, nxt0[ptr + 1][j]);
                }
                if (!bit(sor, j)) {
                    chkmin(nptr, nxt1[ptr + 1][j]);
                }
            }
            int lo = ptr, hi = nptr - 1;
            while (lo < hi) {
                int mi = lo + hi + 1 >> 1;
                if (rmq_or.query(i, mi) - rmq_and.query(i, mi) - rmq_max.query(i, mi) + rmq_min.query(i, mi) >= k) {
                    lo = mi;
                }
                else {
                    hi = mi - 1;
                }
            }
            int mi = lo + hi >> 1;
            if (rmq_or.query(i, mi) - rmq_and.query(i, mi) - rmq_max.query(i, mi) + rmq_min.query(i, mi) >= k) {
                mx = mi;
            }
            if (nptr == n) {
                break;
            }
            ptr = nptr;
            sor = rmq_or.query(i, ptr);
            sand = rmq_and.query(i, ptr);
        }
        if (~mx) {
            int len = mx - i + 1;
            events.pb(mp(i, len));
            events.pb(mp(mx + 1, -len));
        }
    }
    sort(all(events));
    multiset<int> heap;
    int ptr = 0;
    FOR(i, 0, n) {
        while (ptr < sz(events) && events[ptr].fi <= i) {
            int x = events[ptr].se;
            if (x > 0) {
                heap.insert(x);
            }
            else {
                heap.erase(heap.find(-x));
            }
            ptr++;
        }
        cout << (sz(heap) ? *heap.rbegin() : -1) << "\n";
    }
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    if (argc > 1) {
        assert(freopen(argv[1], "r", stdin));
    }
    if (argc > 2) {
        assert(freopen(argv[2], "wb", stdout));
    }
    solve();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
