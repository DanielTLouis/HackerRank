/*
In this problem you operate on two arrays of N integers. We will call them the 0th and the 1st
respectively.
Your goal is just to maintain them under the modification operations, such as:
    1 idlr: Reverse the subarray of the idth array, starting at the lth number, ending at the
    rth number, inclusively;
    2 idl_1r_1l_2r_2: Swap two consecutive fragments of the idth array, the first is from the
    lth_1 number to the rth_1, the second is from the lth_2 number to the rth_2;
    3 lr: Swap the piece that starts at the lth number and end at the rth one between the 0th
    and the 1st array;
    4 lr: We consider only the piece from the lth number to the rth one. The numbers in the
    0th array are X-coordinates of some set of points and the numbers in the 1st array are
    Y-coordinates of them. For the obtained set of points we would like to place such a circle
    on a plane that would contain all the points in it and would have the minimal radius. Find
    this minimal radius.
Input Format
    The first line of input contains two space separated integers N and M denoting the number
    of integers in arrays and the number of queries respectively.
    The second line contains N space separated integers: the initial elements of the 0th
    array.
    The third line contains N space separated integers: the initial elements of the 1st array.
    Then there are M lines containing queries in the format listed above.
Output Format
    For each type-4 query output the sought minimal radius with exactly two symbols after the
    decimal point precision.
Constraints
    1<=N,M<=10^5
    All the numbers in arrays are non-negative and don't exceed 10^6.
    The sum of R-L over the type-4 queries won't exceed 10^6.
    In the query of the type 2, 1<=l1<=r1<l2<=r2<=N.
    In the queries of the types 1, 3, 4, ; 1<=l<=r<=N;0<=id<2.
Sample Input
    10 10
    1 2 3 4 5 6 7 8 9 10
    1 2 3 4 5 6 7 8 9 10
    3 2 6
    1 0 9 9
    4 6 9
    2 0 2 7 9 9
    1 0 3 6
    2 1 2 3 4 5
    1 1 7 10
    2 1 8 8 9 10
    4 6 9
    2 0 2 2 4 6
Example Output
    2.12
    2.50
*/
#include <bits/stdc++.h>
#include <unistd.h>
#define SZ(x) ((int)(x).size())
#define REP(i,n) for ( int i=0; i<int(n); i++ )
#define REP1(i,a,b) for ( int i=(a); i<=int(b); i++ )
#define FOR(it,c) for ( __typeof((c).begin()) it=(c).begin(); it!=(c).end(); it++ )
#define MP make_pair
#define PB push_back
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
typedef vector<int> VI;

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
    scanf("%d",&head);
    RI(tail...);
}
// }}}

const int INF=0x7FFFFFFF;
const int N=400010;
const double eps=1e-6;

struct P { double x,y; } p[N],q[3];
double dis2( P a, P b ) { return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y); }
P operator -( P a, P b ) { return (P){a.x-b.x,a.y-b.y}; }
P operator +( P a, P b ) { return (P){a.x+b.x,a.y+b.y}; }
P operator /( P a, double b ) { return (P){a.x/b,a.y/b}; }
double abs2( P a ) { return a.x*a.x+a.y*a.y; }
double dot( P a, P b ) { return a.x*b.x+a.y*b.y; }
double X( P a, P b ) { return a.x*b.y-a.y*b.x; }
double X( P a, P b, P c ) { return X(b-a,c-a); }
struct C {
    P o; double r2;
    C() { o.x=o.y=r2=0; }
    C( P a ) { o=a; r2=0; }
    C( P a, P b ) { o=(a+b)/2; r2=dis2(o,a); }
    C( P a, P b, P c ) {
        double i,j,k,A=2*X(a,b,c)*X(a,b,c);
        i=abs2(b-c)*dot(a-b,a-c);
        j=abs2(a-c)*dot(b-a,b-c);
        k=abs2(a-b)*dot(c-a,c-b);
        o.x=(i*a.x+j*b.x+k*c.x)/A;
        o.y=(i*a.y+j*b.y+k*c.y)/A;
        r2=dis2(o,a);
    }
    bool cover( P a ) { return dis2(o,a)<=r2+eps; }
};
C MEC( int n, int m ) {
    C mec;
    if ( m==1 ) mec=C(q[0]);
    else if ( m==2 ) mec=C(q[0],q[1]);
    else if ( m==3 ) return C(q[0],q[1],q[2]);
    for ( int i=0; i<n; i++ )
        if ( !mec.cover(p[i]) ) {
            q[m]=p[i];
            mec=MEC(i,m+1);
        }
    return mec;
}

