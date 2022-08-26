/*
*1 Month Preparation kit Test 2
3. Anagram
Two words are anagrams of one another if their letters can be rearranged to Forma
the other word. Given a string, split it into two contiguous substrings of equal
length. Determine the minimum number of characters to change to make the two
substrings characters to change to make the two substrings into anagrams of onece
another
Example
  s=abccde
  Break s into two parts 'abc' and 'cde'. Note that all letters have been used,
  the substrings are contiguous and their lenghs are equal. Now you can change 'a'
  and 'b' in the first substring to 'd' and 'e' to have 'dce' and 'cde' which are
  anagrams. Two changes were necessary. 
  */
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'anagram' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int anagram(string s) {
    if(s.length() % 2 != 0)
        return -1;

    std::string diff;
    int size = s.length();
    string lp = s.substr(0, size / 2);
    string rp = s.substr(size / 2, size / 2);

    std::sort(lp.begin(), lp.end());
    std::sort(rp.begin(), rp.end());

    std::set_difference(lp.begin(), lp.end(), rp.begin(), rp.end(), std::back_inserter(diff));

    return diff.length();
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = anagram(s);

        fout << result << "\n";
    }

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
