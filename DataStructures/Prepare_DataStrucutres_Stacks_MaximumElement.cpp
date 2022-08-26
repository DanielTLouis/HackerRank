/*
You have an empty sequence, and you will be given N queries. Each query is one of
these three types:
    1 x  -Push the element x into the stack.
    2    -Delete the element present at the top of the stack.
    3    -Print the maximum element in the stack.
Function Description
    Complete the getMax function in the editor below.
    getMax has the following parameters:
        - string operations[n]: operations as strings
Returns
    - int[]: the answers to each type 3 query
Input Format
    The first line of input contains an integer, n. The next  lines each contain an
    above mentioned query.
Constraints
Constraints
    1<=n<=10^5
    1<=x<=20^9
    1<=type<=3
    All queries are valid.
Sample Input
    STDIN   Function
    -----   --------
    10      operations[] size n = 10
    1 97    operations = ['1 97', '2', '1 20', ....]
    2
    1 20
    2
    1 26
    1 20
    2
    3
    1 91
    3
Sample Output
    26
    91
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'getMax' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY operations as parameter.
 */
vector<int> getMax(vector<string> operations) {
    vector<int> ans;
    stack<int> s;
    int n=0, i=0, k=0;
    string j;
    n = operations.size();
    while(n--)
    {
        j = operations[i];
        if(j[0] == '1')
        {
            string si = operations[i].substr(2,operations.size());
            k = stoi(si);
            s.push(max(k, s.size()>0 ? s.top():k));
        }
        else if(j[0] == '2')
            s.pop();
        else if(j[0] == '3')
        {
            cout << s.top() << '\n';
            ans.push_back(s.top());
        }
        i++;
    }

    return ans;


}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> ops(n);

    for (int i = 0; i < n; i++) {
        string ops_item;
        getline(cin, ops_item);

        ops[i] = ops_item;
    }

    vector<int> res = getMax(ops);

    for (size_t i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

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
