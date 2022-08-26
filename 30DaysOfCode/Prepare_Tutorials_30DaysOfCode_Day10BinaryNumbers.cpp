/*Problem*/
/**
Objective
    Today, we're working with binary numbers. Check out the Tutorial      tab for learning materials and an instructional video! https://       www.hackerrank.com/challenges/30-binary-numbers/tutorial
Task
    Given a base-10 integer, n, convert it to binary (base-2).            Then find and print the base-10 integer denoting the maximum          number of consecutive 1's in n's binary representation. When          working with different bases, it is common to show the base as a      subscript.
Example
    n=125
    The binary representation of 125_10 is 1111101_2. In base 10,         there are 5 and 1 consecutive ones in two groups. Print the           maximum, 5.
Input Format
    A single integer, n.
Constraints
    1<=n<=10^6
Output Format
    Print a single base- integer that denotes the maximum number of       consecutive 's in the binary representation of .
Sample Input 1
    5
Sample Output 1
    1
Sample Input 2
    13
Sample Output 2
    2
Explanation
    Sample Case 1:
        The binary representation of 5_10 is 101_2, so the maximum            number of consecutive 1's is 1.
    Sample Case 2:
        The binary representation of 13_10 is 1101_2, so the maximum          number of consecutive 1's is 2.
**/
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));
    //bitset<8> the 8 stands for how many chars there will be
    //*the problem has a int that is 19 chars long
    string binary = bitset<20>(n).to_string(); //to binary
    int count = 0, high = 0;
    for(int i = 0; i <= binary.length(); i++)
    {
        if(binary[i]==*"1")
        {
            count +=1;
            if (count > high)
            {
                high = count;
            }
        }
        else
        {
            count = 0;
        }
    }
    cout << high;
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
