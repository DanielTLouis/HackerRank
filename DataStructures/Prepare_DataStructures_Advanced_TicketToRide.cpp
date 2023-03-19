/*
Simon received the board game Ticket to Ride* as a birthday present. After playing it with his friends, he decides to come up with a strategy for the game.
* http://www.daysofwonder.com/tickettoride *
There are n cities on the map and n-1 road plans. Each road plan consists of the following:
    * Two cities which can be directly connected by a road.
    * The length of the proposed road.
The entire road plan is designed in such a way that if one builds all the roads, it will be
possible to travel between any pair of cities.
A ticket enables you to travel between two different cities. There are m tickets, and each
ticket has a cost associated with it. A ticket is considered to be useful if there is a path
between those cities.
Simon wants to choose two cities, u and v, and build a minimal number of roads so that they
form a simple path between them. Let st be the sum of costs of all useful tickets and sr be
the sum of lengths of all the roads Simon builds. The profit for pair (u,v) is defined as
st-sr. Note that u and v are not necessarily unique and may be the same cities.
Given n road plans and m ticket prices, help Simon by printing the value of his maximum
possible profit on a new line.
Input Format
    The first line contains single positive integer, n, denoting the number of cities.
    Each of the n-1 subsequent lines contains three space-separated integers describing the
    respective values of u, v, and l for a road plan, where l<=u, v<=n, and v!=u. Here, u and
    v are two cities that the road plan proposes to connect and l is the length of theproposed
    road.
    The next line contains a single positive integer, m, denoting the number of tickets.
    Each of the m subsequent lines contains three space-separated integers describing the
    respective values of u, v, and c for a ticket from city u to city v (where  is the cost
    of the ticket).
Constraints
    1<=n<=2X10^5
    1<=m<=10^5
    a<=l,c<=10^9
Output Format
    Print a single integer denoting the the maximum profit Simon can make.
Time Limits
    * 6seconds for Java and C#.
    * Please refer to our Environment* page to see time limits for other languages.
    * https://www.hackerrank.com/environment *
Sample Input
7
    1 2 1
    1 3 1
    1 4 4
    4 5 1
    4 6 1
    4 7 1
    5
    5 7 3
    3 6 2
    3 4 10
    2 7 15
    1 6 7
Sample Output
    13
Explanation
        ticket.png
    Simon can maximize his profit by choosing the pair (3,6).
    The roads on the path between them are (3,1), (1,4), and (4,6). The total road length is
    sr=1+4+1=6.
    The useful tickets are (3,6), (3,4), and (1,6). The total ticket cost is st=2+10+7=19.
    The profit is st - sr = 19 - 6 = 13.
*/

#include <algorithm>
#include <climits>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
using namespace std;

#define FOR(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ROF(i, a, b) for (remove_cv<remove_reference<decltype(b)>::type>::type i = (b); --i >= (a); )

const long N = 200000, NN = 1 << 63-__builtin_clzl(N-1)+1, M = 100000;
long st[N], dep[N], pre[N], post[N], tick, mx[2*NN], dlt[2*NN], opt;
vector<pair<long, long>> adj[N], ticket[N], other[N], down[N], up[N];

void mconcat(long i)
{
  mx[i] = max(mx[2*i]+dlt[2*i], mx[2*i+1]+dlt[2*i+1]);
}

void add(long u, long x)
{
  bool lf = false, rf = false;
  long l = NN+pre[u], r = NN+post[u];
  while (l < r) {
    if (l & 1) lf = true, dlt[l++] += x;
    l >>= 1;
    if (lf) mconcat(l-1);
    if (r & 1) rf = true, dlt[--r] += x;
    r >>= 1;
    if (rf) mconcat(r);
  }
  for (l--; l >>= 1, r >>= 1; ) {
    if (lf || l == r) mconcat(l);
    if (rf && l != r) mconcat(r);
  }
}

void dfs(long d, long sum, long u)
{
  dep[u] = d;
  st[d] = u;
  mx[NN+tick] = - sum;
  pre[u] = tick++;
  post[u] = LONG_MAX;
  long x = 0;
  for (auto e: ticket[u])
    if (post[e.first]) {
      long v = e.first, cost = e.second;
      if (post[v] == LONG_MAX) {
        long w = st[dep[v]+1];
        down[w].emplace_back(u, cost);
        up[u].emplace_back(w, cost);
        x += cost;
      } else {
        other[u].emplace_back(v, cost);
        other[v].emplace_back(u, cost);
      }
    }
  for (auto e: adj[u])
    if (! post[e.first])
      dfs(d+1, sum+e.second, e.first);
  post[u] = tick;
  add(u, x);
}

void calc(long u, long p)
{
  for (auto e: other[u])
    add(e.first, e.second);
  for (auto e: down[u])
    add(e.first, - e.second);
  for (auto e: up[u]) {
    dlt[1] += e.second;
    add(e.first, - e.second);
  }
  opt = max(opt, mx[1]+dlt[1]);
  for (auto e: adj[u])
    if (e.first != p) {
      dlt[1] -= e.second;
      add(e.first, 2*e.second);
      calc(e.first, u);
      dlt[1] += e.second;
      add(e.first, -2*e.second);
    }
  for (auto e: other[u])
    add(e.first, - e.second);
  for (auto e: down[u])
    add(e.first, e.second);
  for (auto e: up[u]) {
    dlt[1] -= e.second;
    add(e.first, e.second);
  }
}

int main()
{
  ios_base::sync_with_stdio(0);
  long n, m, u, v, w;
  cin >> n;
  REP(i, n-1) {
    cin >> u >> v >> w;
    u--, v--;
    adj[u].emplace_back(v, w);
    adj[v].emplace_back(u, w);
  }
  cin >> m;
  REP(i, m) {
    cin >> u >> v >> w;
    u--, v--;
    ticket[u].emplace_back(v, w);
    ticket[v].emplace_back(u, w);
  }
  dfs(0, 0, 0);
  ROF(i, 1, NN)
    mconcat(i);
  calc(0, -1);
  cout << opt << endl;
}
