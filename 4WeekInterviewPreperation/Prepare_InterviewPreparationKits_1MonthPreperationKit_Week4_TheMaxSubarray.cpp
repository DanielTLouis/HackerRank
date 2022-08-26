/*
We define subsequence as any subset of an array. We define a subarray as a contiguous
subsequence in an array.
Given an array, find the maximum possible sum among:
    1.all nonempty subarrays.
    2.all nonempty subsequences.
Print the two values as space-separated integers on one line.
Note that empty subarrays/subsequences should not be considered.
Example
    arr=[-1,2,3,-4,5,10]
    The maximum subarray sum is comprised of elements at inidices [1-5]. Their sum is
    2+3+-4+5+10=16. The maximum subsequence sum is comprised of elements at indices
    [1,2,4,5] and their sum is 2+3+5+10=20.
Function Description
    Complete the maxSubarray function in the editor below.
    maxSubarray has the following parameter(s):
        -int arr[n]: an array of integers
Returns
    int[2]: the maximum subarray and subsequence sums
Input Format
    The first line of input contains a single integer t, the number of test cases.
    The first line of each test case contains a single integer n.
    The second line contains n space-separated integers arr[i] where 0<=i<n.
Constraints
    1<=t<=10
    1<=n<=10^5
    -10^4<=arr[i]<=10^4
The subarray and subsequences you consider should have at least one element.
Sample Input
    2
    4
    1 2 3 4
    6
    2 -1 2 3 4 -5
Sample Output
    10 10
    10 11
Explanation
    In the first case:
    The max sum for both contiguous and non-contiguous elements is the sum of ALL the
    elements (as they are all positive).
    In the second case:
    [2 -1 2 3 4] --> This forms the contiguous sub-array with the maximum sum.
    For the max sum of a not-necessarily-contiguous group of elements, simply add all
    the positive elements.
*/
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'maxSubarray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

vector<int> maxSubarray(vector<int> arr) {
    vector<int> ans;

    //subarray calcualtions
    int maxSubAarray = arr[0]; // max sub array
    int testMax = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        testMax = max(testMax + arr[i], arr[i]);
        maxSubAarray = max(maxSubAarray, testMax);
    }
    ans.push_back(maxSubAarray);

    //subsequence calcuations
    int maxSubSequence = INT_MIN;
    for(int i = 0; i < arr.size(); i++)
    {
        if(maxSubSequence <= 0)
        {
            if(maxSubSequence < arr[i])
            {
                maxSubSequence = arr[i];
            }
        }
        else if(arr[i] > 0)
        {
            maxSubSequence += arr[i];
        }
    }
    ans.push_back(maxSubSequence);
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        vector<int> result = maxSubarray(arr);

        for (size_t i = 0; i < result.size(); i++) {
            fout << result[i];

            if (i != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
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
