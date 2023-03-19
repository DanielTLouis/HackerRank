/*
You are given an unrooted tree of n nodes numbered from 1 to n. Each node i has a
color, c_i.
Let d(i,j) be the number of different colors in the path between node i and node j. For
each node i, calculate the value of sum_i, defined as follows:
    sum_i = sumation(d(i,j)) form  j=1 to n
Your task is to print the value of sum_i for each node 1<=i<=n.
Input Format
    The first line contains a single integer, n, denoting the number of nodes.
    The second line contains n space-separated integers, c1,c2,...,cn, where each
    describes the color of node i.
    Each of the n-1 subsequent lines contains 2 space-separated integers, a and b,
    defining an undirected edge between nodes a and b.
Constraints
    1<=n<=10^5
    1<=c_i<=10^5
Output Format
    Print n lines, where the ith line contains a single integer denoting sum_i.
Sample Input
    5
    1 2 3 2 3
    1 2
    2 3
    2 4
    1 5
Sample Output
    10
    9
    11
    9
    12
Explanation
    The Sample Input defines the following tree:
        may(1).png
    Each sum_i is calculated as follows:
        1. sum_1 = d(1,1)+d(1,2)+d(1,3)+d(1,4)+d(1,5) = 1+2+3+2+2 = 10
        2. sum_2 = d(2,1)+d(2,2)+d(2,3)+d(2,4)+d(2,5) = 2+1+2+1+3 = 9
        3. sum_3 = d(3,1)+d(3,2)+d(3,3)+d(3,4)+d(3,5) = 3+2+1+2+3 = 11
        4. sum_4 = d(4,1)+d(4,2)+d(4,3)+d(4,4)+d(4,5) = 2+1+2+1+3 = 9
        5. sum_5 = d(5,1)+d(5,2)+d(5,3)+d(5,4)+d(5,5) = 2+3+3+3+1 = 12
*/

#include <bits/stdc++.h>

using namespace std;

vector<int> ve[110000], V[110000];
long long ans[110000], Base, del[410000];
int sum[110000], L[110000], R[110000], st[110000], Time, n, x, y;

bool cmp(int x, int y) {
    return L[x] > L[y];
}

void dfs(int k, int f) {
    L[k] = ++Time;
    sum[k] = 1;
    for (int i = 0; i < (int) ve[k].size(); i++)
        if (ve[k][i] != f)
            dfs(ve[k][i], k), sum[k] += sum[ve[k][i]];
    R[k] = Time;
}

void modify(int k, int q, int h, int l, int r, int d) {
    if (l <= q && h <= r)
        del[k] += d;
    else {
        if (r <= (q + h) / 2)
            modify(k * 2, q, (q + h) / 2, l, r, d);
        else if ((q + h) / 2 < l)
            modify(k * 2 + 1, (q + h) / 2 + 1, h, l, r, d);
        else
            modify(k * 2, q, (q + h) / 2, l, r, d), modify(k * 2 + 1, (q + h) / 2 + 1, h, l, r, d);
    }
}

void dfs(int k, int q, int h, long long now) {
    now += del[k];
    if (q == h)
        ans[q] = now;
    else {
        dfs(k * 2, q, (q + h) / 2, now);
        dfs(k * 2 + 1, (q + h) / 2 + 1, h, now);
    }
}

void doit(vector <int> V) {
    if (V.size() == 0)
        return ;
    Base += n;
    sort(V.begin(), V.end(), cmp);
    int len = 0;
    for (int i = 0; i < (int) V.size(); i++) {
        vector <int> T;
        while (len && L[V[i]] <= L[st[len]] && L[st[len]] <= R[V[i]]) {
            T.push_back(st[len]);
            len--;
        }
        st[++len] = V[i];
        int r = T.size() - 1;
        for (int p = ((int) ve[V[i]].size()) - 1; p >= 0; p--)
            if (sum[ve[V[i]][p]] < sum[V[i]]) {
                int q = ve[V[i]][p];
                int kk = sum[q];
                int RR = r;
                while (RR >= 0 && L[q] <= L[T[RR]] && L[T[RR]] <= R[q])
                    RR -= 1;
                for (int j = RR + 1; j <= r; j++)
                    kk -= sum[T[j]];
                modify(1, 1, n, L[q], R[q], kk);
                for (int j = RR + 1; j <= r; j++)
                    modify(1, 1, n, L[T[j]], R[T[j]], -kk);
                r = RR;
            }

    }
    int kk = n;
    for (int j = 1; j <= len; j++)
        kk -= sum[st[j]];
    modify(1, 1, n, 1, n, kk);
    for (int j = 1; j <= len; j++)
        modify(1, 1, n, L[st[j]], R[st[j]], -kk);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &x), V[x].push_back(i);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        ve[x].push_back(y);
        ve[y].push_back(x);
    }
    dfs(1, 0);
    for (int i = 1; i <= 100000; i++) {
        doit(V[i]);
    }
    dfs(1, 1, n, 0);
    for (int i = 1 ; i <= n; i++)
        printf("%lld\n", Base - ans[L[i]]);
}
