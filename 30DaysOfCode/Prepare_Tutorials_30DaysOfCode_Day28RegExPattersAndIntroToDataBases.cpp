/*Problem*/
/**
Objective
    Today, we're working with regular expressions. Check out the Tutorial tab for
    learning materials and an instructional video!
    * https://www.hackerrank.com/challenges/30-regex-patterns/tutorial *
Task
    Consider a database table, Emails, which has the attributes First Name and
    Email ID. Given N rows of data simulating the Emails table, print an
    alphabetically-ordered list of people whose email address ends in @gmail.com.
Input Format
    The first line contains an integer, N, total number of rows in the table.
    Each of the N subsequent lines contains 2 space-separated strings denoting a
    person's first name and email ID, respectively.
Constraints
    2<=N<=30
    Each of the first names consists of lower case letters [a-z] only.
    Each of the email IDs consists of lower case letters [a-z], @ and . only.
    The length of the first name is no longer than 20.
    The length of the email ID is no longer than 50.
Output Format
    Print an alphabetically-ordered list of first names for every user with a
    gmail account. Each name must be printed on a new line.
Sample Input
    6
    riya riya@gmail.com
    julia julia@julia.me
    julia sjulia@gmail.com
    julia julia@gmail.com
    samantha samantha@gmail.com
    tanya tanya@gmail.com
Sample Output
    julia
    julia
    riya
    samantha
    tanya
**/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

bool isItGmail(string s)
{
    string temp = s.substr(s.find("@"));
    string gmail = "@gmail.com";

    for(int i = 0; i < temp.size(); i++)
    {
        if(temp[i] != gmail[i])
        {
            return false;
        }
    }
    return true;

}

int main()
{
    string N_temp;
    getline(cin, N_temp);

    int N = stoi(ltrim(rtrim(N_temp)));
    vector<string> names;

    for (int N_itr = 0; N_itr < N; N_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        string firstName = first_multiple_input[0];

        string emailID = first_multiple_input[1];

        if(isItGmail(emailID))
        {
            names.push_back(firstName);
        }
    }
    sort(names.begin(), names.end());
    for(int i = 0; i < names.size(); i++)
    {
        cout << names[i] << endl;
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
