/*
Meera teaches a class of n students, and every day in her classroom is an 
adventure. Today is drawing day!
The students are sitting around a round table, and they are numbered from 1 to n 
in the clockwise direction. This means that the students are numbered 1,2,3,...,
n-1, and students 1 and n are sitting next to each other.
After letting the students draw for a certain period of time, Meera starts 
collecting their work to ensure she has time to review all the drawings before 
the end of the day. However, some of her students aren't finished drawing! Each 
student i needs t_i extra minutes to complete their drawing.
Meera collects the drawings sequentially in the clockwise direction, starting 
with student ID x, and it takes her exactly 1 minute to review each drawing. This 
means that student x gets 0 extra minutes to complete their drawing, student x+1 
gets 1 extra minute, student x+2 gets 2 extra minutes, and so on. Note that Meera 
will still spend 1 minute for each student even if the drawing isn't ready.
Given the values of t_1,t_2,...,t_n, help Meera choose the best possible x to 
start collecting drawings from, such that the number of students able to complete 
their drawings is maximal. Then print x on a new line. If there are multiple such 
IDs, select the smallest one.
Input Format
    The first line contains a single positive integer, n, denoting the number of 
    students in the class.
    The second line contains n space-separated integers describing the respective 
    amounts of time that each student needs to finish their drawings 
    (i.e., t_1,t_2,...,t_n).
Constraints
    1<=n<=10^5
    0<=t_i<=n
Subtasks
    1<=n<=10^4 for 30% of the maximum score.
Output Format
    Print an integer denoting the ID number, , where Meera should start 
    collecting the drawings such that a maximal number of students can complete 
    their drawings. If there are multiple such IDs, select the smallest one.
Sample Input 1
    Array: t
        1
        0
        0
    CopyDownload
        3
        1 0 0
Sample Output 1
    2
Explanation 1
    Meera's class has n=3 students:
        1. If x=1, then only two students will finish.
            The first student needs t_1=1 extra minute to complete their drawing.
            If Meera starts collecting here, this student will never finish their 
            drawing. Students 2 and 3's drawings are already finished, so their 
            drawings are ready when she collects them in the second and third 
            minutes.
        2. If x=2, then all three students will finish.
            The second student needs t_2=0 extra minutes, so the drawing is ready 
            for Meera to collect. The next (third) student's drawing is also 
            ready one minute later, as t_3=0. Meera then proceeds to the next 
            (first) student, who needed t_1=1 extra minute. Because she already 
            spent two minutes collecting the work of the other two students, the 
            first student's drawing has already been completed for 2-1=1 minute.
        3. If x=3, then all three students will finish.
            The third student needs t_3=0 extra minutes, so the drawing is ready 
            for Meera to collect. The next (first) student's drawing is also 
            ready one minute later, as t_1=1 and 1 minute passed while Meera 
            collected the third student's drawing. She then proceeds to the next 
            (second) student, whose drawing was already completed (as t_2=0)
    Starting with student IDs x=2 or x=3 will result in a maximum number of 
    completed drawings (i.e., 3). Because there are two equally valid answers, we 
    choose the smaller ID, 2, and print it as our answer.
Sample Input 2
    Array: t
        0
        1
        2
    CopyDownload
        3
        0 1 2
Sample Output 2
    1
*/

#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the solve function below.
 */
int solve(vector<int> t) {
    /*
     * Return the ID
     */
    /*
        My O(n) solution in C++. Here is my idea: 1. For each value of t[i], count all 
    sastified starting points then store in an array. 2. Search for max element in array 
    then return the index. To store and search effciently, you may try the problem Array 
    Manipulation in Data structure - hard - array
    */
    int n = t.size();
    /* n < 10^5
    Must move to heap memory
    */
    int arr[n+1] = {0}; 
    
    for (int i = 0; i < n; ++i) {
        if (t[i] - i > 0) {
            /* t[i] > i
            The start point is included in (i+1,n - (t[i]-i))
            Add 1 in the count array when go into the interval
            Remove 1 when go out the interval
            */
            arr[i+1] += 1;
            arr[n - (t[i]-i) + 1] -= 1;
        }
        else {
            /* t[i] <= i
            The start point is included in (0,i - t[i]) and (i+1,n-1)
            Add 1 in the count array when go into the interval
            Remove 1 when go out the interval
            */
            arr[0] += 1;
            arr[i - t[i] + 1] -= 1;
            arr[i+1] += 1;
            arr[n] -= 1;
        } 
    }
    
    int index = 0;
    int count = 0;
    int max = 0;
    
    for (int i = 0; i < n; ++i) {
        count += arr[i];
        if (count > max) {
            max = count;
            index = i + 1;
        } 
    }
    
    return index;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t_count;
    cin >> t_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string t_temp_temp;
    getline(cin, t_temp_temp);

    vector<string> t_temp = split_string(t_temp_temp);

    vector<int> t(t_count);

    for (int t_itr = 0; t_itr < t_count; t_itr++) {
        int t_item = stoi(t_temp[t_itr]);

        t[t_itr] = t_item;
    }

    int id = solve(t);

    fout << id << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}