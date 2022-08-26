/*
Given an array of integers, where all elements but one occur twice, find the unique
element.
Example
    a=[1,2,3,4,3,2,1]
    The unique element is 4.
Function Description
    Complete the lonelyinteger function in the editor below.
    lonelyinteger has the following parameter(s):
        -int a[n]: an array of integers
Returns
    int: the element that occurs only once
Input Format
    The first line contains a single integer, , the number of integers in the array.
    The second line contains  space-separated integers that describe the values in .
Constraints
    1<=n<100
    It is guaranteed that  is an odd number and that there is one unique element.
    0<=a[i]<=100, where 0<=i<n.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'lonelyinteger' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

int lonelyinteger(vector<int> a) {
    int ans = 0;
    bool doubleFound = false;
    for(int i = 0; i < a.size(); i++)
    {
        doubleFound = false;
        for(int j = 0; j < a.size(); j++)
        {
            ans = a[i];
            if(a[j] == a[i] && i != j)
            {
                doubleFound = true;
            }
        }
        if(!doubleFound)
        {
            break;
        }
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    int result = lonelyinteger(a);

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
