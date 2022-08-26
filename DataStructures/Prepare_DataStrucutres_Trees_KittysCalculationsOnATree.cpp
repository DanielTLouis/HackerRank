/*
Kitty has a tree, T, consisting of n nodes where each node is uniquely labeled from 1
to n. Her friend Alex gave her q sets, where each set contains k distinct nodes. Kitty
needs to calculate the following expression on each set:
    (sumation(u*v*dist(u,v)))mod(10^9 +7)
where:
    {u,v} denotes an unordered pair of nodes belonging to the set.
    dist(u,v) denotes the number of edges on the unique (shortest) path between nodes
    u and v.
Given T and q sets of k distinct nodes, calculate the expression for each set. For
each set of nodes, print the value of the expression modulo 10^9 +7 on a new line.
Example
    edges=[[1,2],[1,3],[1,4],[3,5],[3,6],[3,7]]
    queries=[4,5,7]
    The graph looks like this:
        image
    There are three pairs that can be created from the query set: [4,5],[4,7],[5,7]. The distance from 4 to 5 is 3, from 4 to 7 is 3, and from 5 to 7 is 2.
    Now do the summation:
        (4*5*dist(4,5)+4*7*dist(4,7)+5*7*dist(5,7)) mod (10^9 + 7)
        = (4*5*3+4*7*3+5*7*2) mod (10^9 +7)
        = 214
Input Format
    The first line contains two space-separated integers, the respective values of
    (the number of nodes in tree T) and q (the number of nodes in the query set).
    Each of the n-1 subsequent lines contains two space-separated integers, a and b,
    that describe an undirected edge between nodes a and b.
    The  subsequent lines define each set over two lines in the following format:
        1.The first line contains an integer, k, the size of the set.
        2.The second line contains k space-separated integers, the set's elements.
Constraints
    1<=n<=2*10^5
    1<=a,b<=n
    1<=q<=10^5
    1<=k_i<=10^5
    The sum of k_i over all q does not exceed 2*10^5.
    All elements in each set are distinct.
Subtasks
    1<=n<=2000 for 24% of the maximum score.
    1<=n<=5*10^4for 45% of the maximum score.
    1<=n<=2*10^5for 100% of the maximum score.
Output Format
    Print  lines of output where each line i contains the expression for the ith query,
    modulo 10^9 +7.
Sample Input 0
    7 3
    1 2
    1 3
    1 4
    3 5
    3 6
    3 7
    2
    2 4
    1
    5
    3
    2 4 5
Sample Output 0
    16
    0
    106
Explanation 0
    Tree T looks like this:
        image
    We perform the following calculations for q=3 sets:
        Set 0: Given set {2,4}, the only pair we can form is (u,v)=(2,4), where
        dist(2,4)=2. We then calculate the following answer and print it on a new line:
            (2*4*dist(2,4))mod(10^9 +7) = (2*4*2)mod(10^9 +7) = 16
        Set 1: Given set {5}, we cannot form any pairs because we don't have at least
        two elements. Thus, we print 0 on a new line.
        Set 2: Given set {2,4,5}, we can form the pairs (2,4), (2,5), and (4,5). We
        then calculate the following answer and print it on a new line:
            (2*4*dist(2,4)+2*5*dist(2,5)+4*5*dist(4,5)) mod (10^9 + 7)
            = (2*4*2+2*5*3+4*5*3) mod (10^9 +7)
            = 106
*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pii;
const int MAX_N = 2e5 + 6;
const int MAX_P = 19;
const LL mod = 1e9 + 7;

vector<int> edg[MAX_N];
int dis[MAX_P][MAX_N];
bool visit[MAX_N];

struct Cen {
    int par;
    int depth;
    pii val_v_av;  //first --> val, second --> minus
    pii val_v;
} cen[MAX_N];

vector<int> v;
int sz[MAX_N];
int mx[MAX_N];

void dfs2(int id) {
    v.push_back(id);
    visit[id]=1;
    sz[id]=1;
    mx[id]=0;
    for (int i:edg[id]) {
        if (!visit[i]) {
            dfs2(i);
            sz[id] += sz[i];
        }
    }
}

#define SZ(x) ((int)(x).size())

int get_cen(int id) {
    v.clear();
    dfs2(id);
    int tot=SZ(v);
    int cen=-1;
    for (int i:v) {
        if (max(mx[i],tot-sz[i]) <= tot/2) {
            cen=i;
        }
        visit[i]=false;
    }
    return cen;
}

void dfs3(int id,int par,int cen_depth,int dist)  {
    dis[cen_depth][id] = dist;
    for (int i:edg[id]) {
        if (!visit[i] && i!=par) {
            dfs3(i,id,cen_depth,dist+1);
        }
    }
}

void dfs(int id,int cen_par,int cen_depth) {
    int ccen=get_cen(id);
    dfs3(ccen,ccen,cen_depth,0);
    cen[ccen]={cen_par,cen_depth,{0,0},{0,0}};
    visit[ccen]=1;
    for (int i:edg[ccen]) {
        if (!visit[i]) dfs(i,ccen,cen_depth+1);
    }
}

pii operator+(const pii &p1,const pii &p2) {
    return make_pair(p1.first+p2.first,p1.second+p2.second);
}

pii operator-(const pii &p1,const pii &p2) {
    return make_pair(p1.first-p2.first,p1.second-p2.second);
}

pii operator+=(pii &p1,const pii &p2) {
    p1 = p1 + p2;
    return p1;
}

pii operator-=(pii &p1,const pii &p2) {
    p1 = p1 - p2;
    return p1;
}

void Pure(pii &p) {
    p.first = (p.first%mod + mod) % mod;
    p.second = (p.second%mod + mod) % mod;
}

void addd(LL x) {
    LL p=x;
    while (p!=-1) {
        cen[p].val_v += {x,0};
        cen[p].val_v_av += {x*dis[cen[p].depth][x],0};
        if (cen[p].par != -1) {
            int par=cen[p].par;
            cen[p].val_v -= {0,x};
            cen[p].val_v_av -= {0,x*dis[cen[par].depth][x]};
        }
        Pure(cen[p].val_v);
        Pure(cen[p].val_v_av);
        p=cen[p].par;
    }
}

void dell(LL x) {
    LL p=x;
    while (p!=-1) {
        cen[p].val_v -= {x,0};
        cen[p].val_v_av -= {x*dis[cen[p].depth][x],0};
        if (cen[p].par != -1) {
            int par=cen[p].par;
            cen[p].val_v += {0,x};
            cen[p].val_v_av += {0,x*dis[cen[par].depth][x]};
        }
        Pure(cen[p].val_v);
        Pure(cen[p].val_v_av);
        p=cen[p].par;
    }
}

LL query(LL x) {
    LL ret=0;
    LL v=0;
    LL v_av=0;
    int p=x;
    while (p!=-1) {
        v += cen[p].val_v.first;
        v_av += cen[p].val_v_av.first;
        ret += x*v_av;
        ret %= mod;
        ret += x*dis[cen[p].depth][x]*v;
        ret %= mod;
        v = cen[p].val_v.second;
        v_av = cen[p].val_v_av.second;
        p=cen[p].par;
    }
    return ret;
}

LL pow(LL a,LL n,LL mod) {
    if (n==0) return 1;
    else if (n==1) return a;
    LL ret=pow(a,n/2,mod);
    ret*=ret;
    ret%=mod;
    if (n&1) {
        ret*=a;
        ret%=mod;
    }
    return ret;
}

int main () {
    int n,q;
    scanf("%d %d",&n,&q);
    for (int i=1;n-1>=i;i++) {
        int a,b;
        scanf("%d %d",&a,&b);
        edg[a].push_back(b);
        edg[b].push_back(a);
    }
    dfs(1,-1,0);
    while (q--) {
        int k;
        scanf("%d",&k);
        vector<int> v;
        while (k--) {
            int x;
            scanf("%d",&x);
            v.push_back(x);
        }
        for (int i:v) addd(i);
        LL ans=0;
        for (int i:v) {
            ans += query(i);
            ans%=mod;
        }
        for (int i:v) dell(i);
        printf("%lld\n",(ans*pow(2,mod-2,mod) + mod)%mod);
    }
}
