/*
Let F(a,d) denote an arithmetic progression (AP) with first term a and common difference d,
i.e. F(a,d) denotes an infinite AP=>a,a+d,a+2d,a+3d,.... You are given n APs => F(a1,d1),
F(a2,d2),F(a3,d3),...,F(an,dn). Let G(a1,a2,...,an,d1,d2,...,dn) denote the sequence obtained
by multiplying these APs.
Multiplication of two sequences is defined as follows. Let the terms of the first sequence be
A1,A2,...,Am, and terms of the second sequence be B1,B2,...,Bm. The sequence obtained by
multiplying these two sequences is
    A1XB1,A2XB2,...,AmXBm
If A1,A2,...,Am are the terms of a sequence, then the terms of the first difference of this
sequence are given by A'1,A'2,...,A'm calculated as A2-A1,A3-A2,...,Am-A(m-1) respectively.
Similarly, the second difference is given by A'2-A'1,A'3-A'2,...,A'm-A'(m-1), and so on.
We say that the kth difference of a sequence is a constant if all the terms of the kth
difference are equal.
Let F'(a,d,q) be a sequence defined as =>a^p, (a+d)^p, (a+2d)^p,...
Similarly, G'(a1,a2,...,an,d1,d2,...,dn,p1,p2,...,pn) is defined as => product of F'(a1,d1,p1),
F'(a1,d2,p2),...F(a2,d2,p2),...,F'(an,dn,pn).
Task:
    Can you find the smallest k for which the kth difference of the sequence G' is a constant?
    You are also required to find this constant value.
    You will be given many operations. Each operation is of one of the two forms:
    1) 0 i j => 0 indicates a query (1<=i<=j<=n). You are required to find the smallest k for
    which the kth difference of G'(a_i,a_(i+1),...,a_j,d_i,d_(i+1),...,d_j,p_i,p_(i+1),...,p_j)
    is a constant. You should also output this constant value.
    2) 1 i j v => 1 indicates an update (1<=i<=j<=n). For all i<=k<=j, we update pk=pk+v.
Input Format
    The first line of input contains a single integer n, denoting the number of APs.
    Each of the next  lines consists of three integers  a_i,d_i,p_i(1<=i<=n).
    The next line consists of a single integer q, denoting the number of operations. Each of
    the next q lines consist of one of the two operations mentioned above.
Output Format
    For each query, output a single line containing two space-separated integers K and V. K is
    the smallest value for which the Kth difference of the required sequence is a constant.
    is the value of this constant. Since V might be large, output the value of V modulo
    1000003.
    Note: K will always be such that it fits into a signed 64-bit integer. All indices for
    query and update are 1-based. Do not take modulo 1000003 for K.
Constraints
    1<=n<=10^5
    1<=a_i,d_i,p_i<=10^4
    1<=q<=10^5
    For updates of the form 1 i j v, 1<=v<=10^4
Sample Input
    2
    1 2 1
    5 3 1
    3
    0 1 2
    1 1 1 1
    0 1 1
Sample Output
    2 12
    2 8
Explanation
    The first sequence given in the input is => 1,3,5,7,9,...
    The second sequence given in the input is => 5,8,11,14,17,...
    For the first query operation, we have to consider the product of these two sequences:
    =>  1 X 5, 3 X 8, 5 X 11, 7 X 14, 9 X 17, ...
    =>  5,24,55,98,153,...
    First difference is =>  19,31,43,55,...
    Second difference is => 12,12,12,... This is a constant and hence the output is 2 12.
    After the update operation 1 1 1 1, the first sequence becomes =>  1^2,3^2,5^2,7^2,9^2,...
    i.e =>  1,9,25,49,81,...
    For the second query, we consider only the first sequence =>  1,9,25,49,81,...
    First difference is =>  8,16,24,32,...
    Second difference is => 8,8,8,.... This is a constant and hence the output is 2 8
*/
#include <cstdio>
#include <iostream>
using std::swap;
using std::cout;
using std::endl;

typedef long long LL;
const LL Mod=1000003;
const int N=100001;
const LL INF=1LL<<62;

LL f[Mod+10];


LL power(LL base, LL k)
{
    LL res=1;
    while(k){
        if(k&1) res=(res*base)%Mod;
        base=(base*base)%Mod;
        k>>=1;
    }
    return res;
}

struct Node{
    int l,r;//sum;
    LL K;
    LL sk;
    LL V;
    LL V2;
    LL s;
    Node *lc,*rc;
    LL getK()
    {
        return K+sk*(r-l+1LL);
    }

    LL getV2()
    {
        return (power(V,s)*V2)%Mod;
        //return power(V,s);
    }
};

Node buf[200010];
Node* root;
int pt=0;


Node*  New()
{
    buf[pt].lc=buf[pt].rc=NULL;
    buf[pt].l =buf[pt].r =-INF;
    buf[pt].K=-1;
    buf[pt].V=-1;
    buf[pt].s=-1;
    return buf+pt++;
}

void build(Node* root, int l,int r)
{
    root->l=l;
    root->r=r;
    root->K=0;
    root->V=1;
    root->V2=1;
    root->s=0;
    root->sk=0;

    if(l==r)return;

    root->lc=New();
    root->rc=New();

    int mid=(l+r)/2;
    build(root->lc,l,mid);
    build(root->rc,mid+1,r);
}

