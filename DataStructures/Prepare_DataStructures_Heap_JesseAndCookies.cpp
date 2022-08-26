/*
Jesse loves cookies and wants the sweetness of some cookies to be greater than value
k. To do this, two cookies with the least sweetness are repeatedly mixed. This creates
a special combined cookie with:
sweetness =(1 * Least sweet cookie  + 2 * 2nd least sweet cookie).
This occurs until all the cookies have a sweetness  >=k.
Given the sweetness of a number of cookies, determine the minimum number of operations
required. If it is not possible, return -1.
Example
    k=9
    A=[2,7,3,6,4,6]
    The smallest values are 2,3.
    Remove them then return 2+2*3=8 to the array. Now A=[8,7,6,4,6].
    Remove 4,6 and return 4+6*2=16 to the array. Now A=[16,8,7,6].
    Remove 6,7, return 6+2*7=20 and A=[20,16,8,7].
    Finally, remove 8,7 and return 7+2*8=23 to A. Now A=[23,20,16].
    All values are >=k=9 so the process stops after 4 iterations. Return 4.
Function Description
    Complete the cookies function in the editor below.
    cookies has the following parameters:
        -int k: the threshold value
        -int A[n]: an array of sweetness values
Returns
    int: the number of iterations required or -1
Input Format
    The first line has two space-separated integers, n and k, the size of A[] and the
    minimum required sweetness respectively.
    The next line contains  space-separated integers, A[i].
Constraints
    1<=n<=10^6
    0<=k<=10^9
    0<=A[i]<10^6
Sample Input
    STDIN               Function
    -----               --------
    6 7                 A[] size n = 6, k = 7
    1 2 3 9 10 12       A = [1, 2, 3, 9, 10, 12]
Sample Output
    2
Explanation
    Combine the first two cookies to create a cookie with sweetness  =  1*1+2*2=5
    After this operation, the cookies are 3,5,9,10,12.
    Then, combine the cookies with sweetness 3 and sweetness 5, to create a cookie
    with resulting sweetness  = 1*3+2*5 = 13
    Now, the cookies are 9,10,12,13.
    All the cookies have a sweetness >= 7.
    Thus, 2 operations are required to increase the sweetness.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'cookies' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY A
 */

int cookies(int k, vector<int> A) {
    priority_queue<int,vector<int>,greater<int>> minHeap;

    int operationCount = 0;

    for(auto i : A)
    {
        minHeap.push(i);
    }


    int tempCookie1 = 0;
    int tempCookie2 = 0;
    int newCookie = 0;


    while(minHeap.top() < k && operationCount < A.size())
    {

        if(!minHeap.empty())
        {
            tempCookie1 = minHeap.top();
            minHeap.pop();
        }

        if(!minHeap.empty())
        {
            tempCookie2 = minHeap.top();
            minHeap.pop();
        }

        newCookie = (1 * tempCookie1) + (2*tempCookie2);
        minHeap.push((newCookie));

        operationCount++;
    }

    return operationCount == A.size() ? - 1 : operationCount;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string A_temp_temp;
    getline(cin, A_temp_temp);

    vector<string> A_temp = split(rtrim(A_temp_temp));

    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        int A_item = stoi(A_temp[i]);

        A[i] = A_item;
    }

    int result = cookies(k, A);

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
