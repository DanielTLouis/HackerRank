/*
Given an array of integers and a target value, determine the number of pairs of
array elements that have a difference equal to the target value.
Example
  k=1
  arr=[1,2,3,4]
  There are three values that differ by : k=1, 2-1=1, 3-2=1, and 4-3=1. Return
  3.
Function Description
  Complete the pairs function below.
  pairs has the following parameter(s):
    -int k: an integer, the target difference
    -int arr[n]: an array of integers
Returns
  int: the number of pairs that satisfy the criterion
Input Format
  The first line contains two space-separated integers n and k, the size of arr
  and the target value.
  The second line contains n space-separated integers of the array arr.
Constraints
  2<=n<=10^5
  0<k<10^9
  0<arr[i]<2^31 -1
  each integer arr[i] will be unique
Sample Input
  STDIN       Function
  -----       --------
  5 2         arr[] size n = 5, k =2
  1 5 3 4 2   arr = [1, 5, 3, 4, 2]
Sample Output
  3
Explanation
  There are 3 pairs of integers in the set with a difference of 2: [5,3], [4,2]
  and [3,1]. .
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);



/*
 * Complete the 'pairs' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY arr
 */

int pairs(int k, vector<int> arr) {
     unordered_map<int, int> mp;
    int cnt=0;
    for(int i:arr)
        mp[i]++;
    for(int i:arr)
        cnt+=mp[k+i];
    return cnt;
    /*
    bool moved = false;
    do {
        moved = false;
        for(int i = 0; i < arr.size() - 1; i++)
        {
            if(arr[i] > arr[i+1])
            {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                moved = true;
                break;
            }
        }
    }while (moved);
     int i=0,j=1,count=0;

    while(j < arr.size()) {
        int diff = arr[j] - arr[i];

        if (diff == k) {
            count++;
            j++;
        } else if (diff > k) {
            i++;
        } else if (diff < k) {
            j++;
        }
    }
    return count;
    */
    /*
    int differs = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        for(int j = 0; j < arr.size(); j++)
        {
            if(j != i)
            {
                if(arr[i] - arr[j] == k)
                {
                    differs += 1;
                }
            }
        }
    }
    return differs;
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

    int result = pairs(k, arr);

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
