/*
Given a string, remove characters until the string is made up of any two
alternating characters. When you choose a character to remove, all instances of
that character must be removed. Determine the longest string possible that
contains just two alternating letters.
Example
    s='abaacdabd'
    Delete a, to leave bcdbd. Now, remove the character c to leave the valid
    string bdbd with a length of 4. Removing either b or d at any point would
    not result in a valid string. Return 4.
    Given a string s, convert it to the longest possible string t made up only
    of alternating characters. Return the length of string t. If no string t
    can be formed, return 0.
Function Description
    Complete the alternate function in the editor below.
    alternate has the following parameter(s):
        string s: a string
Returns.
    int: the length of the longest valid string, or 0 if there are none
Input Format
    The first line contains a single integer that denotes the length of s.
    The second line contains string s.
Constraints
    1<=length of s <=1000
    s[i] isAnElementOf(ascii[a-z])
Sample Input
    STDIN       Function
    -----       --------
    10          length of s = 10
    beabeefeab  s = 'beabeefeab'
Sample Output
    5
Explanation
    The characters present in  are a, b, e, and f. This means that t must
    consist of two of those characters and we must delete two others. Our
    choices for characters to leave are [a,b], [a,e], [a, f], [b, e], [b, f]
    and [e, f].
    If we delete e and f, the resulting string is babab. This is a valid t as
    there are only two distinct characters (a and b), and they are alternating
    within the string.
    If we delete a and f, the resulting string is bebeeeb. This is not a valid
    string t because there are consecutive e's present. Removing them would
    leave consecutive b's, so this fails to produce a valid string t.
    Other cases are solved similarly.
    babab is the longest string we can create.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'alternate' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */


int alternate(string s) {
    set<char> alphSet;

    const int str_len = s.length();

    for(int i = 0; i < str_len; ++i)
        alphSet.insert(s[i]);

    const int alphSetSize = alphSet.size();

    int i = 0;
    vector<int> maxLengths;

    while(i < alphSetSize-1)
    {
        int j = i+1;
        while(j < alphSetSize)
        {
            string temp(s);

            for(int k = 0; k < alphSetSize; ++k)
            {
                set<char>::iterator setIt = alphSet.begin();

                if(k == i || k == j)
                    continue;

                std::size_t found;
                advance(setIt, k);

                found = temp.find(*setIt);
                while (found!=std::string::npos)
                {
                    temp.erase(temp.begin()+found);
                    found = temp.find(*setIt);
                }
            }

            char previousChar = temp.at(0);
            bool solution_found = true;
            for(int string_idx = 1; string_idx < temp.length(); ++string_idx)
            {
                const char actualChar = temp.at(string_idx);
                if(previousChar == actualChar)
                {

                    solution_found = false;
                    break;
                }

                previousChar = actualChar;
            }

            if (solution_found)
                maxLengths.push_back(temp.length());

            j++;
        }

        i++;
    }

    if(maxLengths.size() > 0)
        return (*max_element(maxLengths.begin(), maxLengths.end()));

    return (0);
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string l_temp;
    getline(cin, l_temp);

    int l = stoi(ltrim(rtrim(l_temp)));

    string s;
    getline(cin, s);

    int result = alternate(s);

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
