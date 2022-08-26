/*
Hackerland is a one-dimensional city with houses aligned at integral locations along a
road. The Mayor wants to install radio transmitters on the roofs of the city's houses.
Each transmitter has a fixed range meaning it can transmit a signal to all houses
within that number of units distance away.
Given a map of Hackerland and the transmission range, determine the minimum number of
transmitters so that every house is within range of at least one transmitter. Each
transmitter must be installed on top of an existing house.
Example
    x=[1,2,3,5,9]
    k=1
    3 antennae at houses 2 and 5 and 9 provide complete coverage. There is no house at
    location 7 to cover both 5 and 9. Ranges of coverage, are [1,2,3], [5], and [9].
Function Description
    Complete the hackerlandRadioTransmitters function in the editor below.
    hackerlandRadioTransmitters has the following parameter(s):
        -int x[n]: the locations of houses
        -int k: the effective range of a transmitter
Returns
    int: the minimum number of transmitters to install
Input Format
    The first line contains two space-separated integers n and k, the number of houses
    in Hackerland and the range of each transmitter.
    The second line contains  space-separated integers describing the respective
    locations of each house x[i].
Constraints
    1<=n,k<=10^5
    1<=x[i]<10^5
    There may be more than one house at the same location.
Subtasks
    1<=n<=1000 for 50% of the maximum score.
Output Format
    Print a single integer denoting the minimum number of transmitters needed to cover
    all of the houses.
Sample Input 0
    STDIN       Function
    -----       --------
    5 1         x[] size n = 5, k = 1
    1 2 3 4 5   x = [1, 2, 3, 4, 5]
Sample Output 0
    2
Explanation 0
    The diagram below depicts our map of Hackerland:
        k-nearest(2).png
    We can cover the entire city by installing 2 transmitters on houses at locations 2
    and 4.
Sample Input 1
    8 2
    7 2 4 6 5 9 12 11
Sample Output 1
    3
Explanation 1
    The diagram below depicts our map of Hackerland:
        k-nearest2(2).png
    We can cover the entire city by installing 3 transmitters on houses at locations 4,
    9, and 12.
*/
#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'hackerlandRadioTransmitters' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY x
 *  2. INTEGER k
 */

int hackerlandRadioTransmitters(vector<int> x, int k) {
   /*
   //python
    x.sort()
    p=x[0];n=x[0];r=1
    for i in x:
        if i-p>k:
            r+=1
            p=i
            n=i
        else:
            if i-n<=k:
                p=i
    return r
   */
   sort(x.begin(), x.end());
   int p = x[0], n = x[0], r = 1;
   for(int i = 0; i < x.size(); i++)
   {
       if(x[i] - p > k)
       {
           r += 1;
           p = x[i];
           n = x[i];
       }
       else {
        if(x[i]-n <= k)
        {
            p=x[i];
        }
       }
   }
   return r;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string x_temp_temp;
    getline(cin, x_temp_temp);

    vector<string> x_temp = split(rtrim(x_temp_temp));

    vector<int> x(n);

    for (int i = 0; i < n; i++) {
        int x_item = stoi(x_temp[i]);

        x[i] = x_item;
    }

    int result = hackerlandRadioTransmitters(x, k);

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
