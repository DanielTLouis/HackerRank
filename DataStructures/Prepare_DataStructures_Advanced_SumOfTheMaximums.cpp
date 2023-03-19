/*
Alexey is playing with an array, A, of n integers. His friend, Ivan, asks him to calculate the
sum of the maximum values for all subsegments of A. More formally, he wants Alexey to find
F(A)=sumation(sumation(max A[x])from(l=1 to n))from(l=1 to n).
Alexey solved Ivan's challenge faster than expected, so Ivan decides to add another layer of
difficulty by having Alexey answer m queries. The ith query contains subsegment [L_i,R_i], and
he must calculate the sum of maximum values on all subsegments inside subsegment [L_i,R_i].
More formally, for each query , Alexey must calculate the following function:
    F(A,L_i,R_i)=sumation(sumation(Max A[x])from(l=L_i to R_i))from(l=L_i to R_i).
Can you help Alexey solve this problem?
Input Format
    The first line contains 2 space-separated positive integers, n (the length of array A) and
    m (number of queries), respectively.
    The second line contains n space-separated integers, a_0,a_1,...,a_j describing each
    element (where 0<=j<n) in array A.
    Each of the m subsequent lines contains  space-separated positive integers describing the
    respective values for L_i and R_i in query i (where 0<=i,m).
Constraints
    1<=n,m<=135000
    -10^9<=a_i<=10^9
    1<=L_i<=R_i<=n
Output Format
    For each query i (where 0<=i<m), print its answer on a new line.
Sample Input
    3 6
    1 3 2
    1 1
    1 2
    1 3
    2 2
    2 3
    3 3
Sample Output
    1
    7
    15
    3
    8
    2
Explanation
    The answer for the second query is shown below:
        F(A,1,2)=
    The answer for the third query is shown below:
*/
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int>   II;
typedef vector< II >      VII;
typedef vector<int>     VI;
typedef vector< VI >    VVI;
typedef long long int   LL;

#define PB push_back
#define MP make_pair
#define F first
#define S second
#define SZ(a) (int)(a.size())
#define ALL(a) a.begin(),a.end()
#define SET(a,b) memset(a,b,sizeof(a))

#define si(n) scanf("%d",&n)
#define dout(n) printf("%d\n",n)
#define sll(n) scanf("%lld",&n)
#define lldout(n) printf("%lld\n",n)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)

#define TRACE

#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif

//FILE *fin = freopen("in","r",stdin);
//FILE *fout = freopen("out","w",stdout);

const int N = int(1.35*1e5)+10;
const int SQRT = 400;
LL A[N],dp[N],dp2[N],PS[N],ans[N],dp3[N];
int st[N],top,arr[N],len,st2[N],top2;
VI B[N];
struct query{
  int l,r;
}Q[N];
bool cmp(int i,int j){
  return Q[i].r < Q[j].r;
}
LL get2(int ll,int rr,int n,int L,int len){
  LL ret = 0;assert(len>0);LL mx = -int(1e9);
  for(int i=rr;i>=ll;i--){
    mx = max(mx,A[i]);
    if(mx >= A[arr[len]]){ret += mx*(n + 1 - L);continue;}
    int l = 1, h = len, ans = 0;
    while(l<=h){
      int m = (l+h)/2;
      if(A[arr[m]] >= mx){ans = m;h = m-1;}
      else l = m+1;
    }
    ret += (mx*(arr[ans]-L));
    ret += PS[len]-PS[ans-1];
  }
  return ret;
}
LL get(int l,int r){
  LL ret = 0;top2=0;
  int R = l;
  while(R <= r){
    while(top2 && A[st2[top2]] <= A[R])top2--;
    int lpos = (top2?st2[top2]:l-1);
    dp3[R] = (R -lpos)*A[R] + (top2?dp3[lpos]:0);
    st2[++top2]=R;
    ret+=dp3[R];
    R++;
  }
  return ret;
}
int main()
{
  int n,q;
  si(n);si(q);
  for(int i=1;i<=n;i++)sll(A[i]);
  for(int i=1;i<=q;i++){
    si(Q[i].l);si(Q[i].r);
    B[Q[i].l/SQRT].PB(i);
  }
  for(int i=0;i<N;i++){
    sort(ALL(B[i]),cmp);
    int L = (i+1)*SQRT, R = L;top = len = 0;
    LL add = 0;
    for(int j=0;j<SZ(B[i]);j++){
      int idx = B[i][j];
      int l = Q[idx].l,r = Q[idx].r;
      ans[idx] = get(l,min(r,L-1));
      if(r<L)continue;
      while(R <= r){
        while(top && A[st[top]] <= A[R])top--;
        int lpos = (top?st[top]:L-1);
        dp2[R] = (R -lpos)*A[R] + (top?dp2[lpos]:0);
        st[++top] = R;
        if(!len || A[R]>A[arr[len]]){
          if(len){
            dp[arr[len]] = (R - arr[len])*A[arr[len]];
            PS[len] = PS[len-1] + dp[arr[len]];
          }
          arr[++len]=R;
          dp[R] = (r - R + 1)*A[R];
          PS[len] = PS[len-1] + dp[R];
        }
        add += dp2[R];R++;
      }
      dp[arr[len]] = (r - arr[len] + 1)* A[arr[len]];
      PS[len] = PS[len-1] + dp[arr[len]];
      ans[idx] += add;
      ans[idx] += get2(l,L-1,r,L,len);
    }
  }
  for(int i=1;i<=q;i++)
    lldout(ans[i]);
  return 0;
}
