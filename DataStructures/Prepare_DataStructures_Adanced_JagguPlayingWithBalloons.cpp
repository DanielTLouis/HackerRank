/*
Jaggu is a little kid and he likes playing with water balloons. He took 1 million ( 106 )
empty buckets and he filled the bucket with water balloons under the instruction of his sister
Ishika.
His sister gives him two types of commands:
R pos1 pos2 which implies that jaggu needs to tell her what is the total number of water
balloons in the bucket from pos1 to pos2 (both included).
U pos M plus which implies that he has to work like the function
Update(pos,M,plus)
        void Update(int pos,int M,int plus)
        {
            int N=1000000;  //1 million
            for (int i=1;i<=50;i++)
            {
                int back = pos
                for(int j=1;j<=1000;j++)
                {
                    add M water ballons at bucket pos
                    int s,in=__builtin_popcount(pos);
                    for(int k=0;;k++)
                    {
                        s=pos+pow(2,k)
                        if( __builtin_popcount(s) <= in )
                        {
                            in = __builtin_popcount(s)
                            pos = s;
                            if(pos>N)       break;
                            add M water ballons at bucket pos
                        }
                    }
                    pos = pos - N
                }
                pos = back+plus;
                if(pos>N) pos-=N;
            }
        }
Jaggu is too lazy to put the water ballons in the bucket. Afraid that he might be caught for
not doing what his sister told him to do so, he asks your help to provide correct answers for
each of his sister's query. .
Input Format
    First line contains Q, number of queries to follow.
    Next Q line follows , which can be either an Update Query or Report Query.Each Update
    Query is followed by atleast 1 report query.
Output Format
    For each report query , output the answer in a separate line.
Constraints
    1 ≤ Q ≤ 2 * 105
    1 ≤ pos1,pos2,pos ≤ 106
    pos1 ≤ pos2
    1 ≤ M ≤ 10
    1 ≤ plus ≤ 999999
Sample Input
    2
    U 692778 7 291188
    R 636916 747794
Sample Output
    378
Explanation
    Follow the code above to get the answer.
Note
        1. Input is randomly generated.
        2. __builtin_popcount(x) gives the number of set bits in binary representation of x.
        3. pow(2,k) denotes 2 raised to k , i.e. exponentiation of 2.
    Timelimit is 3 times the timelimit mentioned here
*/

#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for(int i = a; i < b; i++)
#define S(x) scanf("%d", &x)
#define P(x) printf("%d\n", x)

typedef long long int LL;

int X[7] = {48576, 48640, 49152, 65536, 131072, 262144, 524288};
const int MAXN = 1000001;
LL BIT[MAXN];
LL val;

void update(int idx, int val){
    for(int i = idx; i < MAXN; i += i &-i) BIT[i] += val;
}

LL query(int idx){
    LL res = 0;
    for(int i = idx; i; i -= i & -i) res += BIT[i];
    return res;
}

void UUU(int pos, int M, int plus){
    rep(i, 0, 50) {
        int x = pos;
        int cnt = 999;
        while(x < MAXN){
            update(x, M);
            x += x & -x;
            if(x > MAXN && x != 1048576) {
                x -= MAXN - 1;
                cnt--;
            }
        }
        val += cnt * M;
        pos += plus;
        if(pos > 1000000) pos -= 1000000;
    }
}

int main(){
    int Q; S(Q);
    while(Q--){
        string s; cin >> s;
        if(s == "U"){
            int pos, M, plus;
            scanf("%d%d%d", &pos, &M, &plus);
            UUU(pos, M, plus);
        } else{
            int pos1, pos2;
            if(val) rep(i,0,7) update(X[i], val);
            scanf("%d%d", &pos1, &pos2);
            printf("%lld\n", query(pos2) - query(pos1 - 1));
            val = 0;
        }
    }
    return 0;
}
