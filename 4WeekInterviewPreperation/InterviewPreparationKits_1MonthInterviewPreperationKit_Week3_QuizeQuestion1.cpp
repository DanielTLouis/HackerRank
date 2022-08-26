/*
Suppose there is a circle. There are N petrol pumps on that circle. Petrol pumps
are numbered  to  (both inclusive). You have two pieces of information
corresponding to each of the petrol pump: (1) the amount of petrol that
particular petrol pump will give, and (2) the distance from that petrol pump to
the next petrol pump.
Initially, you have a tank of infinite capacity carrying no petrol. You can start
the tour at any of the petrol pumps. Calculate the first point from where the
truck will be able to complete the circle. Consider that the truck will stop at
each of the petrol pumps. The truck will move one kilometer for each litre of
the petrol.
Input Format
  The first line will contain the value of N.
  The next N lines will contain a pair of integers each, i.e. the amount of
  petrol that petrol pump will give and the distance between that petrol pump
  and the next petrol pump.
Constraints:
  1<=N<=10^5
  1<=amount of petrol, distance<=10^9
Output Format
  An integer which will be the smallest index of the petrol pump from which we
  can start the tour.
Sample Input
  3
  1 5
  10 3
  3 4
Sample Output
  1
Explanation
  We can start the tour from the second petrol pump.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);


/*
 * Complete the 'truckTour' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY petrolpumps as parameter.
 */

int truckTour(vector<vector<int>> petrolpumps) {
    long sum = 0;
        int index = 0;
        bool isIndexSet = false;
        for (int i = 0; i < petrolpumps.size(); i++) {
            int currFuel = petrolpumps[i][0];
            int currDist = petrolpumps[i][1];
            int diff = currFuel - currDist;
            sum += diff;
            if (sum < 0) {
                isIndexSet = false;
                sum = 0;
            } else {
                if (!isIndexSet) {
                    isIndexSet = true;
                    index = i;
                }
            }
        }
        return index;
}
int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> petrolpumps(n);

    for (int i = 0; i < n; i++) {
        petrolpumps[i].resize(2);

        string petrolpumps_row_temp_temp;
        getline(cin, petrolpumps_row_temp_temp);

        vector<string> petrolpumps_row_temp = split(rtrim(petrolpumps_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int petrolpumps_row_item = stoi(petrolpumps_row_temp[j]);

            petrolpumps[i][j] = petrolpumps_row_item;
        }
    }

    int result = truckTour(petrolpumps);

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
