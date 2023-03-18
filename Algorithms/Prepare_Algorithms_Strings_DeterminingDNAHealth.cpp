/*
DNA* is a nucleic acid present in the bodies of living things. Each piece of DNA
contains a number of genes, some of which are beneficial and increase the DNA's total
health. Each gene has a health value, and the total health of a DNA is the sum of the
health values of all the beneficial genes that occur as a substring in the DNA. We
represent genes and DNA as non-empty strings of lowercase English alphabetic letters,
and the same gene may appear multiple times as a susbtring of a DNA.
* https://en.wikipedia.org/wiki/DNA *
Given the following:
    -An array of beneficial gene strings, genes=[g_0,g_1,...,g_n-1]. Note that these
    gene sequences are not guaranteed to be distinct.
    -An array of gene health values, health=[h_0,h_1,...,h_n-1], where each h_i is the
    health value for gene g_i.
    -A set of s DNA strands where the definition of each strand has three components,
    start, end, and d, where string d is a DNA for which genes g_start,...,g_end are
    healthy.
Find and print the respective total healths of the unhealthiest (minimum total health)
and healthiest (maximum total health) strands of DNA as two space-separated values on a
single line.
Input Format
    The first line contains an integer, n, denoting the total number of genes.
    The second line contains n space-separated strings describing the respective values
    of g_0,g_1,...,g_n-1 (i.e., the elements of genes).
    The third line contains n space-separated integers describing the respective values
    of h_0,h_1,...,h_n-1 (i.e., the elements of health).
    The fourth line contains an integer, , denoting the number of strands of DNA to
    process.
    Each of the  subsequent lines describes a DNA strand in the form start end d,
    denoting that the healthy genes for DNA strand d are g_start,...,g_end and their
    respective correlated health values are h_start,...,h_end.
Constraints
    1<=n,s<=10^5
    0<=h_i<=10^7
    0<=first<=last<n
    1<=the sum of the lengths of all genes and DNA strands<=2X10^6
    It is guaranteed that each g_i consists of lowercase English alphabetic letters only
    (i.e., a to z).
Output Format
    Print two space-separated integers describing the respective total health of the
    unhealthiest and the healthiest strands of DNA.
Sample Input 0
    6
    a b c aa d b
    1 2 3 4 5 6
    3
    1 5 caaab
    0 4 xyz
    2 4 bcdybc
Sample Output 0
    0 19
Explanation 0
    In the diagrams below, the ranges of beneficial genes for a specific DNA on the left
    are highlighed in green and individual instances of beneficial genes on the right
    are bolded. The total healths of the s=3 strands are:
    1.
        image
        The total health of caaab is 3+4+4+2+6=19
    2..
        image
        The total health of xyz is 0, because it contains no beneficial genes.
    3.
        image
        The total health of bcdybc is 3+5+3=11.
    The unhealthiest DNA strand is xyz with a total health of 0, and the healthiest DNA
    strand is caaab with a total health of 19. Thus, we print 0 19 as our answer.
*/

#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<string.h>
using namespace std;

typedef long long LL;
typedef vector<int> VI;

#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(),i##_end=(c).end();i!=i##_end;++i)
#define eprintf(...) fprintf(stderr, __VA_ARGS__)

template<class T> inline void amin(T &x, const T &y) { if (y<x) x=y; }
template<class T> inline void amax(T &x, const T &y) { if (x<y) x=y; }
template<class Iter> void rprintf(const char *fmt, Iter begin, Iter end) {
    for (bool sp=0; begin!=end; ++begin) { if (sp) putchar(' '); else sp = true; printf(fmt, *begin); }
    putchar('\n');
}
struct PMA {
    struct Node {
    Node *ch, *sib, *fail;
    char c;
    LL cnt;
        Node() : ch(0), sib(0), fail(0), c(0), cnt(0) { }

