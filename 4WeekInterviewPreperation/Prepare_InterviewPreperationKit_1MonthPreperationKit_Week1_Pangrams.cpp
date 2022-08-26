/*
A pangram is a string that contains every letter of the alphabet. Given a sentence
determine whether it is a pangram in the English alphabet. Ignore case. Return either
pangram or not pangram as appropriate.
Example
    s='The quick brown fox jumps over the lazy dog'
    The string contains all letters in the English alphabet, so return pangram.
Function Description
    Complete the function pangrams in the editor below. It should return the string
    pangram if the input string is a pangram. Otherwise, it should return not pangram.
    pangrams has the following parameter(s):
        -string s: a string to test
Returns
    string: either pangram or not pangram
Input Format
    A single line with string s.
Constraints
    0<length of s<= 10^3
    Each character of s,s[i]elementof({a-z,A-Z,space})
Sample Input
    Sample Input 0
        We promptly judged antique ivory buckles for the next prize
    Sample Output 0
        pangram
    Sample Explanation 0
        All of the letters of the alphabet are present in the string.
    Sample Input 1
        We promptly judged antique ivory buckles for the prize
    Sample Output 1
        not pangram
    Sample Explanation 0
        The string lacks an x.
*/

#include <bits/stdc++.h>
#include<string>
#include<locale>

using namespace std;

/*
 * Complete the 'pangrams' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string pangrams(string s) {
    vector<int> arr;
    arr.reserve(26);
    for(int i = 0; i <26; i++)
    {
        arr[i] = 0;
    }
    string st = "";
    for(int i = 0; i < s.length(); i++)
    {
        st += std::tolower(s[i]);
    }
    for(int i = 0; i < s.length(); i++)
    {
        switch(st[i])
        {
            case 'a':
                arr[0] +=1;
                break;
            case 'b':
                arr[1] +=1;
                break;
            case 'c':
                arr[2] +=1;
                break;
            case 'd':
                arr[3] +=1;
                break;
            case 'e':
                arr[4] +=1;
                break;
            case 'f':
                arr[5] +=1;
                break;
            case 'g':
                arr[6] +=1;
                break;
            case 'h':
                arr[7] +=1;
                break;
            case 'i':
                arr[8] +=1;
                break;
            case 'j':
                arr[9] +=1;
                break;
            case 'k':
                arr[10] +=1;
                break;
            case 'l':
                arr[11] +=1;
                break;
            case 'm':
                arr[12] +=1;
                break;
            case 'n':
                arr[13] +=1;
                break;
            case 'o':
                arr[14] +=1;
                break;
            case 'p':
                arr[15] +=1;
                break;
            case 'q':
                arr[16] +=1;
                break;
            case 'r':
                arr[17] +=1;
                break;
            case 's':
                arr[18] +=1;
                break;
            case 't':
                arr[19] +=1;
                break;
            case 'u':
                arr[20] +=1;
                break;
            case 'v':
                arr[21] +=1;
                break;
            case 'w':
                arr[22] +=1;
                break;
            case 'x':
                arr[23] +=1;
                break;
            case 'y':
                arr[24] +=1;
                break;
            case 'z':
                arr[25] +=1;
                break;
        }
    }
    for(int i = 0; i < 26; i++)
    {
        if(arr[i] == 0)
        {
            return "not pangram";
        }
    }
    return "pangram";
    //or from the discusion this works and is clever. 
    /*
    return 'pangram' if len(set(s.replace(' ','').lower()))==26 else 'not pangram';
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = pangrams(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
