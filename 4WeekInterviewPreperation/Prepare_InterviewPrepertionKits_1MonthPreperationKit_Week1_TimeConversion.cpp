/*
Given a time in 12-hour AM/PM format*, convert it to military (24-hour) time.
Note: - 12:00:00AM on a 12-hour clock is 00:00:00 on a 24-hour clock.
- 12:00:00PM on a 12-hour clock is 12:00:00 on a 24-hour clock.
* https://en.wikipedia.org/wiki/12-hour_clock *
Example
    s='12:01:00PM
        Return '12:01:00'.
    s='12:01:00AM
        Return '00:01:00'.
Function Description
    Complete the timeConversion function in the editor below. It should return a new
    string representing the input time in 24 hour format.
    timeConversion has the following parameter(s):
    string s: a time in 12 hour format
Returns
    string: the time in 24 hour format
Input Format
    A single string  that represents a time in 12-hour clock format
    (i.e.: hh:mm:ssAM or hh:mm:ssPM).
Constraints
    All input times are valid
Sample Input
    07:05:45PM
Sample Output
    19:05:45
*/

#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string timeConversion(string s) {
    vector<string> st;
    string temp = "";
    bool pm = false;
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] == ':' || s[i] == 'P' || s[i] == 'A')
        {
            st.push_back(temp);
            cout << temp << " ";
            temp = "";
            if(s[i] == 'P')
            {
                pm = true;
            }
            continue;
        }
        temp += s[i];
    }
    cout << endl;
    string newTime = "";
    if(pm)
    {
        if(st[0] != "12")
        {
            st[0] = to_string(stoi(st[0]) + 12);
            cout << st[0];
        }
        newTime = st[0] + ":" + st[1] + ":" + st[2];
        return newTime;
    }
    else
    {
        if(st[0] != "12")
        {
            newTime = st[0] + ":" + st[1] + ":" + st[2];
            return newTime;
        }
        else
        {
            st[0] = "00";
            newTime = st[0] + ":" + st[1] + ":" + st[2];
            return newTime;
        }
    }
    return temp;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
