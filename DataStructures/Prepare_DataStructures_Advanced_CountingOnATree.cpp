/*
Taylor loves trees, and this new challenge has him stumped!
Consider a tree, t, consisting of n nodes. Each node is numbered from 1 to n, and each node i
has an integer, c_i, attached to it.
A query on tree t takes the form w x y z. To process a query, you must print the count of
ordered pairs of integers (i,j) such that the following four conditions are all satisfied:
        * i != j
        * i isAnElementOf the path from node w to node z.
        * j isAnElementOf path from node y to node z.
        * c_i = c_j
Givent  and q queries, process each query in order, printing the pair count for each query on
a new line.
Input Format
    The first line contains two space-separated integers describing the respective values of
    n (the number of nodes) and q (the number of queries).
    The second line contains  space-separated integers describing the respective values of
    each node (i.e., c_1,c_2,...,c_n).
    Each of the n-1 subsequent lines contains two space-separated integers, u and v, defining
    a bidirectional edge between nodes u and v.
    Each of the q subsequent lines contains a w x y z query, defined above.
Constraints
    1<=n<=10^5
    1<=q<=50000
    1<=c_i<=10^9
    1<=u,v,w,x,y,z<=n
    Scoring for this problem is Binary, that means you have to pass all the test cases to get
    a positive score.
Output Format
    For each query, print the count of ordered pairs of integers satisfying the four given
    conditions on a new line.
Sample Input
    10 5
    10 2 3 5 10 5 3 6 2 1
    1 2
    1 3
    3 4
    3 5
    3 6
    4 7
    5 8
    7 9
    2 10
    8 5 2 10
    3 8 4 9
    1 9 5 9
    4 6 4 6
    5 8 5 8
Sample Output
    0
    1
    3
    2
    0
Explanation
    We perform q=5 queries on the following tree:
        image
    1. Find the number of valid ordered pairs where i is in the path from node 8 to node 5 and
    j is in the path from node 2 to node 10. No such pair exists, so we print 0.
    2. Find the number of valid ordered pairs where i is in the path from node 3 to node 8 and
    j is in the path from node 4 to node 9. One such pair, (3,7), exists, so we print 1.
    3. Find the number of valid ordered pairs where i is in the path from node 1 to node 9 and
    j is in the path from node 5 to node 9. Three such pairs, (1,5), (3,7), and (7,3) exist,
    so we print 3.
    4. Find the number of valid ordered pairs where i is in the path from node 4 to node 6 and
    j is in the path from node 4 to node 6. Two such pairs, (4,6) and (6,4), exist, so we
    print 2.
    5. Find the number of valid ordered pairs where i is in the path from node 5 to node 8 and
    j is in the path from node 5 to node 8. No such pair exists, so we print 0.
*/

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <cassert>

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;

#define SIZE(x) (int((x).size()))
#define rep(i,l,r) for (int i=(l); i<=(r); i++)
#define repd(i,r,l) for (int i=(r); i>=(l); i--)
#define rept(i,c) for (__typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)

#ifndef ONLINE_JUDGE
#define debug(x) { cerr<<#x<<" = "<<(x)<<endl; }
#else
#define debug(x) {}
#endif

#define maxn 100010
#define LIM 100

int ta[maxn];

void ta_modify(int x, int y)
{
    while (x<maxn) ta[x]+=y, x+=x&-x;
}

int ta_query(int x)
{
    int ret=0;
    while (x) ret+=ta[x], x-=x&-x;
    return ret;
}

void ds_modify(int l, int r, int c)
{
    ta_modify(l,c);
    ta_modify(r+1,-c);
}

int ds_query(int v)
{
    return ta_query(v);
}

int dfsN;
int dfsLeft[maxn], dfsRight[maxn];
int lg2[maxn], p[maxn][17], depth[maxn];
vector<int> e[maxn];

void dfs(int cur, int pre, int dep)
{
    dfsN++; dfsLeft[cur]=dfsN;
    depth[cur]=dep;
    p[cur][0]=pre;
    rep(i,1,lg2[dep]) p[cur][i]=p[p[cur][i-1]][i-1];
    rept(it,e[cur]) if (*it!=pre) dfs(*it,cur,dep+1);
    dfsRight[cur]=dfsN;
}

int movedep(int x, int y)
{
    if (y<0) return 0;
    while (y) x=p[x][lg2[y&-y]], y-=y&-y;
    return x;
}

int lca(int x, int y)
{
    if (depth[x]<depth[y]) swap(x,y);
    x=movedep(x,depth[x]-depth[y]);
    repd(i,16,0)
        if (p[x][i]!=p[y][i])
        {
            x=p[x][i]; y=p[y][i];
        }
    if (x==y) return x;
    return p[x][0];
}

int get_dist(int x, int y)
{
    int z=lca(x,y);
    return depth[x]+depth[y]-2*depth[z]+1;
}

int all, ti[5][2];

