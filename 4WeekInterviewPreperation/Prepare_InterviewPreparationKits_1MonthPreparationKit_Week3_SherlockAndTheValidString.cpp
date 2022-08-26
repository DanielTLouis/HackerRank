/*
Sherlock considers a string to be valid if all characters of the string appear the
same number of times. It is also valid if he can remove just 1 character at 1 index in
the string, and the remaining characters will occur the same number of times. Given a
string , determine if it is valid. If so, return YES, otherwise return NO.
Example
    s=abc
    This is a valid string because frequencies are {a:1,b:1,c:1}.
    s=abcc
    This is a valid string because we can remove one c and have 1 of each character in
    the remaining string.
    s=abccc
    This string is not valid as we can only remove 1 occurrence of c. That leaves character frequencies of {a:1,b:1,c:2}.
Function Description
    Complete the isValid function in the editor below.
    isValid has the following parameter(s):
        -string s: a string
Returns
    string: either YES or NO
Input Format
    A single string s.
Constraints
    1<=|s|<=10^5
    Each character s[i] E(set){ ascii[a-z]}
Sample Input
    aabbcd
Sample Output
    NO
Explanation
    2 is the minimum number of removals required to make it a valid string. It can be
    done in following two ways:
    Remove c and d to get aabb.
    Or remove a and b to get abcd.
*/

#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */
string isValid(string s) {

    map<char, int> ch_count;
    bool flag = false;

    for (char ch : s)
    {
        if (ch_count.find(ch) != ch_count.end())
            ch_count[ch] += 1;
        else
            ch_count[ch] = 1;
    }

    for (auto a = ch_count.begin(), b = ++ch_count.begin(); b != ch_count.end(); ++b)
    {

        if (a->second == b->second)
            continue;
        else if ((b->second == 1 || abs(a->second - b->second) == 1) && flag == false)
            flag = true;
        else
            return "NO";
    }

    return "YES";
}
/*
//messes up two large input tests and cant test them myself
string isValid(string s) {
    vector<unsigned int> alphabet;
    alphabet.reserve(25);
    for(int i = 0; i < s.length(); i++)
    {
        switch(s[i])
        {
            case 'a':
                alphabet[0] += 1;
                break;
            case 'b':
                alphabet[1] += 1;
                break;
            case 'c':
                alphabet[2] += 1;
                break;
            case 'd':
                alphabet[3] += 1;
                break;
            case 'e':
                alphabet[4] += 1;
                break;
            case 'f':
                alphabet[5] += 1;
                break;
            case 'g':
                alphabet[6] += 1;
                break;
            case 'h':
                alphabet[7] += 1;
                break;
            case 'i':
                alphabet[8] += 1;
                break;
            case 'j':
                alphabet[9] += 1;
                break;
            case 'k':
                alphabet[10] += 1;
                break;
            case 'l':
                alphabet[11] += 1;
                break;
            case 'm':
                alphabet[12] += 1;
                break;
            case 'n':
                alphabet[13] += 1;
                break;
            case 'o':
                alphabet[14] += 1;
                break;
            case 'p':
                alphabet[15] += 1;
                break;
            case 'q':
                alphabet[16] += 1;
                break;
            case 'r':
                alphabet[17] += 1;
                break;
            case 's':
                alphabet[18] += 1;
                break;
            case 't':
                alphabet[19] += 1;
                break;
            case 'u':
                alphabet[20] += 1;
                break;
            case 'v':
                alphabet[21] += 1;
                break;
            case 'w':
                alphabet[22] += 1;
                break;
            case 'x':
                alphabet[23] += 1;
                break;
            case 'y':
                alphabet[24] += 1;
                break;
            case 'z':
                alphabet[25] += 1;
                break;
        }
    }
    unsigned int num = 0;
    bool oneces = false;
    for(int i = 0; i < 25; i++)
    {
        if(alphabet[i] != 0)
        {
            if(num == 0)
            {
                num = alphabet[i];
            }
            else if(alphabet[i] == num)
            {
                continue;
            }
            else
            {
                if(alphabet[i] + 1 == num && !oneces)
                {
                    oneces = true;
                    continue;
                }
                else if(((alphabet[i] - 1 == num)||(alphabet[i] - 1 == 0)) && !oneces)
                {
                    oneces = true;
                    continue;
                }
                else {
                    return "NO";
                }
            }
        }
    }
    return "YES";
}
*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
