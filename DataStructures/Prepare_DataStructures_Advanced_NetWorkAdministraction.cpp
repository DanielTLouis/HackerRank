/*
Time Limits C:5, Cpp:5, C#:6, Java:8, Php:18, Ruby:20, Python:20, Perl:18, Haskell:10,
Scala:14, Javascript:20, Pascal:5
Like every IT company, the Uplink Corporation has its own network. But, unlike the rest of the
companies around the world, Uplink's network is subject to very specific restrictions:
    * Any pair of servers within the network should be directly connected by at most 1 link.
    * Each link is controlled by some specific network administrator.
    * No server has more than 2 links connected to it, that are controlled by the same
    administrator.
    * For easier management, links controlled by some administrator cannot be redundant (this
    is, removing any link will disconnect some two previously connected servers)
Notice that 2 connected servers might not have any direct link between them. Furthermore, in
order to keep the network in a secured status, Uplink directives periodically try to perform
some modifications over the network to mislead hackers. The problem is, having such a huge
network, they need a software to efficiently simulate the network status after any of such
modifications. You have been assigned to write the core section of that software.
Operations performed by the directives are:
    * Change the administrator assigned to some particular link.
    * Place some number of security devices along a particular link.
Also, given a network administrator, they would like to know how many devices are in the path
created by links controlled by that administrator (if any) between 2 servers.
Input Format
    Input begins with a line containing 4 integers S,L,A,T separated by a single whitespace,
    denoting the number of servers, links, network administrators and transformations,
    respectively. L lines follow each one with 3 integers x,y(x<y) and a_i (1<=a_i<=A), saying
    that there is a link between server x and server y, and that link is controlled by
    administrator a_i. Initially, network topology fulfills the restrictions described above
    and there is no security device along any link. Remaining T lines in the input follow one
    the next formats:
        * 1 A B a_i
    meaning that link between server A and server B(A<B)  is requested to be assigned to
    administrator a_i
        * 2 A B x
    meaning that the number of security devices along the link between server A and server
    B(A<B) will be fixed to x, removing any existing devices on this link before the
    operation. The involved link will always exist.
        * 3 A B a_i
    meaning that directives want to know the number of security devices placed along the path
    between server A and server B, just considering links controlled by administrator .
Output Format
    For each network transformation in the form 1 A B a_i you should output:
        * "Wrong link" if there is no direct link between server A and server B.
        * "Already controlled link" if the requested link does exist, but it is already
        controlled by administrator a_i.
        * "Server overload" if administrator a_i already controls 2 links connected to one of
        the involved servers.
        * "Network redundancy" if the requested assignment creates no new connection
        considering just the links controlled by a_i.
        * "Assignment done" if none of the above conditions holds. In this case, link directly
        connecting A with B is assigned to a_i.
    For each network transformation in the form 2 A B a_i you should output:
        * "No connection" if there is no path between the requested servers considering just
        the links controlled by a_i.
        * "D security devices placed" where D is the number of security devices placed so far
        on the existing connection between the requested servers considering just the links
        controlled by a_i.
Constraints
    1<=S<=10^5
    1<=L<=5X10^5
    1<=A<=10^2
    1<=T<=5X10^5
    1<=x<=2000
Sample Input:
    4 5 3 15
    1 2 1
    2 3 1
    3 4 2
    1 4 2
    1 3 3
    2 3 4 49
    1 1 2 3
    2 1 4 64
    3 1 4 2
    1 1 2 3
    3 4 2 3
    3 1 3 3
    1 1 4 3
    3 3 4 2
    3 2 4 1
    2 1 4 13
    2 1 3 21
    2 2 3 24
    1 2 3 3
    1 2 4 3
Sample Output:
    Assignment done
    64 security devices placed
    Already controlled link
    No connection
    0 security devices placed
    Server overload
    49 security devices placed
    No connection
    Network redundancy
    Wrong link
*/
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> PII;

struct Edge : PII {
    Edge(int a = 0, int b = 0, int i = 0, int l = 0){
        first = a; second = b; k = i; len = l;
    }
    int k, len;
} edge[500010];

struct Node {
    Node *fa, *ch[2];
    int sum, arc[2];
    bool rev;

    void init(){
        fa = ch[0] = ch[1] = 0;
        rev = false;
    }

    int get_sum() const {
        return this ? sum : 0;
    }
    int get_arc(int c) const {
        return ch[c] ? edge[arc[c]].len : 0;
    }

    void mark_rev(){
        if(this == 0) return;
        rev = !rev;
        swap(ch[0], ch[1]);
        swap(arc[0], arc[1]);
    }

    void push_down(){
        if(rev){
            rev = false;
            ch[0]->mark_rev();
            ch[1]->mark_rev();
        }
    }
    void update(){
        sum = ch[0]->get_sum() + get_arc(0)
            + ch[1]->get_sum() + get_arc(1);
    }

