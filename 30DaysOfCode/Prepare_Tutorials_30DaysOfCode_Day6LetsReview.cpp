/*Problem*/
/**
Objective
    Today we will expand our knowledge of strings, combining it with     what we have already learned about loops. Check out the Tutorial     tab for learning materials and an instructional video.
Task
    Given a string, S, of length N that is indexed from 0 to N-1,        print its even-indexed and odd-indexed characters as 2               space-separated strings on a single line (see the Sample below       for more detail).
    Note: 0 is considered to be an even index.
Example
    s=adbecf
    Print abc def
Input Format
    The first line contains an integer, T(the number of test cases).
    Each line i of the T subsequent lines contain a string, S.
Constraints
    1<=T<=10
    2<=length of S <= 1000
Output Format
    For each String  S_j(where 0<=j<=T-1), print S_j's even-indexed      characters, followed by a space, followed by S_j's odd-indexed       characters.
Sample Input
    2
    Hacker
    Rank
Sample Output
    Hce akr
    Rn ak
Explanation
    Test Case 0:  S="Hacker"
    S[0] = "H"
    S[1] = "a"
    S[2] = "c"
    S[3] = "k"
    S[4] = "e"
    S[5] = "r"
    The even indices are 0, 2, and 4, and the odd indices are 1, 3,      and 5. We then print a single line of 2 space-separated strings;     the first string contains the ordered characters from S's even       indices (Hce), and the second string contains the ordered            characters from S's odd indices (akr).
Test Case 1: S = "Rank"
    S[0] = "R"
    S[1] = "a"
    S[2] = "n"
    S[3] = "k"
    The even indices are 0 and 2, and the odd indices are 1 and 3.       We then print a single line of 2 space-separated strings; the        first string contains the ordered characters from S's even           indices (Rn), and the second string contains the ordered             characters from S's odd indices (ak).
**/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    vector<string> str;
    vector<string> newStr;
    int t = 0;
    std::cin >> t;
    string temp= "";
    string temp2 = "";
    //get the strings from standard input
    for(int i = 0; i < t; i++)
    {
            std::cin >> temp;
            str.push_back(temp);
    }
    //create the new strings
    for(int i = 0; i < t; i++)
    {
        temp = "";
        temp2 = "";
        for(int j = 0; j < str[i].length(); j++)
        {
            if(j % 2 == 0)
            {
                temp += str[i][j];
            }
            else
            {
                temp2 += str[i][j];
            }
        }
        newStr.push_back(temp);
        newStr.push_back(temp2);
    }
    //pring the new strings
    for(int i = 0; i < t*2; i+=2)
    {
        std::cout << newStr[i] << " " << newStr[i+1] << endl;
    }
    return 0;
}