int my_rand() {
    static int seed;
    return seed=seed*1103515245+12345;
}
struct Treap {
    static Treap mem[N],*pmem;
    Treap *l,*r;
    int rnd,size,val;
    bool rev;
    Treap() {}
    Treap( int _val ):l(NULL),r(NULL),rnd(rand()),size(1),val(_val),rev(false) {}
} Treap::mem[N],*Treap::pmem=Treap::mem;
inline int size( Treap *t ) { return t?t->size:0; }
inline void push( Treap *t ) {
    if ( !t ) return;
    if ( t->rev ) {
        if ( t->l ) t->l->rev^=1;
        if ( t->r ) t->r->rev^=1;
        swap(t->l,t->r);
        t->rev=false;
    }
}
inline void pull( Treap *t ) {
    if ( !t ) return;
    t->size=size(t->l)+size(t->r)+1;
}
Treap* merge( Treap *a, Treap *b ) {
    if ( !a || !b ) return a?a:b;
    if ( a->rnd < b->rnd ) {
        push(a);
        a->r=merge(a->r,b);
        pull(a);
        return a;
    } else {
        push(b);
        b->l=merge(a,b->l);
        pull(b);
        return b;
    }
}
void split( Treap *t, int k, Treap *&a, Treap *&b ) {
    push(t);
    if ( !t ) a=b=NULL;
    else if ( k<=size(t->l) ) {
        b=t;
        split(t->l,k,a,b->l);
        pull(b);
    } else {
        a=t;
        split(t->r,k-size(t->l)-1,a->r,b);
        pull(a);
    }
}

void go( Treap *t, vector<int> &v ) {
    if ( !t ) return;
    push(t);
    go(t->l,v);
    v.PB(t->val);
    go(t->r,v);
}

Treap* input( int n ) {
    Treap *t=NULL;
    REP1(i,1,n) {
        int x;
        RI(x);
        t=merge(t,new (Treap::pmem++) Treap(x));
    }
    return t;
}

Treap *t[2];

int main() {
    srand(time(0)^getpid()^514514514);
    int n,m;
    RI(n,m);
    REP(i,2) t[i]=input(n);
    while ( m-- ) {
        int op;
        RI(op);
        if ( op==1 ) {
            int id,l,r;
            RI(id,l,r);
            Treap *tl,*tr;
            split(t[id],l-1,tl,t[id]);
            split(t[id],r-l+1,t[id],tr);
            t[id]->rev^=1;
            t[id]=merge(merge(tl,t[id]),tr);
        } else if ( op==2 ) {
            int id,l1,r1,l2,r2;
            RI(id,l1,r1,l2,r2);
            Treap *t1,*t2,*t3,*t4,*t5;
            split(t[id],l1-1,t1,t[id]);
            split(t[id],r1-l1+1,t2,t[id]);
            split(t[id],l2-r1-1,t3,t[id]);
            split(t[id],r2-l2+1,t4,t5);
            t[id]=merge(merge(merge(merge(t1,t4),t3),t2),t5);
        } else if ( op==3 ) {
            int l,r;
            RI(l,r);
            Treap *tl[2],*tm[2],*tr[2];
            REP(i,2) {
                split(t[i],l-1,tl[i],t[i]);
                split(t[i],r-l+1,tm[i],tr[i]);
            }
            t[0]=merge(merge(tl[0],tm[1]),tr[0]);
            t[1]=merge(merge(tl[1],tm[0]),tr[1]);
        } else if ( op==4 ) {
            int l,r;
            RI(l,r);
            vector<int> v[2];
            REP(i,2) {
                Treap *tl,*tr;
                split(t[i],l-1,tl,t[i]);
                split(t[i],r-l+1,t[i],tr);
                go(t[i],v[i]);
                t[i]=merge(merge(tl,t[i]),tr);
            }
            assert(v[0].size() == v[1].size());
            int vn=SZ(v[0]);
            REP(i,vn) {
                p[i].x=v[0][i];
                p[i].y=v[1][i];
            }
            random_shuffle(p,p+vn);
            C c=MEC(vn,0);
            double ans=sqrt(c.r2);
            printf("%.2f\n",ans);
        }
    }
    return 0;
}
