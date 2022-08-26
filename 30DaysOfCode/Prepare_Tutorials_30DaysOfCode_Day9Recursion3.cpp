/*Problem*/
/**
Objective
    Today, we are learning about an algorithmic concept called           recursion. Check out the Tutorial tab for learning materials and     an instructional video.
Recursive Method for Calculating Factorial
    factorial(n) = { N X factorial(N-1) N<=1 otherwise }
Function Description
    Complete the factorial function in the editor below. Be sure to      use recursion.
    factorial has the following paramter:
    int n: an integer
Returns
    int: the factorial of n
    Note: If you fail to use recursion or fail to name your              recursive   function factorial or Factorial, you will get a          score of 0.
Input Format
    A single integer, n(the argument to pass to factorial).
Constraints
    2<=n<=12
    Your submission must contain a recursive function named              factorial.
Sample Input
    3
Sample Output
    6
Explanation
    Consider the following steps. After the recursive calls from         step 1 to 3, results are accumulated from step 3 to 1.
        1.factorial(3) = 3 X factorial(2) = 3X2=6
        2.factorial(2) = 2 X factorial(1) = 2X1=2
        3.factorial(1)=1
**/
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'factorial' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */

int factorial(int n) {
    if(n > 0)
    {
        return n * factorial(n-1);
    }
    else
    {
        return 1;
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    int result = factorial(n);

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
