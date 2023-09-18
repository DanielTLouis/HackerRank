/*
You are given an integer n. A set, S, of triples (xi,yi,zi) is beautiful if and only if:
    * 0<=xi,yi,zi
    * xi+yi+zi=, upsidown(A)i:1<=i<=|S|
    * Let X be the set of different xi's in S, Y be the set of different yi's in S, and Z be the
    set of different zi in S. Then |X|=|Y|=|Z|=|S|.
The third condition means that all xi's are pairwise distinct. The same goes for yi and zi.
Given n, find any beautiful set having a maximum number of elements. Then print the cardinality*
of S(i.e., |S|) on a new line, followed by |S| lines where each line contains 3 space-separated
integers describing the respective values of xi, yi, and zi.
* https://en.wikipedia.org/wiki/Cardinality *
Input Format
    A single integer, n.
Constraints
    1<=n<=300
Output Format
    On the first line, print the cardinality of S(i.e., |S|).
    For each of the |S| subsequent lines, print three space-separated numbers per line describing
    the respective values of xi, yi, and zi for triple i in S.
Sample Input
    3
Sample Output
    3
    0 1 2
    2 0 1
    1 2 0
Explanation
    In this case, n=3. We need to construct a set, S, of non-negative integer triples (xi,yi,zi)
    where xi+yi+zi=n. S has the following triples:
        1.(x1,y1,z1)=(0,1,2)
        2.(x2,y2,z2)=(2,0,1)
        3.(x3,y3,z3)=(1,2,0)
    We then print the cardinality of this set, |S|=3, on a new line, followed by 3 lines where
    each line contains three space-separated values describing a triple in S.
*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <tuple>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n =0;
    cin >> n;
    int c = 2*n/3 + 1;
    std::cout << c << '\n';

    // x goes from 0 to floor(2n/3)
    // y goes from 0 or 1 to ceil(2n/3)
    for ( int x = 0, y = n/3 + n%3; x < c; ++ x, ++ y ) {
        // When resetting y, change parity of z
        if ( x + y > n ) y = (y+1) % 2;
        std::cout << x << ' ' << y << ' ' << n - (x+y) << '\n';
    }
    /*
    vector<tuple<int,int,int>> s;
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            for(int z = 0; z < n; z++){
                if(x + y + z == n && x != y && z != x && y != z){
                    s.push_back(make_tuple(x,y,z));
                }
            }
        }
    }
    cout << s.size() << endl;
    for(int i = 0; i < s.size(); i++){
        cout << get<0>(s[i]) << " " << get<1>(s[i]) << " " << get<2>(s[i]) << endl;
    }
    */
    return 0;
}
