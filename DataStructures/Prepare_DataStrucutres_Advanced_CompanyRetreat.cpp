/*
The LRT Company has n employees. Each employee has a unique ID number from 1 to n, where the
director's ID is number 1. Every employee in the company has exactly one immediate supervisor
— except the director, who has no supervisor. The company's employee hierarchy forms a tree of
employee IDs that's rooted at employee number 1 (the director).
The director decides to have a retreat lasting m days. Each day, the employees will be
assigned to different groups for team building exercises. Groups are constructed in the
following way:
    * An employee can invite their immediate supervisor (the director has no supervisor and,
    thus, doesn't invite anyone). If employee a is invited by employee b, then a and b are
    considered to be in the same group.
    * Once an employee is invited to be in a group, they are in that group. This means that if
    two employees have the same immediate supervisor, only one of them can invite that
    supervisor to be in their group.
    * Every employee must be in a group, even if they are the only employee in it.
The venue where LRT is hosting the retreat has different pricing for each of the m days of the
retreat. For each day j, there is a cost of d_j dollars per group and a per-group size limit
of p_j (i.e., the maximum number of people that can be in any group on that day).
Help the director find optimal groupings for each day so the cost of the m-day retreat is
minimal, then print the total cost of the retreat. As this answer can be quite large, your
answer must be modulo 10^9 +7.
Input Format
    The first line contains two space-separated integers denoting the respective values of
    n (the number of employees) and m (the retreat's duration in days).
    The next line contains n-1 space-separated integers where each integer i denotes
    s_i(1<i<=n), which is the ID number of employee i's direct supervisor.
    Each line j of the m subsequent lines contain two space-separated integers describing the
    respective values of d_j (the cost per group in dollars) and p_j (the maximum number of
    people per group) for the jth day of the retreat.
Constraints
    1<=n,m<=10^5
    1<=s_i<=n
    1<=d_j,p_j<=10^9
Subtask
    1<=n,m<=2000 for 40% of the maximum possible score.
Output Format
    Print a single integer denoting the minimum total cost for the m-day retreat. As this
    number can be quite large, print your answer modulo 10^9 +7.
Sample Input
    7 3
    1 1 3 4 2 4
    5 3
    6 2
    1 1
Sample Output
    46
Explanation
    In the Sample Case above, the company has 7 employees and the retreat goes on for 3 days.
    The hierarchy looks like this:
        company hierarchy
    On the first day, the cost per group is 5 dollars and each group has a maximum size of 3.
    The employees split into the following three groups:
    `   1. Employee 6 invites their manager, employee 2. Employee 2 then invites their manager,
        employee 1(the director).
        2. Employee 5 invites their manager, employee 4. Employee 4 then invites their manager,
        employee 3.
        3. Employee 7's manager is already in another group, so they are in a group by
        themself.
    These groupings are demonstrated in the following image where each group has a different
    pattern:
        groupings
    In other words, the final groups are {1,2,6}, {3,4,5}, and {7}. This means the total cost
    for the first day is groupsXcost=3*5=15 dollars.
    On the second day, they split into 4 groups with a maximum size of 2 at a total cost of 24
    dollars. On the third day, they split into 7 groups of size 1 at a total cost of 7
    dollars. When we sum the costs for all three days, we get 15+24+7=46%(10^9 +7)=46 as our
    answer.
*/
#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef pair < int, int > ii;

const int N = 1 << 17;
const int LOG = 17;

int n, m, tick, cnt;
int dep[N], st[N], nd[N], a[N], leaf[N];
vector < int > v[N], q[N];

int t[N << 1], sparse[LOG][N];

void up(int x, int k) {
    t[x += N] = k;
    while(x > 1) {
        x >>= 1;
        t[x] = min(t[x + x], t[x + x + 1]);
    }
}

int get(int l, int r) {
    int res = 1e9;
    for(l += N, r += N; l <= r; l = (l + 1) >> 1, r = (r - 1) >> 1) {
        if(l & 1) res = min(res, t[l]);
        if(~r & 1) res = min(res, t[r]);
    }
    return res;
}

void dfs(int p, int x) {
    st[x] = ++tick;
    dep[x] = dep[p] + 1;
    sparse[0][x] = p;
    for(int i = 1; i < LOG; i++)
        sparse[i][x] = sparse[i - 1][sparse[i - 1][x]];
    leaf[x] = 1e9;
    for(auto u : v[x]) {
        dfs(x, u);
        leaf[x] = min(leaf[x], leaf[u] + 1);
    }
    if(leaf[x] > 5e8) {
        leaf[x] = 0;
        cnt++;
    }
    q[leaf[x]].push_back(x);
    nd[x] = tick;
}

int calc(int group) {
    int res = cnt;
    priority_queue < ii > Q;
    for(auto x : q[group])
        Q.push({dep[x], x});
    vector < int > vv;
    while(!Q.empty()) {
        int x = Q.top().second;
        Q.pop();
        if(leaf[x] < group or get(st[x], nd[x]) - dep[x] < group)
            continue;
        vv.push_back(x);
        up(st[x], dep[x]);
        res++;
        if(dep[x] > group) {
            int k = group;
            for(int i = LOG - 1; i >= 0; i--) {
                if(k >= (1 << i)) {
                    k -= 1 << i;
                    x = sparse[i][x];
                }
            }
            Q.push({dep[x], x});
        }
    }
    for(auto x : vv)
        up(st[x], 1e9);
    return res;
}

int main () {

    for(int i = 1; i < N + N; i++)
        t[i] = 1e9;

    scanf("%d %d", &n, &m);

    for(int i = 2; i <= n; i++) {
        int x;
        scanf("%d", &x);
        v[x].push_back(i);
    }

    dfs(0, 1);

    for(int i = 1; i <= n; i++)
        a[i] = calc(i);

    ll ans = 0;

    for(int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        ans += (ll) x * a[min(n, y)];
        ans %= (int) 1e9 + 7;
    }

    printf("%lld\n", ans);

    return 0;

}
