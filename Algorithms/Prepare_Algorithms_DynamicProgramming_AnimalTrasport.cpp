/*
Capeta is working part-time for an animal shipping company. He needs to pick up animals from
various zoos and drop them to other zoos. The company ships four kinds of animals: elephants,
dogs, cats, and mice.
There are m zoos, numbered 1 to m. Also, there are n animals. For each animal i, Capeta knows its
type ti (E for elephant, D for dog, C for cat and M for mouse), source zoo si where Capeta has to
pick it up from, and destination zoo di where Capeta needs to deliver it to.
image
Capeta is given a truck with a huge capacity where n animals can easily fit. He is also given
additional instructions:
    1.He must visit the zoos in increasing order. He also cannot skip zoos.
    2.Dogs are scared of elephants, so he is not allowed to bring them together at the same time.
    3.Cats are scared of dogs, so he is not allowed to bring them together at the same time.
    4.Mice are scared of cats, so he is not allowed to bring them together at the same time.
    5.Elephants are scared of mice, so he is not allowed to bring them together at the same time.
Also, loading and unloading animals are complicated, so once an animal is loaded onto the truck,
that animal will only be unloaded at its destination.
Because of these reasons, Capeta might not be able to transport all animals. He will need to
ignore some animals. Which ones? The company decided to leave that decision for Capeta. He is
asked to prepare a report and present it at a board meeting of the company.
Capeta needs to report the minimum number of zoos that must be reached so that she is able to
transport x animals, for each x from 1 to n.
Complete the function minimumZooNumbers and return an integer array where the xth integer is the
minimum number of zoos that Capeta needs to reach so that she is able to transport x animals, or
-1 if it is impossible to transport x animals.
He is good at driving, but not so much at planning. Hence, he needs your help.
Input Format
    The first line contains a single integer t, the number of test cases.
    Each test case consists of four lines. The first line contains two space-separated integers m
    and n. The second line contains t1,t2,...,tn space-separated characters . The third line
    contains  space-separated integers s1,s2,...,sn. The fourth line contains n space-separated
    integers d1,d2,..,dn.
    ti, si and di are the details for the th animal, as described in the problem statement.
Constraints
    1<=t<=10
    1<=m,n<=5*10^4
    1<=si,di<=m
    si!=di
    ti is either E, D, C or M
Subtasks
    For 30% of the total score, m,n<=10^3
Output Format
    For each case, print a single line containing n space-separated integers, where the xth
    integer is the minimum number of zoos that Capeta needs to reach so that she is able to
    transport  animals. If it is not possible to transport x animals at all, then put -1 instead.
Sample Input 0
    2
    10 3
    E D C
    4 1 4
    7 5 8
    10 6
    E D C M E D
    1 1 1 2 9 7
    2 2 2 4 10 10
Sample Output 0
    5 8 -1
    2 2 4 10 -1 -1
Explanation 0
    First Test Case
        Capeta can transport one animal by traveling up to zoo number 5. Just drop the dog there.
        Next, in order to transport 2 animals (elephant and cat), Capeta has to go up to zoo
        number 8.
    Second Test Case
        1 Animal: Drop the elephant to zoo 2.
        2 Animal: Drop the elephant and cat to zoo 2.
        3 Animal: Drop the elephant and cat to zoo 2. Then drop the mouse to zoo 4.
        4 Animal: Drop the elephant and cat to zoo 2. Then drop the mouse to zoo 4. Finally, drop
        either the elephant or the dog to 10.
        It is impossible to transport 5 or 6 animals.
*/
#include <bits/stdc++.h>
#define REP(i, n) for (int i = 0; (i) < int(n); ++ (i))
#define REP_R(i, n) for (int i = (n) - 1; (i) >= 0; -- (i))
using namespace std;

