/*
Consider an array of numeric strings where each string is a positive number with
anywhere from 1 to 10^6 digits. Sort the array's elements in non-decreasing, or
ascending order of their integer values and return the sorted array.
Example
  unsorted = ['1','200','150','3']
  Return the array ['1', '3', '150', '200'].
Function Description
  Complete the bigSorting function in the editor below.
  bigSorting has the following parameter(s):
    -string unsorted[n]: an unsorted array of integers as strings
Returns
  string[n]: the array sorted in numerical order
Input Format
  The first line contains an integer, n, the number of strings in .
  Each of the n subsequent lines contains an integer string, .
Constraints
  1<=n<=2X10^5
  Each string is guaranteed to represent a positive integer.
  There will be no leading zeros.
  The total number of digits across all strings in unsorted is between 1 and
  10^6 (inclusive).
Sample Input 0
  6
  31415926535897932384626433832795
  1
  3
  10
  3
  5
Sample Output 0
  1
  3
  3
  5
  10
  31415926535897932384626433832795
Explanation 0
  The initial array of strings is
  unsorted=[31415926535897932384626433832795,1,3,10,3,5]. When we order each
  string by the real-world integer value it represents, we get:
    1<=3<=3<=5<=10<=31415926535897932384626433832795
  We then print each value on a new line, from smallest to largest.
Sample Input 1
  8
  1
  2
  100
  12303479849857341718340192371
  3084193741082937
  3084193741082938
  111
  200
Sample Output 1
  1
  2
  100
  111
  200
  3084193741082937
  3084193741082938
  12303479849857341718340192371
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



// Use of comparator
//comparing function only sorts if string size is equal and keeps the larger
//integgers at last.
bool myfunction (string i,string j)
{
    int n=i.length();
    int m=j.length();
    if(n==m)
        return (i<j);

    return n<m;
}
/*
 * Complete the 'bigSorting' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY unsorted as parameter.
 */

vector<string> bigSorting(vector<string> unsorted) {
    sort(unsorted.begin(),unsorted.end(),myfunction);
    return unsorted;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> unsorted(n);

    for (int i = 0; i < n; i++) {
        string unsorted_item;
        getline(cin, unsorted_item);

        unsorted[i] = unsorted_item;
    }

    vector<string> result = bigSorting(unsorted);

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
