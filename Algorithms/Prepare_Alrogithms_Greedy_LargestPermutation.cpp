/*
You are given an unordered array of unique integers incrementing from 1. You can
swap any two elements a limited number of times. Determine the largest
lexicographical value array that can be created by executing no more than the
limited number of swaps.
Example
    arr=[1,2,3,4]
    k=1
    The following arrays can be formed by swapping the 1 with the other elements:
        [2,1,3,4]
        [3,2,1,4]
        [4,2,3,1]
    The highest value of the four (including the original) is [4,2,3,1]. If k>=2,
    we can swap to the highest possible value: [4,3,2,1].
Function Description
    Complete the largestPermutation function in the editor below. It must return
    an array that represents the highest value permutation that can be formed.
    largestPermutation has the following parameter(s):
        int k: the maximum number of swaps
        int arr[n]: an array of integers
Input Format
    The first line contains two space-separated integers n and k, the length of
    arr and the maximum swaps that can be performed. The second line contains n
    distinct space-separated integers from 1 to n as arr[i] where 1<=arr[i]<=n.
Constraints
    1<=n<=10^5
    1<=k<=10^9
Output Format
    Print the lexicographically largest permutation you can make with at most k
    swaps.
Sample Input 0
    STDIN       Function
    -----       --------
    5 1         n = 5, k = 1
    4 2 3 5 1   arr = [4, 2, 3, 5, 1]
Sample Output 0
    5 2 3 4 1
Explanation 0
    You can swap any two numbers in [4,2,3,5,1] and see the largest permutation
    is [5,2,3,4,1]
Sample Input 1
    3 1
    2 1 3
Sample Output 1
    3 1 2
Explanation 1
    With 1 swap we can get [1,2,3], [3,1,2] and [2,3,1]. Of these, [3,1,2] is the
    largest permutation.
Sample Input 2
    2 1
    2 1
Sample Output 2
    2 1
Explanation 2
    We can see that [2,1] is already the largest permutation. We don't make any
    swaps.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'largestPermutation' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY arr
 */
 /*
 //not needed sort
vector<int> sort(vector<int> arr)
{
    vector<int> b;
    for(int i = 0; i < arr.size(); i++)
    {
        b.push_back(arr[i]);
    }
    bool found = false;
    do
    {
        found = false;
        for(int i = 0; i < b.size()-1; i++)
        {
            if(b[i] < b[i+1]){
                int temp = b[i];
                b[i] = b[i+1];
                b[i+1] = temp;
                found = true;
                break;
            }
        }
    }while(found);
    return b;
}
*/
vector<int> largestPermutation(int k, vector<int> arr) {
    //bigO O(n)time
    int n = arr.size();
    vector<int> save( n + 1, 0);
    for(int i = 0; i < n;i++){
        save[arr[i]] = i;
    }
    int cur = 0;
    for(int i = n ; i > 0 ; i--){
        if(arr[cur] != i){
            int temp = arr[cur];
            swap(arr[cur], arr[save[i]]);
            swap(save[i], save[temp]);
            k--;
            if(k == 0) break;

        }
        cur++;
    }
    return arr;
    /*
    //to slow
    vector<int> sortedArr = sort(arr);
    for(int i = k-1; i > -1; i--)
    {
        //swap the kth value of sorted with the front value of arr
        vector<int>::iterator index = std::find(arr.begin(),
            arr.end(), sortedArr[i]);
        cout << *index << endl;
        int temp = arr[0];
        arr[0] = *index; //it's a pointer simple derference to access element
        *index = temp;

    }
    return arr;
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    vector<int> result = largestPermutation(k, arr);

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
