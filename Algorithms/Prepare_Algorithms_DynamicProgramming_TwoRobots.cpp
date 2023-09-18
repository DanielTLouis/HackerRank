/*
You have a warehouse with M containers filled with an infinite number of candies. The containers
are arranged in a single row, equally spaced to be 1 meter apart. You also have 2 robots that can
pick up 1 piece of candy and transport it between any two containers.
The robots take instructions in the form of queries consisting of two integers, Ma and Mb,
respectively. To execute a query, a robot travels to container Ma, picks up 1 candy, transports it
to container Mb, and then stops at Mb until it receives another query.
Calculate the minimum total distance the robots must travel to execute N queries in order.
Note: You choose which robot executes each query.
Input Format

    The first line contains a single integer, T(the number of test cases); each of the T test
    cases is described over N+1 lines.
    The first line of a test case has two space-separated integers, M(the number of containers)
    and N(the number of queries).
    The N subsequent lines each contain two space-separated integers, Ma and Mb, respectively;
    each line Ni describes the ith query.
Constraints
    1<=T<=50
    1<M<=1000
    1<=N<=1000
    1<=a,b<=M
    Ma!=Mb
Output Format
    On a new line for each test case, print an integer denoting the minimum total distance that
    the robots must travel to execute the queries in order.
Sample Input
    3
    5 4
    1 5
    3 2
    4 1
    2 4
    4 2
    1 2
    4 3
    10 3
    2 4
    5 4
    9 8
Sample Output
    11
    2
    5
Explanation
    In this explanation, we refer to the two robots as R1 and R2, each container i as Mi, and the
    total distance traveled for each query j as Dj.
    Note: For the first query a robot executes, there is no travel distance. For each subsequent
    query that robot executes, it must travel from the location where it completed its last query.
    Test Case 0:
        The minimum distance traveled is 11:
        Robot: R1
            M1->M5
            D0=|1-5|=4 meters.
        Robot: R2
            M3->M2
            D1=|3-2|=1 meter.
        Robot: R1
            M5->M4->M1
            D2=|5-4|+|4-1|=1+3=4 meters.
        Robot: R2
            M2->M2->M4
            D3=|2-2|+|2-4|=0+2=2 meters.
        Sum the distances traveled (D0+D1+D2+D3=4+1+4+2=11) and print the result on a new line.
    Test Case 1:
        Robot: R1
            M1->M2
            D0=|1-2|=1 meters.
        Robot: R2
            M4->M3
                D1=|4-3|=1 meters.
        Sum the distances traveled (D0+D1=1+1=2) and print the result on a new line.
    Test Case 2:
        Robot: R1
            M2->M4
            D0=|2-4|=2 meters.
        Robot: R1
            M4->M5->M4
            D1=|4-5|+|5-4|=1+1=2 meters.
        Robot: R2
            M9->M8
            D2=|9-8|=1 meters.
        Sum the distances traveled (D0+D1+D2=2+2+1=5) and print the result on a new line.
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define For(i,n) for(int i=0;i<n;i++)
#define mem(a,b) memset(a,b,sizeof(a))
#define int long long int
#define ld long double
#define fio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pb push_back
#define mp make_pair
#define mod 1000000007
#define ld long double
#define pb push_back
#define ff first
#define ss second
#define vpi vector<pair<int,int> >
#define vv vector<int>
#define MAXN 1001
int A[MAXN];
vector<pair<int, int>> p;
int m, n;
int dp[2][MAXN][MAXN];
int fun(int en1, int en2, int i)
{
    //cout << en1 << " " << en2 << " " << i << " " << n << endl;
    if (i >= n)return 0;
    if (dp[en1][en2][i] != -1)return dp[en1][en2][i];
    if (en1 == 0)
    {
        if (en2 == 0) {
            return dp[en1][en2][i] = min(abs(p[i].ff - p[i - 1].ss) + abs(p[i].ff - p[i].ss) + fun(0, en2, i + 1),
                                         abs(p[i].ff - p[i].ss) + fun(1, p[i - 1].ss, i + 1));
        }
        else {
            return dp[en1][en2][i] = min(abs(p[i].ff - p[i - 1].ss) + abs(p[i].ff - p[i].ss) + fun(0, en2, i + 1),
                                         abs(p[i].ff - en2) + abs(p[i].ff - p[i].ss) + fun(1, p[i - 1].ss, i + 1));
        }
    }
    else {

        return dp[en1][en2][i] = min(abs(p[i].ff - en2 ) + abs(p[i].ff - p[i].ss) + fun(0, p[i - 1].ss, i + 1),
                                     abs(p[i].ff - p[i - 1].ss) + abs(p[i].ff - p[i].ss) + fun(1, en2, i + 1));
    }

}
int32_t main()
{

    fio;
    int t;
    cin >> t;
    while (t--)
    {
        p.clear();
        mem(dp, -1);
        cin >> m >> n;
        for (int i = 0; i < n; i++)
        {
            int x, y;
            cin >> x >> y;
            p.pb({x, y});
        }
        cout << abs(p[0].ff - p[0].ss) + fun(0, 0, 1) << endl;
    }


}
