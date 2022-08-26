/*
There is a collection of input strings and a collection of query 
strings. For each query string, determine how many times it occurs in 
the list of input strings. Return an array of the results.
Example
    strigns=['ab','ab','abc']
    queries=['ab','abc','bc']
    There are 2 instances of 'ab', 1 of 'abc' and 0 of 'bc'. For each query, add an element to the return array, result=[2,1,0].
Function Description
    Complete the function matchingStrings in the editor below. The 
    function must return an array of integers representing the 
    frequency of occurrence of each query string in strings.
    matchingStrings has the following parameters:
        -string strings[n] - an array of strings to search
        -string queries[q] - an array of query strings
Returns
    int[q]: an array of results for each query
Input Format
    The first line contains and integer n, the size of strings[].
    Each of the next n lines contains a string strings[i].
    The next line contains q, the size of queries[].
    Each of the next q lines contains a string queries[i].
Constraints
    1<=n<=1000
    1<=q<=1000
    1<=|strings[i]|, |queireies[i]|<=20
Sample Input 1
    4
    aba
    baba
    aba
    xzxb
    3
    aba
    xzxb
    ab
Sample Output 1
    2
    1
    0
Sample Input 2
    3
    def
    de
    fgh
    3
    de
    lmn
    fgh
Sample Output 2
    1
    0
    1
Sample Input 3
    13
    abcde
    sdaklfj
    asdjf
    na
    basdn
    sdaklfj
    asdjf
    na
    asdjf
    na
    basdn
    sdaklfj
    asdjf
    5
    abcde
    sdaklfj
    asdjf
    na
    basdn
Sample Output 3
    1
    3
    4
    3
    2
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
#include <iostream> 
#include <map>
/*
 * Complete the 'matchingStrings' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY strings
 *  2. STRING_ARRAY queries
 */

vector<int> matchingStrings(vector<string> strings, vector<string> queries) 
{
    map<string, int> m; //not used, just for refernce 
    vector<int> numOf; 
    for(int i = 0; i < queries.size(); i++)
    {
        int total = 0; 
        for(int j = 0; j < strings.size(); j++)
        {
            if(queries[i] == strings[j])
            {
                total += 1;
            }
        }
        numOf.push_back(total);
    }
    return numOf;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string strings_count_temp;
    getline(cin, strings_count_temp);

    int strings_count = stoi(ltrim(rtrim(strings_count_temp)));

    vector<string> strings(strings_count);

    for (int i = 0; i < strings_count; i++) {
        string strings_item;
        getline(cin, strings_item);

        strings[i] = strings_item;
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<string> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item;
        getline(cin, queries_item);

        queries[i] = queries_item;
    }

    vector<int> res = matchingStrings(strings, queries);

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
