/*
Alice and Bob each created one problem for HackerRank. A reviewer rates the two
challenges, awarding points on a scale from 1 to 100 for three categories: problem
clarity, originality, and difficulty.
The rating for Alice's challenge is the triplet a = (a[0], a[1], a[2]), and the rating
for Bob's challenge is the triplet b = (b[0], b[1], b[2]).
The task is to find their comparison points by comparing a[0] with b[0], a[1] with
b[1], and a[2] with b[2].
    -If a[i] > b[i], then Alice is awarded 1 point.
    -If a[i] < b[i], then Bob is awarded 1 point.
    -If a[i] = b[i], then neither person receives a point.
Comparison points is the total points a person earned.
Given a and b, determine their respective comparison points.
Example
    a = [1, 2, 3]
    b = [3, 2, 1]
        -For elements *0*, Bob is awarded a point because a[0] .
        -For the equal elements a[1] and b[1], no points are earned.
        -Finally, for elements 2, a[2] > b[2] so Alice receives a point.
    The return array is [1, 1] with Alice's score first and Bob's second.
Function Description
    Complete the function compareTriplets in the editor below.
    compareTriplets has the following parameter(s):
        -int a[3]: Alice's challenge rating
        -int b[3]: Bob's challenge rating
Return
    int[2]: Alice's score is in the first position, and Bob's score is in the second.
Input Format
    The first line contains 3 space-separated integers, a[0], a[1], and a[2], the
    respective values in triplet a.
    The second line contains 3 space-separated integers, b[0], b[1], and b[2], the
    respective values in triplet b.
Constraints
    1 ≤ a[i] ≤ 100
    1 ≤ b[i] ≤ 100
Sample Input 0
    5 6 7
    3 6 10
Sample Output 0
    1 1
Explanation 0
    In this example:
        a=(a[0],a[1],a[2])=(5,6,7)
        b=(b[0],b[1],b[2])=(3,6,10)
    Now, let's compare each individual score:
        a[0]>b[0], so Alice receives 1 point.
        a[1]=b[1], so nobody receives a point.
        a[2]<b[2], so Bob receives 1 point.
    Alice's comparison score is 1, and Bob's comparison score is 1. Thus, we return
    the array [1,1].
Sample Input 1
    17 28 30
    99 16 8
Sample Output 1
    2 1
Explanation 1
    Comparing the 0th elements, 17<99 so Bob receives a point.
    Comparing the 1st and 2nd elements, 28>16 and 30>8 so Alice receives two points.
    The return array is [2,1].
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'compareTriplets' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY a
 *  2. INTEGER_ARRAY b
 */

vector<int> compareTriplets(vector<int> a, vector<int> b) {
    vector<int> win;
    win.resize(2);
    for(int i = 0; i < a.size(); i++)
    {
        if(a[i] > b[i])
        {
            win[0] += 1;
            continue;
        }
        else if(a[i] < b[i])
        {
            win[1] += 1;
            continue;
        }
    }
    return win;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string a_temp_temp;
    getline(cin, a_temp_temp);

    vector<string> a_temp = split(rtrim(a_temp_temp));

    vector<int> a(3);

    for (int i = 0; i < 3; i++) {
        int a_item = stoi(a_temp[i]);

        a[i] = a_item;
    }

    string b_temp_temp;
    getline(cin, b_temp_temp);

    vector<string> b_temp = split(rtrim(b_temp_temp));

    vector<int> b(3);

    for (int i = 0; i < 3; i++) {
        int b_item = stoi(b_temp[i]);

        b[i] = b_item;
    }

    vector<int> result = compareTriplets(a, b);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << " ";
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

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
