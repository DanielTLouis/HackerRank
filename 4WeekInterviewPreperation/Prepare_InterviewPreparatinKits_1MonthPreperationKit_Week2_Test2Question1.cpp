/*
*1 Month Interview Preparation Kit Test2 Question1
1.Palidrom index
Given a string of lowercase letters in the range asscii[a-z], determine the index
of a character that can be removed to make the string a palindrome. there many
be more than one solutions, but any will do. if the word is already a palindrome
or there is no solution, return -1. Otherwise, return the index of a character to
remove. 
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'palindromeIndex' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int palindromeIndex(string s) {
    string temp = s;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != s[(s.length()-1) -i])
        {
            temp.erase(temp.begin()+i);
            for(int j = 0; j < temp.length(); j++)
            {
                if(temp[j] != temp[temp.length()-1-j])
                {
                    return s.length() - 1 - i;
                }
            }
            return i;
        }
    }
    return -1;
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

        int result = palindromeIndex(s);

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
