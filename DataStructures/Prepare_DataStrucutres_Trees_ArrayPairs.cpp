/*
Consider an array of n integers, A=[a1,a2,...,an]. Find and print the total number of (i,j)
pairs such that ai X aj <= max(ai, a(i+1),...,aj) where i<j.
Input Format
    The first line contains an integer, n, denoting the number of elements in the array.
    The second line consists of n space-separated integers describing the respective values of
    a1,a2,...,an.
Constraints
    1<=n<=5X10^5
    1<=a_i<=10^9
Scoring
    1<=n<=1000 for 25% of the test cases.
    1<=n<=10^5 for 50% of the test cases.
    1<=n<=5X10^5 for 100% of the test cases.
Output Format
    Print a long integer denoting the total number (i,j) pairs satisfying
    a_i X a_j <= max(a_i,a_(i+1),...,a_j) where i<j.
Sample Input
    5
    1 1 2 4 2
Sample Output
    8
Explanation
    There are eight pairs of indices satisfying the given criteria: (1,2), (1,3), (1,4), (1,5),
    (2,3), (2,4), (2,5), and (3,5). Thus, we print 8 as our answer.
*/
#include <bits/stdc++.h>
using namespace std;

#define rep(i,n) for(int i=0;i<n;i++)
#define ll long long int
#define f first
#define s second
#define pi pair<ll,ll>
#define pii pair<pi,ll>
#define f first
#define s second
#define pb push_back
#define mod 1000000007
#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)

int N;
int A[1000011];
int L[1000011];
int R[1000011];
vector<int>g[1000011];
ll bt[1000011];
int maxn;
void update(int ind, int val) {
    while(ind <= maxn) {
        bt[ind] += val;
        ind += (ind & -ind);
    }
}
ll query(int ind) {
    ll ans = 0;
    while(ind > 0) {
        ans += bt[ind];
        ind -= (ind & -ind);
    }
    return ans;
}
vector<int>V;
int find_ind(int x) {
    if(V.back() <= x) return V.size();
    return upper_bound(V.begin(), V.end(), x) - V.begin();
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    set<int>S;
    unordered_map<int, int>M;

    for(int i = 1; i <= N; i++) {
        cin >> A[i];
        assert(A[i] >= 1 and A[i] <= 1000000000);
        S.insert(A[i]);
    }
    vector<pi>window;
    for(int i = 1; i <= N; i++) {
        while(window.size() > 0 and window.back().f < A[i]) window.pop_back();
        if(window.size() == 0) L[i] = 1;
        else {
            L[i] = window.back().s + 1;
        }
        window.pb(mp(A[i], i));
    }
    window.clear();
    for(int i = N; i >= 1; i--) {
        while(window.size() > 0 and window.back().f <= A[i]) window.pop_back();
        if(window.size() == 0) R[i] = N;
        else {
            R[i] = window.back().s - 1;
        }
        window.pb(mp(A[i], i));
    }

    for(int i = 1; i <= N; i++) {
        if(i - L[i] <= R[i] - i) {
            for(int j = L[i]; j < i; j++) {
                g[i - 1].pb(-A[i] / A[j]);
                g[R[i]].pb(A[i] / A[j]);
                //S.insert(A[i]/A[j]);
            }

            g[i].pb(-1);
            g[R[i]].pb(1);
        } else {

            for(int j = i + 1; j <= R[i]; j++) {
                g[L[i] - 1].pb(-A[i] / A[j]);
                g[i].pb(A[i] / A[j]);
                //S.insert(A[i]/A[j]);
            }

            g[L[i] - 1].pb(-1);
            g[i - 1].pb(1);
        }
    }
    maxn = S.size() + 2;
    int cnt = 1;
    for(set<int>::iterator it = S.begin(); it != S.end(); it++) {
        M[*it] = cnt++;
    }
    ll ans = 0;
    int r;
    V = vector<int>(S.begin(), S.end());
    for(int i = 1; i <= N; i++) {
        update(M[A[i]], 1);
        for(int j = 0; j < g[i].size(); j++) {
            r = find_ind(abs(g[i][j]));
            if(g[i][j] < 0) {
                ans -= query(r);
            } else {
                ans += query(r);
            }
        }
    }
    cout << ans;
}
