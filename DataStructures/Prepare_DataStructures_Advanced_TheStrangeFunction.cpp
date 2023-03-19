/*
One of the most important skills a programmer needs to learn early on is the ability to
pose a problem in an abstract way. This skill is important not just for researchers but
also in applied fields like software engineering and web development.
You are able to solve most of a problem, except for one last subproblem, which you have
posed in an abstract way as follows: Given an array consisting of  integers , define
    f(l,r)=gcd(al,a(l+1),...,ar) * (summation(i=l, ai, to r) - max(al,a(l+1),...,ar))
For example, for an input array [ 10, -5, 5, 20 ], a subsegment f(1,1) would be computed
as follows:
    image
What is max(1<=l<=r<=n) f(l,r), i.e., the maximum value of f(l,r) among all subsegments
[l,r]?
Complete the function maximumValue which takes an integer array as input and returns the
maximum value of f among all subsegments [l,r].
Note that:
    * gcd(x,y)=gcd(|x|,|y|)
    * gcd(x,0)=gcd(0,x)=|x|
Input Format
    The first line contains a single integer n
    The second line contains n space-separated integers a1,a2,...,an
Constraints
    1<=n<=50000

Output Format
    Print a single integer denoting the answer
Sample Input 0
    4
    10 -5 5 20
Sample Output 0
    50
Explanation 0
    The maximum value occurs at f(1,4)=50 as shown below.
    image
Sample Input 1
    5
    7 12 24 6 5
Sample Output 1
    144
Explanation 1
    The maximum value occurs at f(2,3)=144.
*/
#include <bits/stdc++.h>

using namespace std;

int n;
vector<long long int> v;
vector<pair<long long int, pair<long long int, long long int>>> vl;
vector<pair<long long int, pair<long long int, long long int>>> vr;
map<long long int, long long int> mp;
long long int ans;

long long int gcd(long long int a, long long int b){
    if(a > b){
        swap(a, b);
    }
    while(a){
        swap(a, b);
        a %= b;
    }
    return b;
}

long long int lcm(long long int a, long long int b){
    return a / gcd(a, b) * b;
}

inline void solve(int l, int r){
    int mid = (l + r) >> 1;
    {
        vl.clear();
        long long int sum = 0;
        long long int mx = v[mid];
        int gc = 0;
        for(int j = mid; j <= r; j++){
            sum += v[j];
            gc = gcd(gc, abs(v[j]) );
            mx = max(mx, v[j]);
            ans = max(ans, gc*(sum - mx));
        vl.push_back(make_pair(mx, make_pair(sum, gc)));
        }
    }
    {
        vr.clear();
        long long int sum = 0;
        long long int mx = v[mid];
        int gc = 0;
        for(int j = mid; j >=l; j--){
            sum += v[j];
            gc = gcd(gc, abs(v[j]) );
            mx = max(mx, v[j]);
            ans = max(ans, gc*(sum - mx));
        vr.push_back(make_pair(mx, make_pair(sum, gc)));
        }
    }
    sort(vl.begin(), vl.end());
    sort(vr.begin(), vr.end());
    int idx = 0;
    mp.clear();
    for(int i = 0; i < vl.size(); i++){
        while(idx < vr.size() && vr[idx].first <= vl[i].first){
            int gc = vr[idx].second.second;
            if(mp.count(gc) == 0){
                mp[gc] = LLONG_MIN;
            }
            mp[gc] = max(mp[gc], vr[idx].second.first-v[mid]);
            idx++;
        }
        for(auto it = mp.begin(); it != mp.end(); it++){
            long long int G = gcd((*it).first, vl[i].second.second);
            long long int SUM = (*it).second + vl[i].second.first;
            long long int MX = vl[i].first;
            G *= (SUM - MX);
            ans = max(ans, G);
        }
    }
    mp.clear();
    swap(vl, vr);
    idx = 0;
    for(int i = 0; i < vl.size(); i++){
        while(idx < vr.size() && vr[idx].first <= vl[i].first){
            int gc = vr[idx].second.second;
            if(mp.count(gc) == 0){
                mp[gc] = LLONG_MIN;
            }
            mp[gc] = max(mp[gc], vr[idx].second.first - v[mid]);
            idx++;
        }
        for(auto it = mp.begin(); it != mp.end(); it++){
            long long int G = gcd((*it).first, vl[i].second.second);
            long long int SUM = (*it).second + vl[i].second.first;
            long long int MX = vl[i].first;
            G *= (SUM - MX);
            ans = max(ans, G);
        }
    }
    if(l <= mid - 1) solve(l, mid - 1);
    if(mid + 1 <= r) solve(mid + 1, r);
}
int main(){
    cin >> n;
    for(int i = 0; i < n; i++){
        int a;
        scanf("%d", &a);
        v.push_back(a);
    }
    solve(0, n - 1);
    printf("%lld\n", ans);
    return 0;
}
