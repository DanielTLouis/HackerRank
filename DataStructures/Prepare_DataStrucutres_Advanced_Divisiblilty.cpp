/*
Two positive integers P and S are given.
S=d1,d2,...,dn is decimal representation of integer S.
Lets define f(l,r)=dl,d(l+1),...,dr.
For example, if S=9876:
    d1=9, d2=8, d3=7, d4=6
    f(2,3)=d2d3=87
    f(1,3)=d1d2d3=987
    f(4,4)=d4=6
For each query you will be given two integers b and e that define a substring equal to f(b,e).
Your task is to calculate divisibility of given substring.
Divisibility of given substring is equal to number of (i,j) pairs such that:
    b<=i<=j<e and
    f(i,j) is divisible by P, assuming that 0 is divisible by any other integer.
Timelimits
    Timelimits for this challenge is given here*
    * http://hr-testcases.s3.amazonaws.com/4520/checkerlimits.json *
Input Format
    First line contains two integers P and Q separated by a single space. Q is the number of
    queries.
    Second line contains a big integer S.
    Next Q lines contains two integers b and e separated by a single space each - begin and
    end points of substring.
Constraints
    2<=P<=10^9
    1000<=S<=10^100000
    1<=Q<=100000
    1<=b<=e<=N
Output Format
    Output Q lines, the i-th line of the output should contain single integer [] divisibility
    of the i-th query substring.
Sample Input
    3 5
    4831318
    3 5
    5 7
    1 7
    1 2
    2 3
Sample Output
    2
    3
    9
    1
    1
Explanation
    In the first query, b = 3 and e = 5. Two such pairs that are divisible by P = 3 are
    f(3, 3) = 3 and f(5, 5). Hence the answer 2.
    In the second query, b = 5 and e = 7. Three such pairs that are divisible by P are
    F(5, 5) = 3, f(6, 7) = 18 and f(5, 7) = 318
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

#define fi first
#define se second

using namespace std;

typedef long long int Lint;
typedef pair<int, int> ii;
int N, Q, K, srt[110000], sizeLeft[110000], sizeRight[110000], A, B, C, D = 1,
        R[110000][35], L[110000][35], OK[110000];
Lint num[110000], ans[110000], G[110000], P, POW[35]; //G[x]=f( x , N )
ii query[110000];
string s;

int compare(const int &a, const int &b) {
    if (query[a].fi / K != query[b].fi / K) {
        return query[a].fi < query[b].fi;
    }

    return query[a].se < query[b].se;
}

int compare2(const int &a, const int &b) {
    return G[a] < G[b];
}

int main() {
    cin >> P >> Q;
    cin >> s;

    while ((P % 2) == 0) {
        P /= 2;
        A++;
        D *= 2;
    }

    while ((P % 5) == 0) {
        P /= 5;
        B++;
        D *= 5;
    }

    C = max(A, B);
    N = s.size();

    for (int i = 0; i < N; i++) {
        num[i + 1] = s[i] - '0';
    }

    K = sqrt(N);
    Lint power = 1;

    for (int i = N; i; i--) {
        srt[i + 1] = i + 1;
        G[i] = (G[i + 1] + (power * num[i]) % P) % P;
        power = (power * 10LL) % P;
    }

    POW[0] = 1;

    for (int i = 1; i <= 32; i++) {
        POW[i] = (POW[i - 1] * 10) % D;
    }

    srt[1] = 1;
    sort(srt + 1, srt + 2 + N, compare2);

    for (int i = 1, prev = -1, count = 0; i <= N + 1; i++) {
        if (G[srt[i]] != prev) {
            count++, prev = G[srt[i]];
        }

        G[srt[i]] = count;
    }

    for (int i = 1; i <= N; i++) {
        Lint md = 0;
        int j;

        for (j = 0; i - j && j < C; j++) {
            md = (md + (POW[j] * num[i - j]) % D) % D;
            R[i + 1][j + 1] = R[i + 1][j];

            if (!md && G[i - j] == G[i + 1]) {
                R[i + 1][j + 1]++, L[i - j][j + 1]++;
            }
        }

        if (j == C && !md) {
            OK[i + 1] = 1;
        }
    }

    for (int i = 1; i <= N + 1; i++) {
        for (int j = 0; i + j <= N && j < C; j++) {
            L[i][j + 1] += L[i][j];
        }
    }

    for (int i = 1, begin, end; i <= Q; i++) {
        scanf(" %d %d", &begin, &end);
        query[i] = ii(begin, end);
        srt[i] = i;
    }

    sort(srt + 1, srt + 1 + Q, compare);
    Lint sum = 0;
    int left = N, right = N + 5, r, l;

    for (int i = 1, b, e; i <= Q; i++) {
        b = query[srt[i]].fi, e = query[srt[i]].se + 1;

        if (e < right) {
            r = b - C - 1, l = b + C;
            memset(sizeRight, 0, sizeof sizeRight);
            memset(sizeLeft, 0, sizeof sizeLeft);
            left = b, right = b - 1;
            sum = 0;
        }

        for (int j = right + 1; j <= e; j++, r++) {
            if (r >= left) {
                sizeRight[G[r]]++;
            }

            if (j - left > C && OK[j]) {
                sum += sizeRight[G[j]], sizeLeft[G[j]]++;
            }

            sum += R[j][min(j - left, C)];
        }

        for (int j = left - 1; j >= b; j--, l--) {
            if (OK[l] && l <= e) {
                sizeLeft[G[l]]++;
            }

            sum += sizeLeft[G[j]] + L[j][min(C, e - j)];

            if (e - C > j) {
                sizeRight[G[j]]++;
            }
        }

        for (int j = left; j < b; j++) {
            if (l < e) {
                l++;
                sum -= sizeLeft[G[j]] + L[j][min(C, e - j)];

                if (OK[l]) {
                    sizeLeft[G[l]]--;
                }
            } else {
                sum -= L[j][e - j];
            }

            if (l >= e) {
                l = j + C + 1;
            }

            if (e - C > j) {
                sizeRight[G[j]]--;
            }
        }

        left = b;
        right = e;
        ans[srt[i]] = sum;
    }

    for (int i = 1; i <= Q; i++) {
        printf("%lld\n", ans[i]);
    }

    return 0;
}
