/*
You have three stacks of cylinders where each cylinder has the same diameter, but they
may vary in height. You can change the height of a stack by removing and discarding
its topmost cylinder any number of times.
Find the maximum possible height of the stacks such that all of the stacks are exactly
the same height. This means you must remove zero or more cylinders from the top of
zero or more of the three stacks until they are all the same height, then return the
height.
Example
    h3=[1,2,1,1]
    h2=[1,1,2]
    h3=[1,1]
    There are 4,3 and 2 cylinders in the three stacks, with their heights in the three
    arrays. Remove the top 2 cylinders from  h1(heights = [1, 2]) and from  h2(heights
    = [1, 1]) so that the three stacks all are 2 units tall. Return 2 as the answer.
    Note: An empty stack is still a stack.
Function Description
    Complete the equalStacks function in the editor below.
    equalStacks has the following parameters:
        -int h1[n1]: the first array of heights
        -int h2[n2]: the second array of heights
        -int h3[n3]: the third array of heights
Returns
    int: the height of the stacks when they are equalized
Input Format
    The first line contains three space-separated integers, n1, n2, and n3, the
    numbers of cylinders in stacks 1, 2, and 3. The subsequent lines describe the
    respective heights of each cylinder in a stack from top to bottom:
        -The second line contains n1 space-separated integers, the cylinder heights in
        stack 1. The first element is the top cylinder of the stack.
        -The third line contains n2 space-separated integers, the cylinder heights in
        stack 2. The first element is the top cylinder of the stack.
        -The fourth line contains n3 space-separated integers, the cylinder heights in
        stack 3. The first element is the top cylinder of the stack.
Constraints
    0<n1,n2,n3<=10^5
    0<hight of any cylinder <= 100
Sample Input
    STDIN       Function
    -----       --------
    5 3 4       h1[] size n1 = 5, h2[] size n2 = 3, h3[] size n3 = 4
    3 2 1 1 1   h1 = [3, 2, 1, 1, 1]
    4 3 2       h2 = [4, 3, 2]
    1 1 4 1     h3 = [1, 1, 4, 1]
Sample Output
    5
Explanation
    Initially, the stacks look like this:
    initial stacks
    To equalize thier heights, remove the first cylinder from stacks 1 and 2, and then
    remove the top two cylinders from stack 3(shown below).
        modified stacks
    The stack heights are reduced as follows:
        1. 8-3=5
        2. 9-4=5
        3. 7-1-1=5
    All three stacks now have height=5, the value to return.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'equalStacks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY h1
 *  2. INTEGER_ARRAY h2
 *  3. INTEGER_ARRAY h3
 */
 /*
int sum(vector<int> arr)
{
    int total = 0;
    for(int i = 0; i < arr.size(); i++)
    {
        total += arr[i];
    }
    return total;
}
int equalStacks(vector<int> h1, vector<int> h2, vector<int> h3) {
    int t1 = sum(h1), t2 = sum(h2), t3 = sum(h3);
    while(t1 != t2 || t1 != t3 || t2 != t3)
    {
        t1 = sum(h1), t2 = sum(h2), t3 = sum(h3);
        cout << t1 << " " << t2 << " " << t3 << endl;
        if(t1 > t2)
        {
            h1.erase(h1.begin());
        }
        else if(t2 > t3)
        {
            h2.erase(h2.begin());
        }
        else if(t3 > t1)
        {
            h3.erase(h3.begin());
        }
        else if(t3 > t2)
        {
            h3.erase(h3.begin());
        }
        else if(t2 > t1)
        {
            h2.erase(h2.begin());
        }
        else if(t1 > t3)
        {
            h1.erase(h1.begin());
        }
    }
    return sum(h1);
}
*/

int equalStacks(vector<int> h1, vector<int> h2, vector<int> h3) {
    for(int i=h1.size()-2;i>=0;i--) h1[i]+=h1[i+1];
    for(int i=h2.size()-2;i>=0;i--) h2[i]+=h2[i+1];
    for(int i=h3.size()-2;i>=0;i--) h3[i]+=h3[i+1];

    std::reverse(h1.begin(),h1.end());
    std::reverse(h2.begin(),h2.end());
    std::reverse(h3.begin(),h3.end());

    stack<int> st1,st2,st3;
    for(int i=0;i<h1.size();i++) st1.push(h1[i]);
    for(int i=0;i<h2.size();i++) st2.push(h2[i]);
    for(int i=0;i<h3.size();i++) st3.push(h3[i]);

    while(true){
        if(st1.empty() || st2.empty() || st3.empty()) return 0;

        if(st1.top()==st2.top() && st2.top()==st3.top()){
            return st1.top();
        }
        else{
            if(st1.top()>=st2.top() && st1.top()>=st3.top()) st1.pop();
            else if(st2.top()>=st1.top() && st2.top()>=st3.top()) st2.pop();
            else st3.pop();
        }
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n1 = stoi(first_multiple_input[0]);

    int n2 = stoi(first_multiple_input[1]);

    int n3 = stoi(first_multiple_input[2]);

    string h1_temp_temp;
    getline(cin, h1_temp_temp);

    vector<string> h1_temp = split(rtrim(h1_temp_temp));

    vector<int> h1(n1);

    for (int i = 0; i < n1; i++) {
        int h1_item = stoi(h1_temp[i]);

        h1[i] = h1_item;
    }

    string h2_temp_temp;
    getline(cin, h2_temp_temp);

    vector<string> h2_temp = split(rtrim(h2_temp_temp));

    vector<int> h2(n2);

    for (int i = 0; i < n2; i++) {
        int h2_item = stoi(h2_temp[i]);

        h2[i] = h2_item;
    }

    string h3_temp_temp;
    getline(cin, h3_temp_temp);

    vector<string> h3_temp = split(rtrim(h3_temp_temp));

    vector<int> h3(n3);

    for (int i = 0; i < n3; i++) {
        int h3_item = stoi(h3_temp[i]);

        h3[i] = h3_item;
    }

    int result = equalStacks(h1, h2, h3);

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
