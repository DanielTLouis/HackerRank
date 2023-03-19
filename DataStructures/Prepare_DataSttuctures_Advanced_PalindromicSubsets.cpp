/*
Consider a lowercase English alphabetic letter character denoted by c. A shift operation on
some c turns it into the next letter in the alphabet. For example, and shift(a)=b, shift(e)=f,
shift(z)=a.
Given a zero-indexed string, s, of n lowercase letters, perform q queries on s where each query takes one of the following two forms:
    * 1 i j t: All letters in the inclusive range from i to j are shifted t times.
    * 2 i j: Consider all indices in the inclusive range from i to j. Find the number of
    non-empty subsets of characters, c1,c2,...,ck where i <= index of c1 < index of c2 < ... <
    index of ck <= j, such that characters c1,c2,c3,...,ck can be rearranged to form a
    palindrome. Then print this number modulo 10^9 +7 on a new line. Two palindromic subsets
    are considered to be different if their component characters came from different indices
    in the original string.
Note Two palindromic subsets are considered to be different if their component characters came
from different indices in the original string.
Input Format
    The first line contains two space-separated integers describing the respective values of n
    and q.
    The second line contains a string of n lowercase English alphabetic letters (i.e., a
    through z) denoting s.
    Each of the q subsequent lines describes a query in one of the two formats defined above.
Constraints
    1<=n<=10^5
    1<=q<=10^5
    0<=i<=j<n for each query.
    0<=t<10^9 for each query of type 1.
Subtasks
    For 20% of the maximum score:
        * n<=500
        * q<=500
    For another 30% of the maximum score:
        * All queries will be of type 2.
Output Format
    For each query of type 2 (i.e., 2 i j), print the number of non-empty subsets of
    characters satisfying the conditions given above, modulo 10^9 +7, on a new line.
Sample Input 0
    3 5
    aba
    2 0 2
    2 0 0
    2 1 2
    1 0 1 1
    2 0 2
Sample Output 0
    5
    1
    2
    3
Explanation 0
    We perform the following q=5 queries:
        1. 2 0 2: s=aba and we want to find the palindromic subsets of substring aba. There
        are five such subsets that form palindromic strings (a, b, a, aa, and aba), so we
        print the result of 5mod(10^9 +7)=5 on a new line
        2. 2 0 0: s=aba and we want to find the palindromic subsets of substring a. Because
        this substring only has one letter, we only have one subset forming a palindromic
        string (a). We then print the result of 1mod(10^9 +7)=1 on a new line.
        3. 2 1 2: s=aba and we want to find the palindromic subsets of substring ba. There are
        two such subsets that form palindromic strings (b and a), so we print the result of
        2mod(10^9 +7)=2 on a new line.
        4. 1 0 1 1: s=aba and we need to perform t=1 shift operations on each character from
        index i=0 to index j=1. After performing these shifts, s=bca.
        5. 2 0 2: s=bca and we want to find the palindromic subsets of substring bca. There
        are three valid subsets that form palindromic strings (b, c, and a), so we print the
        result of 3mod(10^9 +7)=3 on a new line.
*/

#include <bits/stdc++.h>

using namespace std;

const int MOD=1000000007;
int N, Q;
char S[100002];

struct node
{
    int lazy;
    int cnt[26];
} seg[262144], id;

node combine(node a, node b)
{
    node c;
    c.lazy=0;
    for(int i=0; i<26; i++)
        c.cnt[i]=a.cnt[(i+a.lazy)%26]+b.cnt[(i+b.lazy)%26];
    return c;
}

void apply(int idx, int v)
{
    seg[idx].lazy+=v;
}

void down(int idx)
{
    if(seg[idx].lazy)
    {
        apply(idx*2, seg[idx].lazy);
        apply(idx*2+1, seg[idx].lazy);
        node c;
        c.lazy=0;
        for(int i=0; i<26; i++)
            c.cnt[i]=seg[idx].cnt[(i+seg[idx].lazy)%26];
        seg[idx]=c;
    }
}

void build(int idx, int begin, int end)
{
    if(begin==end)
        seg[idx].cnt[S[begin]-'a']++;
    else
    {
        int mid=(begin+end)/2;
        build(idx*2, begin, mid);
        build(idx*2+1, mid+1, end);
        seg[idx]=combine(seg[idx*2], seg[idx*2+1]);
    }
}

void update(int idx, int begin, int end, int l, int r, int v)
{
    if(r<begin || end<l)
        return;
    if(l<=begin && end<=r)
        apply(idx, v);
    else
    {
        down(idx);
        int mid=(begin+end)/2;
        update(idx*2, begin, mid, l, r, v);
        update(idx*2+1, mid+1, end, l, r, v);
        seg[idx]=combine(seg[idx*2], seg[idx*2+1]);
    }
}

node query(int idx, int begin, int end, int l, int r)
{
    if(r<begin || end<l)
        return id;
    if(l<=begin && end<=r)
        return seg[idx];
    down(idx);
    int mid=(begin+end)/2;
    return combine(query(idx*2, begin, mid, l, r),
                   query(idx*2+1, mid+1, end, l, r));
}

int powmod(int a, int b)
{
    int ret=1;
    for(; b>0; b/=2)
    {
        if(b&1)
            ret=1LL*ret*a%MOD;
        a=1LL*a*a%MOD;
    }
    return ret;
}

int getans(node n)
{
    int e=0;
    for(int i=0; i<26; i++) if(n.cnt[i]>0)
        e+=n.cnt[i]-1;
    int f=1;
    for(int i=0; i<26; i++) if(n.cnt[i]>0)
        f++;
    return ((1LL*powmod(2, e)*f)%MOD-1+MOD)%MOD;
}

int main()
{
    scanf("%d%d", &N, &Q);
    scanf("%s", S+1);
    build(1, 1, N);
    while(Q--)
    {
        int t;
        scanf("%d", &t);
        if(t==1)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            update(1, 1, N, a+1, b+1, (26-(c%26))%26);
        }
        else
        {
            int a, b;
            scanf("%d%d", &a, &b);
            printf("%d\n", getans(query(1, 1, N, a+1, b+1)));
        }
    }
    return 0;
}