    struct Iter {
        Node *x;
        Iter(Node *x_) : x(x_) {}
        operator Node*() { return x; }
        Node *operator->() { return x; }
        void operator++() { x = x->sib; }
        bool operator!=(const Iter & y) const { return x != y.x; }
        bool operator==(const Iter & y) const { return x == y.x; }
    };
    Iter begin() { return ch; }
    Iter end() { return NULL; }
    };

    Node *root, *nodes;
    int nodes_i;

    PMA() { }

    PMA(const vector<string> &d, const vector<int> &g) {
    int len = 0;
    REP (i, d.size()) len += d[i].size();
    len++;
    nodes_i = 0;
    nodes = new Node[len];
    root = new_node();

    // Trie
    REP (i, d.size()) {
        Node *x = root;
        const string &s = d[i];
        REP (j, s.size()) x = get_child(x, s[j], true);
        x->cnt += g[i];
    }

    vector<Node*> ord; ord.reserve(nodes_i);
    ord.push_back(root);
    for (int i=0; i<nodes_i; i++) {
        Node *x = ord[i];
        EACH (ch, *x) ord.push_back(ch);
    }

    root->fail = root; // ord[0]
    EACH (x, *root) x->fail = root;

    for (int i=1; i<nodes_i; i++) {
        Node *x = ord[i];
        EACH (ch, *x) {
        Node *f = x->fail, *y;
        while (!(y=get_child(f, ch->c)) && f != root) f = f->fail;
        ch->fail = y ?: root;
        }
    }

    REP (i, nodes_i) ord[i]->cnt += ord[i]->fail->cnt;
    }

    Node *new_node() {
    return &nodes[nodes_i++];
    }

    Node *get_child(Node *x, char c, bool create=false) { // assert(x != NULL);
    if (!x->ch) {
        if (create) {
        x->ch = new_node();
        x->ch->c = c;
        }
        return x->ch;
    } else {
        EACH (ch, *x) {
        if (ch->c == c) return ch;
        if (create && !ch->sib) {
            ch->sib = new_node();
            ch->sib->c = c;
            return ch->sib;
        }
        }
        return NULL;
    }
    }

    LL match(const string &s) {
    Node *x = root;
    LL ret = 0;
    REP (i, s.size()) {
        Node *y = NULL;
        while (!(y=get_child(x, s[i])) && x != root) x = x->fail;
        x = y ?: root;
        ret += x->cnt;
    }
    return ret;
    }

    void clear() {
    delete[] nodes;
    root = nodes = NULL;
    nodes_i = 0;
    }
};

int N;
char buf[2000111];
string S[100111];
int H[100111];
int Q;
string W[100111];
LL ans[100111];

const int MAXN = 1<<17;
VI ids[1<<18];
int L, R, id;
void add(int l, int r, int k) {
    if (L <= l && r <= R) {
    ids[k].push_back(id);
    } else if (R <= l || r <= L) {
    } else {
    add(l, (l+r)/2, k+k);
    add((l+r)/2, r, k+k+1);
    }
}
void calc(int l, int r, int k) {
    if (k < 2 * MAXN) {
    if (ids[k].size()) {
        PMA pma(vector<string>(S+l, S+r), VI(H+l, H+r));
        EACH (e, ids[k]) {

        ans[*e] += pma.match(W[*e]);
        }
        pma.clear();
    }
    calc(l, (l+r)/2, k+k);
    calc((l+r)/2, r, k+k+1);
    }
}

int main() {
    scanf("%d", &N);
    REP (i, N) {
    scanf("%s", buf);
    S[i] = buf;
    }
    REP (i, N) scanf("%d", H+i);
    scanf("%d", &Q);
    REP (i, Q) {
    scanf("%d%d%s", &L, &R, buf);
    R++;
    id = i;
    W[i] = buf;
    add(0, MAXN, 1);
    }
    calc(0, MAXN, 1);
    auto p = minmax_element(ans, ans + Q);

    printf("%lld %lld\n", *p.first, *p.second);

    return 0;
}
