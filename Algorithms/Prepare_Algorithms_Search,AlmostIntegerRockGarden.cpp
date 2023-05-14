/*
Victor is building a Japanese rock garden in his 24X24 square courtyard. He overlaid the
courtyard with a Cartesian coordinate system so that any point(x,y)  in the courtyard has
coordinates x isAnElementOf([-12,12]) and y isAnElementOf([-12,12]). Victor wants to place 12
 stones in the garden according to the following rules:
    * The center of each stone is located at some point (x,y), where x and y are integers
    isAnElementOf([-12,12]).
    * The coordinates of all twelve stones are pairwise distinct.
    * The Euclidean distance from the center of any stone to the origin is not an integer.
    * The sum of Euclidean distances between all twelve points and the origin is an almost
    integer, meaning the absolute difference between this sum and an integer must be <=10^-12.
Given the values of x and y for the first stone Victor placed in the garden, place the
remaining 11 stones according to the requirements above. For each stone you place, print two
space-separated integers on a new line describing the respective x and y coordinates of the
stone's location.
Input Format
    Two space-separated integers describing the respective values of x and y for the first
     stone's location.
Constraints
    * -12<=x,y<=12
Output Format
    Print 11 lines, where each line contains two space-separated integers describing the
    respective values of x and y for a stone's location.
Sample Input 0
    7 11
Sample Output 0
    1 1 1
    -2 12
    5 4
    12 -3
    10 3
    9 6
    -12 -7
    1 11
    -6 -6
    12 -4
    4 12
Explanation 0
    The diagram below depicts the placement of each stone and maps its distance to the origin
    (note that red denotes the first stone placed by Victor and blue denotes the eleven
    remaining stones we placed):
        image
    Now, let's determine if the sum of these distances is an almost integer. First, we find
    the distance from the origin to the stone Victor placed at (7,11), which is
    sqrt(7^2  + 11^2) ~ 13.038404... . Next, we calculate the distances for the remaining
    stones we placed in the graph above:
        1. sqrt(11^2+ 1^2)~11.045 and soo onil
        2.
        ...
        11. sqrt(4^2 + 12^2) ~ 12.6491105
When we sum these eleven distances with the distance for the stone Victor placed, we
get ~135.0000000... . The nearest integer to this number is 135, and the distance between this
sum and the nearest integer is ~1.6X10^-14<=10^10 (meaning it's an almost integer). Because
 this configuration satisfies all of Victor's rules for his rock garden, we print eleven lines
 of x y coordinates describing the locations of the stones we placed
*/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

typedef int _loop_int;
#define REP(i,n) for(_loop_int i=0;i<(_loop_int)(n);++i)
#define FOR(i,a,b) for(_loop_int i=(_loop_int)(a);i<(_loop_int)(b);++i)
#define FORR(i,a,b) for(_loop_int i=(_loop_int)(b)-1;i>=(_loop_int)(a);--i)

#define DEBUG(x) cout<<#x<<": "<<x<<endl
#define DEBUG_VEC(v) cout<<#v<<":";REP(i,v.size())cout<<" "<<v[i];cout<<endl
#define ALL(a) (a).begin(),(a).end()

#define CHMIN(a,b) a=min((a),(b))
#define CHMAX(a,b) a=max((a),(b))

inline int pack(int x,int y){
  return (x+25)*64 + (y+25);
}
inline void unpack(int p,int &x,int &y){
  x = (p/64)-25;
  y = (p%64)-25;
}

map<double,vi> mp;
vector<double> V;
int n;
map<double,int> rev;

vector<vi> answers;
vi ids;

void appen(int a,int b,int c,int d,int e,int f,int g,int h,int i,int j,int k,int l){
  vi v;
  v.push_back(a);
  v.push_back(b);
  v.push_back(c);
  v.push_back(d);
  v.push_back(e);
  v.push_back(f);
  v.push_back(g);
  v.push_back(h);
  v.push_back(i);
  v.push_back(j);
  v.push_back(k);
  v.push_back(l);
  int demi = answers.size();
  answers.push_back(v);
  double sum = 0.0;
  REP(z,v.size()){
    ids[v[z]] = demi;
    sum += V[v[z]];
  }
  // printf("%.15f\n",sum);
}

int main(){
  FOR(x,-12,13)FOR(y,-12,13){
    int dst = x*x + y*y;
    double sq = sqrt(dst);
    int sqi = sq;
    if(sqi!=sq)mp[sq].push_back(pack(x,y));
  }
  {
    map<double,vi>::iterator iter = mp.begin();
    while(iter != mp.end()){
      double d = iter->first;
      V.push_back(d);
      iter++;
    }
  }
  n = V.size();
  REP(i,n)rev[V[i]] = i;
  // go
  ids.assign(n,-1);
  appen(0,1,3,25,41,43,62,8,10,20,34,39);
  appen(2,1,3,25,41,43,62,6,8,20,34,39);
  appen(4,13,27,65,8,45,49,25,28,37,43,51);
  appen(5,30,31,45,22,31,46,13,16,31,52,54);
  appen(7,1,3,25,8,15,34,16,20,39,43,62);
  appen(9,10,41,48,21,24,62,21,25,30,38,44);
  appen(11,37,43,67,12,35,44,29,31,44,53,57);
  appen(14,21,44,66,21,36,37,3,36,37,54,62);
  appen(17,1,3,25,41,43,62,4,8,16,20,34);
  appen(18,8,27,31,7,12,57,25,29,31,50,57);
  appen(19,15,43,59,33,47,59,4,7,30,32,59);
  appen(23,1,30,66,46,54,61,27,28,31,33,66);
  appen(26,1,3,25,34,43,62,1,8,16,20,39);
  appen(40,11,38,43,26,36,65,0,3,27,59,62);
  appen(42,44,48,49,18,30,66,18,28,31,40,61);
  appen(55,0,24,40,49,54,55,27,29,40,48,49);
  appen(56,3,6,25,0,34,43,0,8,20,39,62);
  appen(58,45,53,65,26,51,65,18,21,22,46,65);
  appen(60,26,34,63,31,33,41,9,15,31,34,37);
  appen(64,12,35,37,43,44,60,11,29,31,44,57);

  int xx,yy;
  scanf("%d%d",&xx,&yy);
  double vv = sqrt(xx*xx+yy*yy);
  int id = ids[rev[vv]];
  vi vec = answers[id];
  vi head(n,0);
  bool poyo = false;
  REP(i,vec.size()){
    double ww = V[vec[i]];
    if(!poyo && ww==vv){
      poyo = true;
      continue;
    }
    while(true){
      int po = mp[ww][head[vec[i]]++];
      int xxx,yyy;
      unpack(po,xxx,yyy);
      if(xx==xxx && yy==yyy)continue;
      printf("%d %d\n",xxx,yyy);
      break;
    }
  }
  return 0;
}
