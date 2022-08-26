/*
You will be given a list of integers, arr, and a single integer k. You must create an array of length k from elements of arr such that its unfairness is minimized. Call that array arr'. Unfairness of an array is calculated as
    max(arr')-min(arr')
Where:
    - max denotes the largest integer in arr'
    - min denotes the smallest integer in arr'
Example
    arr=[1,4,7,2]
    k=2
    Pick any two elements, say arr'=[4,7].
    unfairness=max(4,7)-min(4,7)=7-4=3
    Testing for all pairs, the solution [1,2] provides the minimum unfairness.
    Note: Integers in arr may not be unique.
Function Description
    Complete the maxMin function in the editor below.
    maxMin has the following parameter(s):
        int k: the number of elements to select
        int arr[n]:: an array of integers
Returns
    int: the minimum possible unfairness
Input Format
    The first line contains an integer , the number of elements in array arr.
    The second line contains an integer k.
    Each of the next  lines contains an integer arr[i] where 0<=i<n.
Constraints
    2<=n<=10^5
    2<=k<=n
    0<=arr[i]<=10^9
Sample Input
    Sample Input #01
        10
        4
        1
        2
        3
        4
        10
        20
        30
        40
        100
        200
Sample Output
    Sample Output #01
        3
Explanation
    Explanation #01
        Here k=4; selecting the 4 integers 1,2,3,4, unfairness equals
            max(1,2,3,4) - min(1,2,3,4) = 4 - 1 = 3
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'maxMin' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY arr
 */

int maxMin(int k, vector<int> arr) {
        sort(arr.begin(), arr.end());
        k -= 1;
        int min = INT_MAX;
        for(int i=0; i<arr.size() - k; i++){
            int sub = arr[i+k] - arr[i];
            if(sub < min)
                min = sub;
        }
        return min;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string k_temp;
    getline(cin, k_temp);

    int k = stoi(ltrim(rtrim(k_temp)));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        string arr_item_temp;
        getline(cin, arr_item_temp);

        int arr_item = stoi(ltrim(rtrim(arr_item_temp)));

        arr[i] = arr_item;
    }

    int result = maxMin(k, arr);

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
