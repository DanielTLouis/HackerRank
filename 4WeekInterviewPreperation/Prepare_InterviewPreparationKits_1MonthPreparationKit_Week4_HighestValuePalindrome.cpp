/*
Palindromes are strings that read the same from the left or right, for example madam
or 0110.
You will be given a string representation of a number and a maximum number of changes
you can make. Alter the string, one digit at a time, to create the string
representation of the largest number possible given the limit to the number of
changes. The length of the string may not be altered, so you must consider 0's left of
all higher digits in your tests. For example 0110 is valid, 0011 is not.
Given a string representing the starting number, and a maximum number of changes
allowed, create the largest palindromic string of digits possible or the string '-1'
if it is not possible to create a palindrome under the contstraints.
Example
    s='1231'
    k=3
    Make 3 replacements to get '9339'.
    s='12321'
    k=1
    Make 1 replacement to get '12921'.
Function Description
    Complete the highestValuePalindrome function in the editor below.
    highestValuePalindrome has the following parameter(s):
    string s: a string representation of an integer
        -int n: the length of the integer string
        -int k: the maximum number of changes allowed
Returns
    string: a string representation of the highest value achievable or -1
Input Format
    The first line contains two space-separated integers, n and k, the number of
    digits in the number and the maximum number of changes allowed.
    The second line contains an -digit string of numbers.
Constraints
    0<n<=10^5
    0<=k<=10^5
    Each character i in the number is an integer where 0<=i<=9.
Output Format
    Sample Input 0
    STDIN   Function
    -----   --------
    4 1     n = 4, k = 1
    3943    s = '3943'
Sample Output 0
    3993
Sample Input 1
    6 3
    092282
Sample Output 1
    992299
Sample Input 2
    4 1
    0011
Sample Output 2
    -1
Explanation
    Sample 0
    There are two ways to make 3943 a palindrome by changing no more than k=1 digits:
        1.3943 -> 3443
        2.3943-> 3993
    3993 > 3443
*/
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'highestValuePalindrome' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER n
 *  3. INTEGER k
 */

string highestValuePalindrome(string s, int n, int k) {
    //first make k or less changes to see if it can be palindrom
    //then sort to decending order
    //*assuming this is what it means and not making k changes doesnt matter in this part
    //change all to be same and if any extra ks make the highest ones 9
    /*
    int moves = 0;
    cout << "Start: " << s << " " << n << " " << k << endl;
    for(int i = 0; i < n; i++)
    {
        if(moves > k)
        {
            s="-1";
            return s;
        }
        if(s[i] < s[s.length()-1-i])
        {
            s[i] = s[s.length()-1-i];
            moves += 1;
        }
        else if(s[i] > s[s.length()-1-i])
        {
            s[s.length()-1-i] = s[i];
            moves += 1;
        }
        cout <<"1 "<< s << " " << moves<< endl;
    }
    if(moves < k)
    {
        int i = 0;
        if(moves % 2 != 0)
        {
            moves -= 1;
        }
        while(moves < k)
        {
            if(s[i] != '9')
            {
                s[i] = '9';
                s[s.length()-i-1] = '9';
                moves += 2;
            }
            i++;
            cout <<"2 " << s << " " << moves<< endl;
        }
    }
    return s;
    */

    bool changed[s.length()] = {false};

    int a = 0, b = n-1;
    while (a < b) {
        if (s[a] != s[b]) {
            if (k == 0) return "-1";
            k--;
            if (s[a] > s[b]) {
                s[b] = s[a], changed[b] = true;
            } else {
                s[a] = s[b], changed[a] = true;
            }
        }
        a++, b--;
    }

    a = 0, b = n-1;
    while (a <= b && k > 0) {
        if (s[a] == '9') {
        } else if (a == b) {
            k--, s[a] = '9';
        } else if (changed[a] || changed[b]) {
            k--, s[a] = '9', s[b] = '9';
        } else if (k >= 2) {
            k -= 2, s[a] = '9', s[b] = '9';
        }
        a++, b--;
    }

    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

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

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
