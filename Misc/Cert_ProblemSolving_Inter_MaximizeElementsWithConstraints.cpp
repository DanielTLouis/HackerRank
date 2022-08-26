/*
1.maximizing elements with constraints 
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'maxElement' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER maxSum
 *  3. INTEGER k
 */

int maxElement(int n, int maxSum, int k) {
    if(n == 1)
        return maxSum;
    int right = k, left = k; int count = 1;
    int limitRight = n - 1;
    while(n <= maxSum && (left > 0 || right < limitRight)){
        n += right - left + 1;
        if(left > 0) left--;
        if(right < limitRight) right++; count++;
        }
    if(n < maxSum)
        count += (maxSum - n)/(right - left + 1) + 1;
    return count-1;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string maxSum_temp;
    getline(cin, maxSum_temp);

    int maxSum = stoi(ltrim(rtrim(maxSum_temp)));

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    int result = maxElement(n, maxSum, k);

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