void check_intersect(int p1, int p2, int q1, int q2)
{
    if (depth[p2]>depth[q2])
    {
        swap(p1,q1); swap(p2,q2);
    }
    if (depth[p1]<depth[q2]) return;
    if (lca(p1,q2)!=q2 || lca(q2,p2)!=p2) return;
    int z=lca(p1,q1);
    rep(i,1,all) if (ti[i][0]==z && ti[i][1]==q2) return;
    rep(i,1,all) if (ti[i][1]==z && ti[i][0]==q2) return;
    //if (z==q2) rep(i,1,all) if (ti[i][0]==z || ti[i][1]==z) return;
    all++; ti[all][0]=z; ti[all][1]=q2;
}

struct tasktype
{
    int x, y, c;
    tasktype() {}
    tasktype(int x, int y, int c): x(x), y(y), c(c) {}
};

vector<tasktype> eventAddList[maxn], eventQueryList[maxn];

void addQueryEvent(int i, int p1, int q1, int c)
{
    p1=dfsLeft[p1]; q1=dfsLeft[q1];
    eventQueryList[p1].push_back(tasktype(q1,i,c));
}

void addContributionEvent(int p1, int p2, int q1, int q2)
{
    eventAddList[p1].push_back(tasktype(q1,q2,1));
    eventAddList[p2+1].push_back(tasktype(q1,q2,-1));
}

void add_task(int i, int p1, int p2, int q1, int q2)
{
    if (!p1 || !p2 || !q1 || !q2) return;
    addQueryEvent(i,p1,q1,1);
    if (p[q2][0]) addQueryEvent(i,p1,p[q2][0],-1);
    if (p[p2][0]) addQueryEvent(i,p[p2][0],q1,-1);
    if (p[p2][0] && p[q2][0]) addQueryEvent(i,p[p2][0],p[q2][0],1);
}

map<int, vector<int> > clist;
int color[maxn];
int q[maxn][6];
int ans[maxn];

void lemon()
{
    lg2[1]=0; rep(i,2,maxn-1) lg2[i]=lg2[i>>1]+1;
    int n,qa; scanf("%d%d",&n,&qa);
    rep(i,1,n)
    {
        scanf("%d",&color[i]);
        clist[color[i]].push_back(i);
    }
    rep(i,1,n-1)
    {
        int x,y; scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    rep(i,1,qa)
    {
        scanf("%d%d%d%d",&q[i][0],&q[i][1],&q[i][2],&q[i][3]);
    }
    dfsN=0;
    dfs(1,0,0);
    rep(i,1,qa) ans[i]=0;
    rep(i,1,qa)
    {
        all=0;
        int z1=lca(q[i][0],q[i][1]);
        int z2=lca(q[i][2],q[i][3]);

        q[i][4]=z1; q[i][5]=z2;

        check_intersect(q[i][0],z1,q[i][2],z2);
        check_intersect(q[i][0],z1,q[i][3],z2);
        check_intersect(q[i][1],z1,q[i][2],z2);
        check_intersect(q[i][1],z1,q[i][3],z2);

        int t1=movedep(q[i][1],depth[q[i][1]]-depth[z1]-1);
        int t2=movedep(q[i][3],depth[q[i][3]]-depth[z2]-1);

        add_task(i,q[i][0],z1,q[i][2],z2);
        add_task(i,q[i][0],z1,q[i][3],t2);
        add_task(i,q[i][1],t1,q[i][2],z2);
        add_task(i,q[i][1],t1,q[i][3],t2);

        if (all>0)
        {
            rep(k,1,all)
                ans[i]-=get_dist(ti[k][0],ti[k][1]);

            ans[i]+=all-1;
        }
    }

    rept(it,clist)
    {
        int cl=it->first;
        if (it->second.size()<=LIM)
        {
            int s=it->second.size();
            rep(i,0,s-1)
                rep(j,0,s-1)
                {
                    int i1=it->second[i], j1=it->second[j];
                    addContributionEvent(dfsLeft[i1], dfsRight[i1], dfsLeft[j1], dfsRight[j1]);
                }
        }
        else
        {
            rept(it2,it->second)
                ds_modify(dfsLeft[*it2],dfsRight[*it2],1);

            rep(i,1,qa)
            {
                int x1=ds_query(dfsLeft[q[i][0]])+ds_query(dfsLeft[q[i][1]])-2*ds_query(dfsLeft[q[i][4]]);
                if (color[q[i][4]]==cl) x1++;
                //printf("%d: %d %d %d\n",cl,q[i][0],q[i][1],x1);
                int x2=ds_query(dfsLeft[q[i][2]])+ds_query(dfsLeft[q[i][3]])-2*ds_query(dfsLeft[q[i][5]]);
                if (color[q[i][5]]==cl) x2++;
                //printf("%d: %d %d %d\n",cl,q[i][2],q[i][3],x2);
                ans[i]+=x1*x2;
            }

            rept(it2,it->second)
                ds_modify(dfsLeft[*it2],dfsRight[*it2],-1);

        }
    }

    rep(i,1,n)
    {
        rept(it,eventAddList[i]) ds_modify(it->x,it->y,it->c);
        rept(it,eventQueryList[i]) ans[it->y]+=it->c*ds_query(it->x);
    }

    rep(i,1,qa) printf("%d\n",ans[i]);
}

int main()
{
    ios::sync_with_stdio(true);
    #ifndef ONLINE_JUDGE
        //freopen("8.in","r",stdin);
    #endif
    lemon();
    return 0;
}
