/*
Given a set of distinct integers, print the size of a maximal subset of S where 
the sum of any 2 numbers in S' is not evenly divisible by k.
Example
    S=[19,10,10,12,24,25,22]
    One of the arrays that can be created is S'[0]=[10,12,25]. Another is 
    S'[1]=[19,22,24]. After testing all permutations, the maximum length solution 
    array has 3 elements.
Function Description
    Complete the nonDivisibleSubset function in the editor below.
    nonDivisibleSubset has the following parameter(s):
        int S[n]: an array of integers
        int k: the divisor
Returns
    int: the length of the longest subset of S meeting the criteria
Input Format
    The first line contains 2 space-separated integers, n and k, the number of 
    values in S and the non factor.
    The second line contains n space-separated integers, each an S[i], the unique 
    values of the set.
Constraints
    1<=n<=10^5
    1<=k<=100
    1<=S[i]<=10^9
    All of the given numbers are distinct.
Sample Input
    STDIN    Function
    -----    --------
    4 3      S[] size n = 4, k = 3
    1 7 2 4  S = [1, 7, 2, 4]
Sample Output
    3
Explanation
    The sums of all permutations of two elements from S={1,7,2,4} are:
        1 + 7 = 8
        1 + 2 = 3
        1 + 4 = 5
        7 + 2 = 9
        7 + 4 = 11
        2 + 4 = 6
    Only S'=[1,7,4] will not ever sum to a multiple of k=3.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'nonDivisibleSubset' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY s
 */

int nonDivisibleSubset(int k, vector<int> s) {
    //maintain frequency of number with 0 to k-1 remainder
    vector<int> freq(k,0);
    int res;
        //build frequency array
    for(int i=0; i<s.size(); i++){
        freq[s[i]%k]+=1;
    }
    //on reaminder 0 case we need only one count , because if we combine diffrent 
    //numbers with 0 reminder we end with number which is equally divisible by k   
    res=min(freq[0],1);
    for(int i=1; i<=(k/2); i++){
        if(i!=k-i){
            res+=max(freq[i],freq[k-i]);
        }
        else{
            res+=min(freq[i],1);
        }
    }
    return res;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s_temp_temp;
    getline(cin, s_temp_temp);

    vector<string> s_temp = split(rtrim(s_temp_temp));

    vector<int> s(n);

    for (int i = 0; i < n; i++) {
        int s_item = stoi(s_temp[i]);

        s[i] = s_item;
    }

    int result = nonDivisibleSubset(k, s);

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
