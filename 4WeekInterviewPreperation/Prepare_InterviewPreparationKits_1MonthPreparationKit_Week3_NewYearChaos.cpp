/*
It is New Year's Day and people are in line for the Wonderland rollercoaster ride.
Each person wears a sticker indicating their initial position in the queue from 1 to
n. Any person can bribe the person directly in front of them to swap positions, but
they still wear their original sticker. One person can bribe at most two others.
Determine the minimum number of bribes that took place to get to a given queue order.
Print the number of bribes, or, if anyone has bribed more than two people, print Too
chaotic.
Example
    q=[1,2,3,5,4,6,7,8]
    If person 5 bribes person 4, the queue will look like this: 1,2,3,5,4,6,7,8. Only
    bribe is required. Print 1.
    q=[4,1,2,3]
    Person 4 had to bribe 3 people to get to the current position. Print Too chaotic.
Function Description
    Complete the function minimumBribes in the editor below.
    minimumBribes has the following parameter(s):
        -int q[n]: the positions of the people after all bribes
Returns
    No value is returned. Print the minimum number of bribes necessary or Too chaotic
    if someone has bribed more than  people.
Input Format
    The first line contains an integer t, the number of test cases.
    Each of the next t pairs of lines are as follows:
        - The first line contains an integer t, the number of people in the queue
        - The second line has  space-separated integers describing the final state of
        the queue.
Constraints
    1<=t<=10
    1<=n<=10^5
Subtasks
    For 60% score 1<=n<=10^3
    For 100% score 1<=n<=10^5
Sample Input
    STDIN       Function
    -----       --------
    2           t = 2
    5           n = 5
    2 1 5 3 4   q = [2, 1, 5, 3, 4]
    5           n = 5
    2 5 1 3 4   q = [2, 5, 1, 3, 4]
Sample Output
    3
    Too chaotic
Explanation
    Test Case 1
        The initial state:
            ride<-1<-2<-3<-4<-5
        After person 5 moves one position ahead by bribing person 4:
            ride<-1<-2<-3<-5<-4
        Now person 5 moves another position ahead by bribing person 3:
            ride<-1<-2<-5<-3<-4
        And person 2 moves one position ahead by bribing person 1:
            ride<-2<-1<-5<-3<-2
        So the final state is 2,1,5,3,4 after three bribing operations.
    Test Case 2
        No person can bribe more than two people, yet it appears person 5 has done so.
        It is not possible to achieve the input state.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumBribes' function below.
 *
 * The function accepts INTEGER_ARRAY q as parameter.
 */

void minimumBribes(vector<int> q) {
    int total_skips = 0;
    for(int i = q.size()-1; i >= 0; --i) {
        int target_value = i + 1;
        int skips = 0;
        int target_index = i;
        while(q[target_index] != target_value) {
            ++skips;
            if(skips > 2) { cout << "Too chaotic\n"; return; }
            --target_index;
        }
        total_skips += skips;
        q.erase(q.begin()+target_index);
    }
    cout << total_skips << "\n";
}
/*
void minimumBribes(vector<int> q) {
    int moves = 0, total = 0;
    for(int i = 0; i < q.size(); i++)
    {
        moves = 0;
        for(int j = i+1; j < q.size(); j++)
        {
            if(q[j]<q[i])
            {
                moves += 1;
                total += 1;
                int temp = q[j];
                q[j] = q[i];
                q[i]=temp;
                continue;
            }
        }
        if(moves > 2)
        {
            cout << "Too chaotic\n";
            return;
        }
    }
    cout << total<<endl;
    return;
}
*/

int main()
{
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split(rtrim(q_temp_temp));

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

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
