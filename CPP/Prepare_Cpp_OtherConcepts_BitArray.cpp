/*Problem*/
/**
You are given four integers: N, S, P, Q. You will use them in order to create the sequence a with the following pseudo-code.
a[0] = S (modulo 2^31)
for i = 1 to N-1
    a[i] = a[i-1]*P+Q (modulo 2^31)
Your task is to calculate the number of distinct integers in the sequence a.
Input Format
Four space separated integers on a single line, N, S, P, and Q respectively.
Output Format
A single integer that denotes the number of distinct integers in the sequence a.
Constraints
1<=N<=10^8
0<=S,P,Q<=2^31
Sample Input
3 1 1 1
Sample Output
3
Explanation
a=[1,2,3]
Hence, there are 3 different integers in the sequence.
**/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*Iteration one: does not work but does what the for loop says
in the problem, however, there is not enough memory to do that
for the test cases given*//*idk if this is truly right but I
think I get what is happening, the longer it goes the more
likely it will reach infinity so every number is unique
otherwise a number will be converged on to (like calculus and
finding the integral) so if it goes to long and breaks the
program it will throw an excption and that means all n elements
are unique otherwise if it converges on a number all numbers
before are unique.*/
int distinctIntegers(int n, int s, int p, int q)
{
    //if it reaches infinity all numbers are distinct return n
    //* else it may reach 0 return i
    vector<unsigned int> a;
    //rounding error casting to int results in
    try {
        a.push_back(static_cast<unsigned int>(
            s % int(pow(2,31))));

        for(int i = 1; i < n; i++)
        {
            if(static_cast<unsigned int>(a[i-1]
                * p+q % int(pow(2,31)))
                == a[i-1])
            {
                a.pop_back();
                break;
            }
            a.push_back(static_cast<unsigned int>(a[i-1]
                    * p+q % int(pow(2,31))));
        }
        sort( a.begin(), a.end() );
        a.erase( unique( a.begin(), a.end() ), a.end() );

        return a.size();
    }
    catch(...)
    {
        return n;
    }

}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N, S, P, Q;
    int sol = 0;
    cin >> N >> S >> P >> Q;
    sol = distinctIntegers(N, S, P, Q);
    cout << sol << endl;
    return 0;
}
