/*
A Sumo wrestling championship is scheduled to be held this winter in the HackerCity where N
wrestlers from different parts of the world are going to participate. The rules state that two
wrestlers can fight against each other if and only if the difference in their height is less
than or equal to K,
(i.e) wrestler A and wrestler B can fight if and only if |height(A)-height(B)|<=K.
Given an array H[], where H[i] represents the height of the ith fighter, for a given l, r
where 0 <= l <= r < N, can you count the number of pairs of fighters between l and r (both
inclusive) who qualify to play a game?
Input Format
    The first line contains an integer N and K separated by a single space representing the
    number of Sumo wrestlers who are going to participate and the height difference K.
    The second line contains N integers separated by a single space, representing their
    heights H[0] H[1] ... H[N - 1].
    The third line contains Q, the number of queries. This is followed by Q lines each having
    two integers l and r separated by a space.
Output Format
    For each query Q, output the corresponding value of the number of pairs of fighters for
    whom the absolute difference of height is not greater that K.
Constraints
    1 <= N <= 100000
    0 <= K <= 109
    0 <= H[i] <= 109
    1 <= Q <= 100000
    0 <= l <= r < N
Sample Input
    5 2
    1 3 4 3 0
    3
    0 1
    1 3
    0 4
Sample Output
    1
    3
    6
Explanation
    Query #0: Between 0 and 1 we have i,j as (0,1) and |H[0]-H[1]|=2 therefore output is 1.
    Query #1: The pairs (H[1],H[2]) (H[1],H[3]) and (H[2],H[3]) are the pairs such that
    |H[i]-H[j]| <=2. Hence output is 3.
    Query #2: Apart from those in Query #1, we have (H[0],H[1]), (H[0], H[3]), (H[0], H[4]),
    hence 6.
    Timelimits
    Timelimits are given here
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
using namespace std;
#define mp make_pair
#define ll long long
const int mx=1e5+10;

#define gc getchar_unlocked
void scan(int &x)
{
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}

static ll b2d[410][410], b1d[mx][410];
static int h[mx], szb[410], lb[410], rb[410];
pair<int, int> bb[410], *buck[410];
int n, k, q, sqr;

inline void cum2d()
{
    rep(i, 1, 409) rep(j, 1, 409)
        b2d[i][j] += b2d[i-1][j]+b2d[i][j-1]-b2d[i-1][j-1];
}
inline void cum1d()
{
    rep(i, 0, n) rep(j, 1, 409)
        b1d[i][j] += b1d[i][j-1];
}

inline ll inonev(int* v, int sz)
{
    if(sz<=0) return 0;

    ll ret = 0; int up=0;
    rep(i, 0, sz-1)
    {
        while(v[up] <= v[i]+k and up<sz) up++;
        ret += up-(i+1);
    }
    return ret;
}
inline ll intwov(int* v1, int sz1, int* v2, int sz2)
{
    if(sz1<=0 or sz2<=0) return 0;

    ll ret=0; int low=0, up=0;
    rep(i, 0, sz1-1)
    {
        while(v2[low] < v1[i]-k and low<sz2) low++;
        while(v2[up] <= v1[i]+k and up<sz2) up++;
        ret += up-low;
    }
    return ret;
}

void process()
{
    for(int i=0; i*sqr<n; ++i)
    {
        int s=i*sqr, e=min(n-1, s+sqr-1);
        buck[i+1]=new pair<int, int>[e-s+1]; szb[i+1]=e-s+1;

        rep(j, s, e)
            buck[i+1][j-s] = mp(h[j], j),
            lb[j-s] = h[j];
        sort(lb, lb+szb[i+1]);
        sort(buck[i+1], buck[i+1]+szb[i+1]);

        ll val=inonev(lb, szb[i+1]);
        b2d[i+1][i+1] += val;

        rep(j, 1, i)
        {
            val=0; int up=0, low=0;
            rep(l, 0, szb[i+1]-1)
            {
                while(buck[j][low].first < buck[i+1][l].first-k and low<szb[j]) low++;
                while(buck[j][up].first <= buck[i+1][l].first+k and up<szb[j]) up++;
                b1d[buck[i+1][l].second][j] += up-low; val += up-low;
            }
            b2d[j][i+1]+=val;
        }
    }

    for(int i=0; i*sqr<=n; ++i)
    {
        for(int j=i+2; szb[j]; ++j)
        {
            int up=0, low=0;
            rep(l, 0, szb[i+1]-1)
            {
                while(buck[j][low].first < buck[i+1][l].first-k and low<szb[j]) low++;
                while(buck[j][up].first <= buck[i+1][l].first+k and up<szb[j]) up++;
                b1d[buck[i+1][l].second][j] += up-low;
            }
        }
    }
}

int main()
{
    //rf; wf;
    scan(n); scan(k); sqr=sqrt(n);
    rep(i, 0, n-1)
        scan(h[i]);

    process();
    cum1d();
    cum2d();

    scanf("%d", &q);
    while(q--)
    {
        int l, r;
        scan(l); scan(r);
        ll ans=0;

        int sqrl=l/sqr, sqrr=r/sqr, szl=0, szr=0; sqrl++;

        rep(i, 0, szb[sqrl]-1)
            if(buck[sqrl][i].second>=l and buck[sqrl][i].second<=r)
                lb[szl++]=buck[sqrl][i].first;
        rep(i, 0, szb[sqrr+1]-1)
            if(buck[sqrr+1][i].second>=l and buck[sqrr+1][i].second<=r)
                rb[szr++]=buck[sqrr+1][i].first;

        ans+=inonev(lb, szl);
        if(sqrr+1==sqrl) {printf("%lld\n", ans); continue;}
        ans+=inonev(rb, szr);

        ans += intwov(lb, szl, rb, szr);
        ans += b2d[sqrr][sqrr]-b2d[sqrr][sqrl]-b2d[sqrl][sqrr]+b2d[sqrl][sqrl];

        rep(i, l, sqr*sqrl-1)
            ans += b1d[i][sqrr]-b1d[i][sqrl];
        rep(i, sqr*sqrr, r)
            ans += b1d[i][sqrr]-b1d[i][sqrl];

        printf("%lld\n", ans);
    }
    return 0;
}
