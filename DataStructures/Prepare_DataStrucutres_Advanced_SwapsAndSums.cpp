/*
You are given a sequence a_1,a_2,...,a_n. The task is to perform the following queries on it:
Type 1. Given two integers l and r (1<=l<=r<=n; r-l+1 is even). Reorder the elements of the
sequence in such a way (changed part of the sequence is in brackets):
    a_1,a_2,...,a_n -> a1_a2,...,a_(l-2),a_(l-1),[a_(l+1),a_l,a_(l+3),a_(l+2),...a_r,a_(r-1)],
    a_(r+1),a_(r+2)
That is swap the first two elements of segment [l,r], the second two elements, and so on.
Type 2. Given two integers l and r, print the value of sum sumation(a_i)from(i=l to r).
Input Format
    The first line contains two integers n and q. The second line contains n integers
    a_1,a_2,...,a_n, denoting initial sequence.
    Each of the next q lines contains three integers tp_i,l_i,r_i, where tp_i denotes the type
    of the query, and l_i,r_i are parameters of the query. It's guaranteed that for a
    first-type query (r-l+1) will be even.
Constraints
    2<=n<=2X10^5
    1<=q<=2X10^5
    1<=a_i<=10^6
    1<=tp_i<=2
    1<=l_i<=r_i<=n
Output Format
    For each query of the second type print the required sum.
Sample Input
    6 4
    1 2 3 4 5 6
    1 2 5
    2 2 3
    2 3 4
    2 4 5
Example Output
    5
    7
    9
Explanation
    After the first query the sequence becomes [1, 3, 2, 5, 4, 6].
*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cassert>
#include <chrono>
#include <map>
#include <set>
#include <vector>
#include <complex>
#include <queue>
#include <tuple>

using namespace std;
typedef long long ll;

struct Tree {
    using D = ll;
    struct Node;
    using NP = Node*;
    static Node last_d;
    static NP last;
    struct Node {
        NP p, l, r;
        int sz;
        D v, sm;
        Node(D v) :p(nullptr), l(last), r(last), sz(1), v(v), sm(v) {}
        Node() : l(nullptr), r(nullptr), sz(0), v(0), sm(0) {}
        inline int pos() {
            if (p) {
                if (p->l == this) return -1;
                if (p->r == this) return 1;
            }
            return 0;
        }
        void rot() {
            NP qq = p->p;
            int pps = p->pos();
            if (p->l == this) {
                p->l = r; r->p = p;
                r = p; p->p = this;
            } else {
                p->r = l; l->p = p;
                l = p; p->p = this;
            }
            p->update(); update();
            p = qq;
            if (!pps) return;
            if (pps == -1) {
                qq->l = this;
            } else {
                qq->r = this;
            }
            qq->update();
        }
        void splay() {
            assert(this != last);
            supush();
            int ps;
            while ((ps = pos())) {
                int pps = p->pos();
                if (!pps) {
                    rot();
                } else if (ps == pps) {
                    p->rot(); rot();
                } else {
                    rot(); rot();
                }
            }
        }
        NP splay(int k) {
            assert(this != last);
            assert(0 <= k && k < sz);
            if (k < l->sz) {
                return l->splay(k);
            } else if (k == l->sz) {
                splay();
                return this;
            } else {
                return r->splay(k-(l->sz+1));
            }
        }
        void supush() {
            if (pos()) {
                p->supush();
            }
            push();
        }
        //pushpush""
        void push() {
            assert(sz);
        }
        NP update() {
            assert(this != last);
            sz = 1+l->sz+r->sz;
            sm = v;
            if (l->sz) {
                sm += l->sm;
            }
            if (r->sz) {
                sm += r->sm;
            }
            return this;
        }
    } *n;
    static NP merge(NP l, NP r) {
        if (r == last) {
            return l;
        }
        r = r->splay(0);
        assert(r->l == last);
        r->l = l;
        l->p = r;
        return r->update();
    }
    static pair<NP, NP> split(NP x, int k) {
        assert(0 <= k && k <= x->sz);
        if (k == x->sz) {
            return {x, last};
        }
        x = x->splay(k);
        NP l = x->l;
        l->p = nullptr;
        x->l = last;
        return {l, x->update()};
    }
    static NP built(int sz, ll d[]) {
        if (!sz) return last;
        int md = sz/2;
        NP x = new Node(d[md]);
        x->l = built(md, d);
        x->l->p = x;
        x->r = built(sz-(md+1), d+(md+1));
        x->r->p = x;
        return x->update();
    }
    Tree() : n(last) {}
    Tree(NP n) : n(n) {}
    Tree(int sz, D d[]) {
        n = built(sz, d);
    }
    int sz() {
        return n->sz;
    }
    void insert(int k, D v) {
        auto u = split(n, k);
        n = merge(merge(u.first, new Node(v)), u.second);
    }
    void erase(int k) {
        auto u = split(n, k);
        n = merge(u.first, split(u.second, 1).second);
    }
    void merge(Tree t) {
        n = merge(n, t.n);
    }
    Tree split(int l) {
        auto a = split(n, l);
        n = a.first;
        return Tree(a.second);
    }
    D get(int l) {
        auto a = split(n, l);
        auto b = split(a.second, 1);
        D res = b.first->v;
        n = merge(merge(a.first, b.first), b.second);
        return res;
    }
    D sum(int l, int r) {
        auto b = split(n, r);
        auto a = split(b.first, l);
        D res = a.second->sm;
        n = merge(merge(a.first, a.second), b.second);
        return res;
    }
};
Tree::Node Tree::last_d = Tree::Node();
Tree::NP Tree::last = &last_d;

const int MN = 100100;
ll a[2][MN];
Tree tr[2];
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i%2][i/2]);
    }
    tr[0] = Tree((n+1)/2, a[0]);
    tr[1] = Tree(n/2, a[1]);
    for (int qc = 0; qc < q; qc++) {
        int t; ll l, r;
        scanf("%d %lld %lld", &t, &l, &r); l--;
        if (t == 1) {
            Tree x[2], y[2];
            x[1] = tr[0].split((r+1)/2);
            x[0] = tr[0].split((l+1)/2);
            y[1] = tr[1].split(r/2);
            y[0] = tr[1].split(l/2);
            tr[0].merge(y[0]);
            tr[0].merge(x[1]);
            tr[1].merge(x[0]);
            tr[1].merge(y[1]);
        } else {
            printf("%lld\n", tr[0].sum((l+1)/2, (r+1)/2) + tr[1].sum(l/2, r/2));
        }
    }
    return 0;
}
