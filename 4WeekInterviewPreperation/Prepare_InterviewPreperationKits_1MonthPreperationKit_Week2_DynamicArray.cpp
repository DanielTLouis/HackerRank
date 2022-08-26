/*
-Declare a 2-dimensional array, , of  empty arrays. All arrays are zero indexed.
-Declare an integer, , and initialize it to .
-There are  types of queries, given as an array of strings for you to parse:
    1.Query: 1 x y
        1.Let idx=((x^lasterAnswer)%n).
        2.Append the integer y to arr[edx].
    2.Query: 2 x y
        1.Let idx=((x^lastAnwser)%n).
        2.Assign the value arr[idx][y%size(arr[idx])] to lastAnswer.
        3.Store the new value of lastAnswer to an answers array.
Note: ^ is the bitwise XOR operation, which corresponds to the ^ operator in most languages. Learn more about it on Wikipedia. % is the modulo operator.
Finally, size(arr[idx]) is the number of elements in arr[idx]
Function Description
    Complete the dynamicArray function below.
    dynamicArray has the following parameters:
        - int n: the number of empty arrays to initialize in
        - string queries[q]: query strings that contain 3 space-separated integers
Returns
    int[]: the results of each type 2 query in the order they are presented
Input Format
    The first line contains two space-separated integers, , the size of  to create,
    and , the number of queries, respectively.
    Each of the q subsequent lines contains a query string, queries[i].
Constraints
    1<=n,q<=10^5
    0<=x,y<=10^9
    It is guaranteed that query type 2 will never query an empty array or index.
Sample Input
    2 5
    1 0 5
    1 1 7
    1 0 3
    2 1 0
    2 1 1
Sample Output
    7
    3
Explanation
    Initial Values:
    n=2
    lastAnswer=0
    arr[0]= [ ]
    arr[1]= [ ]
    Query 0: Append 5 to arr[((0^0)%2)]=arr[0].
    lastAnswer=0
    arr[0]= [5]
    arr[1]= [ ]
    Query 1: Append 7 to [((1^0)%2)]=arr[1].
    arr[0]= [5]
    arr[1]= [7]
    Query 2: Append 3 to arr[((0^0)%2)]=arr[0].
    lastAnswer=0
    arr[0]= [5, 3]
    arr[1]= [7]
    Query 3: Assign the value at index 0 of arr[((1^0)%2)]=arr[1] to lastAnswer, print
    lastAnswer.
    lastAnswer=7
    arr[0]= [5, 3]
    arr[1]= [7]
        7
    Query 4: Assign the value at index 1 of arr[((1^7)%2)]=arr[0] to lastAnswer, print
    lastAnswer.
    lastAnswer=3
    arr[0]= [5, 3]
    arr[1]= [7]
        3
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'dynamicArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. 2D_INTEGER_ARRAY queries
 */

vector<int> dynamicArray(int n, vector<vector<int>> queries) {
    vector<vector<int>> arr;
    arr.reserve(n);
    vector<int> ans;
    int lastAnswer = 0;
    for(int i = 0; i < queries.size(); i++)
    {
        if(queries[i][0] == 1)
        {
            int idx = ((queries[i][1] ^ lastAnswer)%n);
            arr[idx].push_back(queries[i][2]);
        }
        else if(queries[i][0] == 2)
        {
            int idx = ((queries[i][1] ^ lastAnswer)%n);
            lastAnswer = arr[idx][queries[i][2]%arr[idx].size()];
            ans.push_back(lastAnswer);
        }
    }
    return ans;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int q = stoi(first_multiple_input[1]);

    vector<vector<int>> queries(q);

    for (int i = 0; i < q; i++) {
        queries[i].resize(3);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int queries_row_item = stoi(queries_row_temp[j]);

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> result = dynamicArray(n, queries);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
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
