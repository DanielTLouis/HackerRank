/*
Given an integer , find each  such that:
    0<=x<=n
    n+x=n^x
where  denotes the bitwise XOR* operator. Return the number of 's satisfying the criteria.
* https://en.wikipedia.org/wiki/Bitwise_operation#XOR *
Example
    n=4
    There are four values that meet the criteria:
        4+0=4^0=4
        4+1=4^1=5
        4+2=4^2=6
        4+3=4^3=7
    Return 4.
Function Description
    Complete the sumXor function in the editor below.
    sumXor has the following parameter(s):
        - int n: an integer
Returns
    - int: the number of values found
Input Format
    A single integer, n.
Constraints
    0<=n<=10^15
Subtasks
    0<=n<=100 for 60% of the maximum score.
Output Format
Sample Input 0
    5
Sample Output 0
    2
Explanation 0
    For n=5, the x values 0 and 2 satisfy the conditions:
        5+0=5, 5^0=5
        5+2=7, 5^2=7
Sample Input 1
    10
Sample Output 1
    4
Explanation 1
    For n=10, the x values 0, 1, 4, and 5 satisfy the conditions:
        10+0=10, 10^0=10
        10+1=11, 10^1=11
        10+4=14, 10^4=14
        10+5=15, 10^5=15
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'sumXor' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts LONG_INTEGER n as parameter.
 */

long sumXor(long n)
{
    /*
    //takes to long
    int count = 0;
    for(long i = 0; i <= n; i++)
    {
        if((n+i) == (n^i))
        {
            count++;
        }
    }
    return count;
    */

    // So, consider this number as a binary string:
    // i.e. 1001000110100
    // All of the numbers that will satisfy the
    // condition, is any number that has zeros
    // where the ones are in the string.

    // You can see that this is the case
    // if you consider a single bit.
    // In the case of 1:
    //   1 + 1 = 10 while 1 + 0 = 1
    //   1 ^ 1 = 0 while 1 ^ 0 = 1.
    //   So, in the case of one as operand,
    //   you get the same value, only when
    //   you add / xor 0 to it.
    // In the case of 0:
    //   0 + 0 = 0 while 0 + 1 = 1
    //   0 ^ 0 = 0 while 0 ^ 1 = 1
    //   So in the case of zero as operand,
    //   you get the same value when you
    //   add / xor either value (0 or 1) to it

    // So the numbers that will work with
    // 1001000110100 are:
    // 0**0***00*0**
    // where * can be either a zero or a one.

    // To calculate the number of permutations:
    // Take the number of options (zero or one, so two)
    // to the power of the number of times that option
    // can be taken, which is the number of zeros in the
    // binary string of the original number, n.

    // The exception here is zero, which has one option
    if (n == 0) return 1;

    //long int can have a lot more than 8 char spaces or bits (8 byts = 32 bits)
    //*I padded by doubling it
    string binary = std::bitset<64>(n).to_string();
    long zeros = 0;
    bool foundOne = false;
    for(int i = 0; i < binary.length(); i++)
    {
        if(binary[i] == '1')
        {
            foundOne = true;
        }
        if(binary[i] == '0' && foundOne)
        {
            zeros += 1;
        }
    }
    return static_cast<long>(pow(2, zeros));
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    long n = stol(ltrim(rtrim(n_temp)));

    long result = sumXor(n);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