    void rotate(int c){
        Node *y = fa;
        y->ch[1 - c] = ch[c];
        if(ch[c])
            ch[c]->fa = y;
        fa = y->fa;
        if(y->fa != 0){
            if(y->fa->ch[0] == y)
                y->fa->ch[0] = this;
            else
                y->fa->ch[1] = this;
        }
        ch[c] = y;
        y->fa = this;
        y->update();
    }

    void splay(Node *f){
        push_down();
        while(fa != f){
            if(fa->fa == f){
                fa->push_down(); push_down();
                if(fa->ch[0] == this)
                    rotate(1);
                else
                    rotate(0);
            } else{
                Node *y = fa, *z = y->fa;
                z->push_down(); y->push_down(); push_down();
                if(z->ch[0] == y){
                    if(y->ch[0] == this)
                        y->rotate(1), rotate(1);
                    else
                        rotate(0), rotate(1);
                } else{
                    if(y->ch[1] == this)
                        y->rotate(0), rotate(0);
                    else
                        rotate(1), rotate(0);
                }
            }
        }
        update();
    }
} nodes[1000010], *ptr = nodes;

struct Administrator {
    int degree[100010];
    Node* mem[100010];

    Node* node(int v){
        return mem[v] ? mem[v] : (mem[v] = ptr++);
    }

    bool link(int v, int u, int p){
        node(v)->splay(0); node(u)->splay(0);
        if(node(v)->fa == 0 && node(u)->fa == 0){
            if(node(v)->ch[1]){
                node(v)->mark_rev();
                node(v)->push_down();
            }
            if(node(u)->ch[0]){
                node(u)->mark_rev();
                node(u)->push_down();
            }
            node(v)->ch[1] = node(u);
            node(v)->arc[1] = p;
            node(u)->fa = node(v);
            node(u)->arc[0] = p;
            node(v)->update();
            ++degree[v], ++degree[u];
            return true;
        } else{
            return false;
        }
    }

    void cut(int v, int u){
        node(v)->splay(0); node(u)->splay(node(v));
        if(node(v)->ch[0] == node(u)){
            node(v)->ch[0] = 0;
        } else{
            node(v)->ch[1] = 0;
        }
        node(v)->update();
        node(u)->fa = 0;
        --degree[v]; --degree[u];
    }

    int query(int v, int u){
        node(u)->splay(0); node(v)->splay(0);
        if(node(v)->fa == 0 && node(u)->fa == 0)
            return -1;
        node(u)->splay(node(v));
        if(node(v)->ch[0] == node(u))
            return node(v)->get_arc(0) + node(u)->ch[1]->get_sum()
                + node(u)->get_arc(1);
        else
            return node(u)->get_arc(0) + node(u)->ch[0]->get_sum()
                + node(v)->get_arc(1);
    }

    void modify(int v, int u){
        node(v)->splay(0); node(u)->splay(0);
    }
} admin[101];

int main(){
    int S, L, A, T;
    scanf("%d%d%d%d", &S, &L, &A, &T);
    for(int i = 0; i < L; ++i){
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        if(a > b) swap(a, b);
        edge[i] = Edge(a, b, k);
    }
    sort(edge, edge + L);
    for(int i = 0; i < L; ++i)
        admin[edge[i].k].link(edge[i].first, edge[i].second, i);
    for(int i = 0; i < T; ++i){
        int opt; scanf("%d", &opt);
        if(opt == 1){
            int a, b, k;
            scanf("%d%d%d", &a, &b, &k);
            if(a > b) swap(a, b);
            int p = lower_bound(edge, edge + L, PII(a, b)) - edge;
            if(p == L || edge[p] != PII(a, b)){
                puts("Wrong link");
            } else if(edge[p].k == k){
                puts("Already controlled link");
            } else if(admin[k].degree[a] == 2 || admin[k].degree[b] == 2){
                puts("Server overload");
            } else if(!admin[k].link(a, b, p)){
                puts("Network redundancy");
            } else{
                admin[edge[p].k].cut(a, b);
                edge[p].k = k;
                puts("Assignment done");
            }
        } else if(opt == 2){
            int a, b, x;
            scanf("%d%d%d", &a, &b, &x);
            if(a > b) swap(a, b);
            int p = lower_bound(edge, edge + L, PII(a, b)) - edge;
            edge[p].len = x;
            admin[edge[p].k].modify(a, b);
        } else{
            int a, b, k;
            scanf("%d%d%d", &a, &b, &k);
            int r = admin[k].query(a, b);
            if(r == -1){
                puts("No connection");
            } else{
                printf("%d security devices placed\n", r);
            }
        }
    }
    return 0;
}
