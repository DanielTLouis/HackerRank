/*
There are N points on an XY plane. In one turn, you can select a set of collinear points on the
plane and remove them. Your goal is to remove all the points in the least number of turns. Given
the coordinates of the points, calculate two things:
    * The minimum number of turns (T) needed to remove all the points.
    * The number of ways to to remove them in T turns. Two ways are considered different if any
    point is removed in a different turn.
Input Format
    The first line contains the number of test cases T. T test cases follow. Each test case
    contains N on the first line, followed by N lines giving the coordinates of the points.
Constraints
    1 <= T <= 50
    1 <= N <= 16
    0 <= xi,yi <= 100
    No two points will have the same coordinates.
Output Format
    Output T lines, one for each test case, containing the least number of turns needed to remove
    all points and the number of ways to do so. As the answers can be large, output them modulo
    1000000007.
Sample Input
    2
    3
    0 0
    0 1
    1 0
    4
    3 4
    3 5
    3 6
    5 5
Sample Output
    2 6
    2 8
Explanation
    For the 1st input, Let the points be labelled p1,p2,p3. These are the ways to remove them
    (first turn's points, followed by second turn's points):
    a. 1) p1,p2 2) p3
    b. 1) p1,p3 2) p2
    c. 1) p2,p3 2) p1
    d. 1) p3 2) p1,p2
    e. 1) p2 2) p1,p3
    f. 1) p1 2) p3,p2
*/
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MOD 1000000007
#define MAXN 17
int N, X[MAXN], Y[MAXN], a[MAXN][MAXN];
bool colinear[1 << MAXN];
int dp1[1 << MAXN], dp2[1 << MAXN];

int gcd(int a, int b){ return b ? gcd(b, a%b) : a; }


int CMP;
bool cmp(int x, int y){ return a[CMP][x] < a[CMP][y]; }

int get(int mask){
  if(dp2[mask] != -1) return dp2[mask];
  dp2[mask] = 0;
  int points[MAXN], P = 0;
  REP(j, N) if(mask & (1 << j)) points[P++] = j;
  if(P < 3) return dp2[mask] = 1;
  int mask1 = mask ^ (1 << points[0]);
  if(dp1[mask] - 1 == dp1[mask1]) dp2[mask] = (dp2[mask] + get(mask1)) % MOD;
  int first = points[0];
  CMP = first;
  sort(points + 1, points + P, cmp);
  int start = 0, end = 1;
  while(end < P){
    start = end++;
    while(end < P && a[first][points[start]] == a[first][points[end]]) end++;
    //printf("mask: %d P: %d start: %d end: %d\n", mask, P, start, end);
    FOR(i, 1, (1 << (end - start)) - 1){
      int mask2 = mask1;
      REP(j, end - start) if(i & (1 << j)) mask2 ^= 1 << points[start + j];
      if(dp1[mask] - 1 == dp1[mask2]) dp2[mask] = (dp2[mask] + get(mask2)) % MOD;
    }
  }
  return dp2[mask];
}

int fac(int n){
  int ans = 1;
  REP(i, n) ans = ((long long) ans * (i + 1)) % MOD;
  return ans;
}

int main(int argc, char *argv[]){
  int T;
  int points[MAXN], P;
  scanf("%d", &T);
  while(T--){
    scanf("%d", &N);
    REP(i, N) scanf("%d%d", X+i, Y+i);
    REP(i, N) REP(j, N) if(i != j){
      int dx = X[i] - X[j], dy = Y[i] - Y[j];
      int g = gcd(dx, dy);
      dx /= g;
      dy /= g;
      if(dx <= 0 || (dx == 0 && dy < 0)){
        dx *= -1;
        dy *= -1;
      }
      a[i][j] = dy * 1000 + dx;
    }
    REP(i, 1 << N){
      colinear[i] = true;
      int first = -1, second = -1;
      REP(j, N) if(i & (1 << j)){
        if(first == -1){ first = j; continue; }
        if(second == -1){ second = j; continue; }
        if(a[first][second] != a[first][j]){ colinear[i] = false; break; }
      }
    }
    REP(i, 1 << N){
      dp2[i] = -1;
      P = 0;
      REP(j, N) if(i & (1 << j)) points[P++] = j;
      if(P < 3){ dp1[i] = (P != 0); continue; }
      dp1[i] = N;
      int first = points[0];
      FOR(j, 1, P - 1){
        int second = points[j];
        int ii = i ^ (1 << first) ^ (1 << second);
        FOR(k, j+1, P - 1) if(a[first][second] == a[first][points[k]]) ii ^= (1 << points[k]);
        dp1[i] = min(dp1[i], dp1[ii] + 1);
      }
    }
    int ans1 = dp1[(1 << N) - 1];
    int ans2 = ((long long)get((1 << N) - 1) * fac(ans1)) % MOD;
    printf("%d %d\n", ans1, ans2);
  }
  return 0;
}
