/*
Sherlock Holmes suspects his archenemy Professor Moriarty is once again plotting
something diabolical. Sherlock's companion, Dr. Watson, suggests Moriarty may be
responsible for MI6's recent issues with their supercomputer, The Beast.
Shortly after resolving to investigate, Sherlock receives a note from Moriarty
boasting about infecting The Beast with a virus. He also gives him a clue: an
integer. Sherlock determines the key to removing the virus is to find the largest
Decent Number having that number of digits.
A Decent Number has the following properties:
    1.Its digits can only be 3's and/or 5's.
    2.The number of 3's it contains is divisible by 5.
    3.The number of 5's it contains is divisible by 3.
    4.It is the largest such number for its length.
Moriarty's virus shows a clock counting down to The Beast's destruction, and time
is running out fast. Your task is to help Sherlock find the key before The Beast
is destroyed!
For example, the numbers 55533333 and 555555 are both decent numbers because there
are 3 5's and 5 3's in the first, and 6 5's in the second. They are the largest
values for those length numbers that have proper divisibility of digit occurrences.
Function Description
    Complete the decentNumber function in the editor below.
    decentNumber has the following parameter(s):
        int n: the length of the decent number to create
Prints
    Print the decent number for the given length, or -1 if a decent number of that
    length cannot be formed. No return value is expected.
Input Format
    The first line is an integer, t, the number of test cases.
    The next t lines each contain an integer n, the number of digits in the number
    to create.
Constraints
    1<=t<=20
    1<=n<=1000000
Sample Input
    STDIN   Function
    -----   --------
    4       t = 4
    1       n = 1 (first test case)
    3       n = 3 (second test case)
    5
    11
Sample Output
    -1
    555
    33333
    55555533333
Explanation
    For n=1, there is no Decent Number having 1 digit, so print -1.
    For n=3, 555 is the only possible number. (Decent Number Property 3).
    For n=5, 33333 is the only possible number. (Decent Number Property 2).
    For n=11, 55555533333 is the Decent Number. All other permutations of these
    digits are not decent (Decent Number Property 4).
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'decentNumber' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

void decentNumber(int n) {
    /*if(n < 3 || n % 2 == 0)
    {
        cout << -1<<endl;
        return;
    }
    else if(n % 3 == 0)
    {
        string s = string(n, '5');
        cout << s << endl;
        return;
    }
    else if(n % 5 == 0){
        string s = string(n, '3');
        cout << s << endl;
        return;
    }
    else
    {
        if((n - 5) % 3 == 0)
        {
            cout << string(n-5, '5') << string(5,'3') << endl;
        }
        else if( (n - 3) % 5 == 0)
        {
            cout << string(3,'5') << string(n-3,'3') << endl;
        }
        else {
            cout << -1 << endl;
        }
        return;
    }
    return;
    */
    int y = 0;
    for (; n - 5 * y >= 0; y++)
    {
        if ((n - 5 * y) % 3 == 0)
            break;
    }
    int a = n - 5 * y;
    int b = 5 * y;
    if (a >= 0)
    {
        for (int i = 0; i < a; i++)
            cout << 5;
        for (int i = 0; i < b; i++)
            cout << 3;
        cout << "\n";
    }
    else{
        cout << -1 << "\n";
    }
}

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        decentNumber(n);
    }

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