void fresh(Node* root)
{
    root->K = root->lc->getK() + root->rc->getK();
    root->V = (root->lc->V*root->rc->V )%Mod;
    root->V2 = (root->lc->getV2()*root->rc->getV2())%Mod;
}

LL queryK(Node* root,int l, int r)
{
    if(root->l==l && root->r==r){
        return root->getK();
    }
    int mid = (root->l+root->r)/2;
    if(l>mid){
        LL res=queryK(root->rc,l,r);
        return res+root->sk*(r-l+1LL);
    }
    else if(r<=mid){
        LL res=queryK(root->lc,l,r);
        return res+root->sk*(r-l+1LL);
    }
    else{
        LL a = queryK(root->lc,l,mid);
        LL b = queryK(root->rc,mid+1,r);
        return a+b+root->sk*(r-l+1LL);
    }
    return -INF;
}

LL queryV(Node* root,int l, int r, int ac)
{
    //printf("root->l=%d root->r=%d root->s=%I64d root->v=%I64d root->k=%I64d\n",
    //root->l,root->r,root->s,root->V,root->K);

    if(root->l==l && root->r==r){
        //return power(root->V,ac+root->s);
        LL res = root->getV2();
        return (res*power(root->V,ac))%Mod;
    }
    int mid = (root->l+root->r)/2;
    if(l>mid){
        //LL res=queryV(root->rc,l,r);
        //return power(res,root->s+1);
        //return (res*root->getV())%Mod;

        return queryV(root->rc,l,r,ac+root->s);
    }
    else if(r<=mid){
        //LL res=queryV(root->lc,l,r);
        //return power(res,root->s+1);
        //return (res*root->getV())%Mod;

        return queryV(root->lc,l,r,ac+root->s);
    }
    else{
        LL a = queryV(root->lc,l,mid,ac+root->s);
        LL b = queryV(root->rc,mid+1,r,ac+root->s);
        LL res = (a*b)%Mod;
        //return power((a*b)%Mod,root->s+1);
        //return (res*root->getV())%Mod;

        return res;
    }
    return -INF;
}


void add( Node* root, int l, int r, int delta)
{
    //printf("root->l=%d root->r=%d l=%d r=%d val=%d\n",root->l,root->r,l,r,val);

    if(root->l==l && root->r==r){
        root->s += delta;
        root->sk += delta;
        return;
    }

    int mid = (root->l+root->r)/2;
    if(l>mid){
        add(root->rc,l,r,delta);
    }
    else if(r<=mid){
        add(root->lc,l,r,delta);
    }
    else{
        add(root->lc,l,mid,delta);
        add(root->rc,mid+1,r,delta);
    }
    fresh(root);
}

void update(Node* root,int l,int r,int d,int k)
{
    //printf("update, l=%d r=%d val=%d\n",root->l,root->r,val);
    if(l!=r){
        puts("currently only update single element");
    }

    if(root->l==l && root->r==r){
        //printf("index=%d is updated, val=%d\n",l,val);
        root->V=d;
        root->K=k;
        root->s=k;
        root->sk=0;
        return;
    }

    int mid = (root->l+root->r)/2;

    if(l>mid){
        //puts("should not execute");
        update(root->rc,l,r,d,k);
    }
    else if(r<=mid){
        update(root->lc,l,r,d,k);
    }
    else{
        //puts("should not execute");
        //add(root->lc,l,mid,val);
        update(root->rc,mid+1,r,d,k);
    }

    fresh(root);
}


void output(Node* p, int l, int r)
{
    if(p->l==l && p->r==r){
        if(l==r){
            printf("index=%d K=%I64d V=%I64d\n",l,queryK(root,l,l),queryV(root,l,l,0));
        }
        else{
            output(p->lc,l,(l+r)/2);
            output(p->rc, (l+r)/2+1, r);
        }
        return;
    }
    int mid=(p->l+p->r)/2;
    if(l>mid){
        output(p->rc,l,r);
    }
    else if(r<=mid){
        output(p->lc,l,r);
    }
    else{
        output(p->lc,l,mid);
        output(p->rc,mid+1,r);
    }
}

void Init()
{
    root=New();
    build(root,1,N);
    f[0]=1;
    for(int i=1;i<Mod;++i)
        f[i]=(i*f[i-1])%Mod;
}

int main()
{
    Init();
    /*
    output(root,1,10);
    update(root,2,2,0);
    add(root,3,N,2);
    puts("add(root,3,N,2)");
    output(root,1,10);

    update(root,1,1,0);
    add(root,2,N,1);

    puts("add(root,2,N,1)");
    output(root,1,10);
    */
    //return 0;
    char cmd[10];

    int n,q;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int a,d,p;
        scanf("%d%d%d",&a,&d,&p);
        update(root,i,i,d,p);
    }

    scanf("%d",&q);
    while(q--){
        int c,a,b,delta;
        scanf("%d",&c);

        if(!c){
            scanf("%d%d",&a,&b);
            LL r1 = queryK(root,a,b);
            LL r2 = queryV(root,a,b,0);
            //printf("K=%I64d V=%I64d\n",r1,r2);
            r2 = r1<Mod ? (f[r1]*r2)%Mod : 0;

            cout<<r1<<" "<<r2<<endl;
        }
        else{
            scanf("%d%d%d",&a,&b,&delta);
            add(root,a,b,delta);
        }

        //output(root,1,10);
    }


    return 0;
}
