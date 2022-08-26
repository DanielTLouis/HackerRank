/*
Whenever George asks Lily to hang out, she's busy doing homework. George wants to help
her finish it faster, but he's in over his head! Can you help George understand
Lily's homework so she can hang out with him?
Consider an array of  distinct integers, arr=[a[0],a[1],...,a[n-1]]. George can swap
any two elements of the array any number of times. An array is beautiful if the sum of
|arr[i]-arr[i-1]| among 0<i<n is minimal.
Given the array , determine and return the minimum number of swaps that should be
performed in order to make the array beautiful.
Example
    arr=[7,15,12,3]
    One minimal array is [3,7,12,15]. To get there, George performed the following
    swaps:
        Swap      Result
            [7, 15, 12, 3]
        3 7   [3, 15, 12, 7]
        7 15  [3, 7, 12, 15]

    It took 2 swaps to make the array beautiful. This is minimal among the choices of
    beautiful arrays possible.
Function Description
    Complete the lilysHomework function in the editor below.
    lilysHomework has the following parameter(s):
        -int arr[n]: an integer array
Returns
    int: the minimum number of swaps required
Input Format
    The first line contains a single integer, n, the number of elements in arr. The
    second line contains n space-separated integers, arr[i].
Constraints
    1<=n<=10^5
    1<=arr[i]<=2X10^9
Sample Input
    STDIN       Function
    -----       --------
    4           arr[]size n = 4
    2 5 3 1     arr = [2, 5, 3, 1]
Sample Output
    2
Explanation
    Define arr'=[1,2,3,5] to be the beautiful reordering of arr. The sum of the
    absolute values of differences between its adjacent elements is minimal among all
    permutations and only two swaps (1 with 2 and then 2 with 5) were performed.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'lilysHomework' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
int count_swap(vector<int> arr, vector<int> compare)
{
    int count = 0, i =0;
    while(i < arr.size())
    {
        if(compare[i] != arr[i])
        {
            //confused what to swap here
            int temp = compare[i];
            compare[i] = arr[i];
            arr[i] = temp;
            count += 1;
            i+=1;
        }
        else{
            i+=1;
        }
    }
    return count-1;
}
int lilysHomework(vector<int> arr) {
    /*
    def lilysHomework(arr):
        # function to count swaps to bring sorted array (s)
        # back to reference array (r)
        def countSwaps(s):
            count = 0
            i=0
            while i < len(arr):
        # if reference and sorted not the same value
                if s[i]['val'] != arr[i]:
        # swap them and increment count
        # (don't increment i to check again)
                    s[s[i]['idx']],s[i] = s[i],s[s[i]['idx']]
                    count += 1
                else: # check next i
                    i += 1

            return count

        # create object of value and index
        vec = [{"val": arr[i], "idx": i} for i in range(len(arr))]
        # assending sorted array
        a = sorted(vec, key=lambda x: x['val'])
        # descending sorted array
        d = sorted(vec, key=lambda x: x['val'], reverse=True)
        # return the minimum between assending and descending
        return min(countSwaps(a), countSwaps(d))
    */
    vector<int> a = arr;
    vector<int> b = arr;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end(), greater<int>());
    return min(count_swap(arr,a) , count_swap(arr,b));
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

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

    int result = lilysHomework(arr);

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
