/*
Jim has invented a new flying object called HZ42. HZ42 is like a broom and can 
only fly horizontally, independent of the environment. One day, Jim started his 
flight from Dubai's highest skyscraper, traveled some distance and landed on 
another skyscraper of same height! So much fun! But unfortunately, new 
skyscrapers have been built recently.
Let us describe the problem in one dimensional space. We have in total N 
skyscrapers aligned from left to right. The ith skyscraper has a height of h_i. A 
flying route can be described as (i,j) with i!=j, which means, Jim starts his 
HZ42 at the top of the skyscraper  and lands on the skyscraper j. Since HZ42 can 
only fly horizontally, Jim will remain at the height h_i only. Thus the path (i,j)
can be valid, only if each of the skyscrapers i,i+1,...,j-1,j is not strictly 
greater than h_i and if the height of the skyscraper he starts from and arrives 
on have the same height. Formally, (i,j) is valid iff 
Ak isAnElementOf([i,j]:h_k>h_i) and h_i=h_j.
Help Jim in counting the number of valid paths represented by ordered pairs (i,j).
Input Format
    The first line contains N, the number of skyscrapers. The next line contains 
    N space separated integers representing the heights of the skyscrapers.
Output Format
    Print an integer that denotes the number of valid routes.
Constraints
    1<=N<=3*10^5 and no skyscraper will have height greater than 10^6 and less 
    than 1.
Sample Input #00
    6
    3 2 1 2 3 3
Sample Output #00
    8
Sample Input #01
    3
    1 1000 1
Sample Output #01
    0
Explanation
    First testcase: (1, 5), (1, 6) (5, 6) and (2, 4) and the routes in the 
    opposite directions are the only valid routes.
    Second testcase: (1, 3) and (3, 1) could have been valid, if there wasn't a 
    big skyscraper with height 1000 between them.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

//int solve(vector<int> arr) {
long long solve(vector<int> arr){
     int n = arr.size();
    long long int count = 0;
    stack<pair<long long int, long long int> > s;
    
    for(int i = 0; i < n ; i ++){
        // iterating through arr, we have four cases.
        // first is that the stack is empty. 
        // second is that the top of the stack is greater than arr[i]
        if(s.empty() || arr[i] < s.top().first)
            s.push({arr[i], 1});
        // third is that the top of the stack is the same as arr[i]
        else if( arr[i] == s.top().first)
            s.top().second++;
        // fourth is that the top of the stack is less than arr[i]
        else{
            //so we need to pop each value that is less than arr[i]
            while(!s.empty() && arr[i] > s.top().first){
                // when we pop values, add 2* triangular sum
                count += s.top().second * (s.top().second - 1);
                s.pop();
            }
            // 3 cases
            // 1) the stack is now empty
            // 2) top > arr[i]
            if(s.empty() || arr[i] < s.top().first)
                s.push(make_pair(arr[i], 1));
            // 3) top == arr[i]
            else
                s.top().second++;
        }
    }

    // now need to count the values of the rest of the stack
    while(!s.empty() ){
        count += s.top().second * (s.top().second - 1);
        s.pop();
    }
    return count;
   /*
   //to slow
    long long gcount=0;
    for(int i=0;i<arr.size();i++)
    {
        long long ce = arr[i];
        for(int j = i+1; j < arr.size(); j++)
        {
            if(arr[j] > int(ce))
            {
                break;
            }
            if(arr[j] == int(ce))
            {
                gcount += 2;
                continue;
            }
        }
    }
    return int(gcount);
    */
/*
//fails two cases 
    int n = arr.size();
    int M[n];
    long long int sum = 0;
    M[0] = -1;
    //Create an Array M where M[i] is the index of the closest element to the left of arr[i] that is greater than or equal to arr[i]. If there is no such element let M[i]=-1
    for(int i = 1; i < n; i++){
        if(arr[i-1] >= arr[i])
            M[i] = i - 1;
        else {
            int j = i - 1;
            while(j >=0 && arr[j] < arr[i] && M[j] != -1){
                j = M[j];
                M[i] = j;
            }
        }
    }
    set<int> covered;
    for(int i = n - 1; i >= 0; i--){
        //If a particular series of elements have been covered make sure we don't cover the index i again
        if(covered.find(i) != covered.end())
            continue;
        int j = i;
        long k = 1;
        //Find the number of elements (k) where height is same and in between all elements are of lesser height
        while(j >= 0 && arr[M[j]] == arr[j]){
            k++;
            covered.insert(j);
            j = M[j]; 
        }
        //Add the number of ways of making pairs from k elements multiplied by 2 (bidirectional) to the overall sum
        sum = sum + (k * (k - 1));
    }
    return int(sum);
*/
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string arr_count_temp;
    getline(cin, arr_count_temp);

    int arr_count = stoi(ltrim(rtrim(arr_count_temp)));

    string arr_temp_temp;
    getline(cin, arr_temp_temp);

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(arr_count);

    for (int i = 0; i < arr_count; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    long long result = solve(arr);//this needs to be long long not int

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
