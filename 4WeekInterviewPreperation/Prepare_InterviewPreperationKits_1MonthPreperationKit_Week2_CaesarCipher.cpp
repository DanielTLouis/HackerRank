/*
Julius Caesar protected his confidential information by encrypting it 
using a cipher. Caesar's cipher* shifts each letter by a number of 
letters. If the shift takes you past the end of the alphabet, just 
rotate back to the front of the alphabet. In the case of a rotation by 
3, w, x, y and z would map to z, a, b and c.
* https://en.wikipedia.org/wiki/Caesar_cipher *
    Original alphabet:      abcdefghijklmnopqrstuvwxyz
    Alphabet rotated +3:    defghijklmnopqrstuvwxyzabc
Example
    k=3
    The alphabet is rotated by 3, matching the mapping above. The 
    encrypted string is Wkhuh'v-d-vwdpdq-zdlwlqj-lq-wkh-vnb.
    Note: The cipher only encrypts letters; symbols, such as -, remain 
    unencrypted.
Function Description
    Complete the caesarCipher function in the editor below.
    caesarCipher has the following parameter(s):
        string s: cleartext
        int k: the alphabet rotation factor
Returns
    string: the encrypted string
Input Format
    The first line contains the integer, n, the length of the 
    unencrypted string.
    The second line contains the unencrypted string, s.
    The third line contains k, the number of letters to rotate the 
    alphabet by.
Constraints
    1<=n<=100
    0<=k<=100
    s is a valid ASCII string without any spaces.
Sample Input
    11
    middle-Outz
    2
Sample Output
    okffng-Qwvb
Explanation
    Original alphabet:      abcdefghijklmnopqrstuvwxyz
    Alphabet rotated +2:    cdefghijklmnopqrstuvwxyzab
        m -> o
        i -> k
        d -> f
        d -> f
        l -> n
        e -> g
        -    -
        O -> Q
        u -> w
        t -> v
        z -> b
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'caesarCipher' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER k
 */

string caesarCipher(string s, int k) {
    if(k > 26)
    {
        while(k>26)
        {
            k -= 26;
        }
    }
    for(int i = 0; i < s.size(); i++)
    {
        if(isalpha(s[i]))
        {
            if(tolower(s[i]) > 'z'- k)
            {
                int newK =abs('z' - tolower(s[i])-k)-1;
                cout<<newK;
                if(isupper(s[i]))
                {
                    s[i]='A' + newK;
                }
                else 
                {
                    s[i] = 'a' + newK;
                }
            }
            else
            {
                s[i] += k;
            }
        }
    }
    return s;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string s;
    getline(cin, s);

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    string result = caesarCipher(s, k);

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