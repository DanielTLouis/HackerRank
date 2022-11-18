/*
A weighted string is a string of lowercase English letters
where each letter has a weight. Character weights are 1 to 26
from  to  as shown below:
        image
    -The weight of a string is the sum of the weights of its
    characters. For example:
        image
    -A uniform string consists of a single character repeated
    zero or more times. For example, ccc and a are uniform
    strings, but bcb and cd are not.
Given a string, s, let U be the set of weights for all possible
uniform contiguous substrings* of string s. There will be n
queries to answer where each query consists of a single
integer. Create a return array where for each query, the value
is Yes if quiery[i].isAnElementOf(U). Otherwise, append No.
Note: The elementOf symbol denotes that x[i] is an
    element** of set U.
    * https://en.wikipedia.org/wiki/Substring *
    ** https://en.wikipedia.org/wiki/Element_(mathematics) **
Example
    s='abbcccdddd'
    queries=[1,7,5,4,15].
    Working from left to right, weights that exist are:
        string  weight
        a       1
        b       2
        bb      4
        c       3
        cc      6
        ccc     9
        d       4
        dd      8
        ddd     12
        dddd    16
    Now for each value in queries, see if it exists in the
    possible string weights. The return array is
    ['Yes', 'No', 'No', 'Yes', 'No'].
Function Description
    Complete the weightedUniformStrings function in the editor
    below.
    weightedUniformStrings has the following parameter(s):
        - string s: a string
        - int queries[n]: an array of integers
Returns
    - string[n]: an array of strings that answer the queries
Input Format
    The first line contains a string s, the original string.
    The second line contains an integer n, the number of
    queries.
    Each of the next n lines contains an integer queries[i],
    the weight of a uniform subtring of s that may or may not
    exist.
Constraints
    1<=lengthofs,n<=10^5
    1<=queries[i]<=10^7
    s will only contain lowercase English letters, ascii[a-z].
Sample Input 0
    abccddde
    6
    1
    3
    12
    5
    9
    10
Sample Output 0
    Yes
    Yes
    Yes
    Yes
    No
    No
Explanation 0
    The weights of every possible uniform substring in the
    string abccddde are shown below:
        image
    We print Yes on the first four lines because the first four
    queries match weights of uniform substrings of s. We print
     No for the last two queries because there are no uniform
     substrings in s that have those weights.
    Note that while de is a substring of s that would have a
    weight of 9, it is not a uniform substring.
    Note that we are only dealing with contiguous substrings.
    So ccc is not a substring of the string ccxxc.
Sample Input 1
    aaabbbbcccddd
    5
    9
    7
    8
    12
    5
Sample Output 1
    Yes
    No
    Yes
    Yes
    No
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'weightedUniformStrings' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER_ARRAY queries
 */

vector<string> weightedUniformStrings(string s, vector<int> queries) {
    int continueChar = 1;
    int lastAlphaNum = 0;
    vector<int> numList;
    for(int i=0 ;i< s.length(); i ++){
        int alphaNum = s[i] - 'a' + 1;
        if(alphaNum == lastAlphaNum){
            continueChar++;
        }
        else{
            continueChar = 1;
            lastAlphaNum = alphaNum;
        }
        int num = (alphaNum) * continueChar;
        numList.push_back(num);
    }
    vector<string> ans;

    for(int i = 0; i < queries.size(); i++)
    {
        if(std::find(numList.begin(), numList.end(), queries[i]) != numList.end())
        {
            ans.push_back("Yes");
        }
        else
        {
            ans.push_back("No");
        }
    }

     return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));

        queries[i] = queries_item;
    }

    vector<string> result = weightedUniformStrings(s, queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
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