template <class Monoid, class OperatorMonoid>
struct lazy_propagation_segment_tree { // on monoids
    static_assert (is_same<typename Monoid::underlying_type, typename OperatorMonoid::target_type>::value, "");
    typedef typename Monoid::underlying_type underlying_type;
    typedef typename OperatorMonoid::underlying_type operator_type;
    Monoid mon;
    OperatorMonoid op;
    int n;
    vector<underlying_type> a;
    vector<operator_type> f;
    lazy_propagation_segment_tree() = default;
    lazy_propagation_segment_tree(int a_n, underlying_type initial_value = Monoid().unit(), Monoid const & a_mon = Monoid(), OperatorMonoid const & a_op = OperatorMonoid())
            : mon(a_mon), op(a_op) {
        n = 1; while (n <= a_n) n *= 2;
        a.resize(2 * n - 1, mon.unit());
        fill(a.begin() + (n - 1), a.begin() + ((n - 1) + a_n), initial_value); // set initial values
        REP_R (i, n - 1) a[i] = mon.append(a[2 * i + 1], a[2 * i + 2]); // propagate initial values
        f.resize(max(0, (2 * n - 1) - n), op.identity());
    }
    void point_set(int i, underlying_type z) {
        assert (0 <= i and i < n);
        point_set(0, 0, n, i, z);
    }
    void point_set(int i, int il, int ir, int j, underlying_type z) {
        if (i == n + j - 1) { // 0-based
            a[i] = z;
        } else if (ir <= j or j+1 <= il) {
            // nop
        } else {
            range_apply(2 * i + 1, il, (il + ir) / 2, 0, n, f[i]);
            range_apply(2 * i + 2, (il + ir) / 2, ir, 0, n, f[i]);
            f[i] = op.identity();
            point_set(2 * i + 1, il, (il + ir) / 2, j, z);
            point_set(2 * i + 2, (il + ir) / 2, ir, j, z);
            a[i] = mon.append(a[2 * i + 1], a[2 * i + 2]);
        }
    }
    void range_apply(int l, int r, operator_type z) {
        assert (0 <= l and l <= r and r <= n);
        range_apply(0, 0, n, l, r, z);
    }
    void range_apply(int i, int il, int ir, int l, int r, operator_type z) {
        if (l <= il and ir <= r) { // 0-based
            a[i] = op.apply(z, a[i]);
            if (i < f.size()) f[i] = op.compose(z, f[i]);
        } else if (ir <= l or r <= il) {
            // nop
        } else {
            range_apply(2 * i + 1, il, (il + ir) / 2, 0, n, f[i]);
            range_apply(2 * i + 2, (il + ir) / 2, ir, 0, n, f[i]);
            f[i] = op.identity();
            range_apply(2 * i + 1, il, (il + ir) / 2, l, r, z);
            range_apply(2 * i + 2, (il + ir) / 2, ir, l, r, z);
            a[i] = mon.append(a[2 * i + 1], a[2 * i + 2]);
        }
    }
    underlying_type range_concat(int l, int r) {
        assert (0 <= l and l <= r and r <= n);
        return range_concat(0, 0, n, l, r);
    }
    underlying_type range_concat(int i, int il, int ir, int l, int r) {
        if (l <= il and ir <= r) { // 0-based
            return a[i];
        } else if (ir <= l or r <= il) {
            return mon.unit();
        } else {
            return op.apply(f[i], mon.append(
                    range_concat(2 * i + 1, il, (il + ir) / 2, l, r),
                    range_concat(2 * i + 2, (il + ir) / 2, ir, l, r)));
        }
    }
};
struct max_monoid {
    typedef int underlying_type;
    int unit() const { return 0; }
    int append(int a, int b) const { return max(a, b); }
};
struct plus_operator_monoid {
    typedef int underlying_type;
    typedef int target_type;
    int identity() const { return 0; }
    int apply(underlying_type a, target_type b) const { return a + b; }
    int compose(underlying_type a, underlying_type b) const { return a + b; }
};
typedef lazy_propagation_segment_tree<max_monoid, plus_operator_monoid> starry_sky_tree;

int main() {
    int testcase; scanf("%d", &testcase);
    while (testcase --) {
        // input
        int m, n; scanf("%d%d", &m, &n);
        vector<char> t(n); REP (i, n) scanf(" %c", &t[i]);
        vector<int> s(n); REP (i, n) { scanf("%d", &s[i]); -- s[i]; }
        vector<int> d(n); REP (i, n) { scanf("%d", &d[i]); -- d[i]; }
        // solve
        vector<vector<int> > from_d(m);
        REP (i, n) {
            if (s[i] < d[i]) {
                from_d[d[i]].push_back(i);
            }
        }
        vector<int> dp(m);
        array<starry_sky_tree, 2> segtree;
        REP (p, 2) segtree[p] = starry_sky_tree(m + 1);
        REP (x, m) {
            for (int i : from_d[x]) {
                const char *table = "EDCM";
                int p = (strchr(table, t[i]) - table) % 2;
                segtree[p].range_apply(0, s[i] + 1, 1);
            }
            dp[x] = max(
                segtree[0].range_concat(0, x + 1),
                segtree[1].range_concat(0, x + 1));
            REP (p, 2) {
                segtree[p].range_apply(x, x + 1, dp[x]);
            }
        }
        // output
        int y = 1;
        for (int x = 0; ; ++ y) {
            while (x < m and dp[x] < y) ++ x;
            if (x == m) break;
            printf("%d ", x + 1);
        }
        for (; y <= n; ++ y) printf("-1%c", y < n ? ' ' : '\n');
    }
    return 0;
}
