/*
In this challenge, the task is to debug the existing code to
successfully execute all provided test files.
There are n boxes in front of you. For each i, box i contains
r[i] red balls, g[i] green balls, and b[i] blue balls.
You want to separate the balls by their color. In each
operation, you can pick a single ball from some box and put
it into another box. The balls are separated if no box
contains balls of more than one color.
Debug the given function min_operations and compute the
minimal number of operations required to separate the balls.
Note: In this problem you can modify at most six lines of
code and you cannot add any new lines.
To restore the original code, click on the icon to the right
of the language selector.
Input Format
    The first line contains a single integer n. The next n
    lines i contain three space-separated integers, r[i],
    g[i], and b[i], respectively.
Constraints
    1<=n<=100
    0<=r[i],g[i],b[i]<=105
Output Format
    Print the minimal number of operations required to
    separate the balls. If this is impossible, return -1.
Sample Input
    3
    1 1 1
    1 1 1
    1 1 1
Sample Output
    6
Explanation
    Each box contains 1 ball of each color. In this
    explanation, the goal will be to let the first box
    contain only red balls, the second box only blue balls,
    and the third box only green balls.
        -Move 1 blue ball and 1 green ball from the first box
        to the second and third boxes.
        -Move 1 red ball and 1 green ball from the second box
        to the first and third boxes.
        -Move 1 red ball and 1 blue ball from the third box
        to the first and second boxes.
    The number of operations is 6.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <map>
using namespace std;

int dp[110][1<<3];

int min_operations(vector <int> red, vector <int> green, vector <int> blue) {

    int n = (int)red.size(), i, j;
    for (i = 0; i <= n; i++) { //i<n changed to i<=n
        for (j = 0; j < 8; j++) {//j<7 changed to j<8
            dp[i][j] = 1<<30;
        }
    }

    dp[0][0] = 0;
    for (i = 0; i < n; i++){
        for (j = 0; j < 8; j++){//j<7 changed to  j<8
            dp[i + 1][j | 1] = min(dp[i + 1][j | 1], dp[i][j] + green[i] + blue[i]);
            dp[i + 1][j | 2] = min(dp[i + 1][j | 2], dp[i][j] + red[i] + blue[i]);
            dp[i + 1][j | 4] = min(dp[i + 1][j | 4], dp[i][j] + red[i] + green[i]);//blue changed to red
        }
    }
    j = 0;
    for (i = 0; i < n; i++){
        if (green[i]) j |= 2;//|=1 changed to |=2
        if (red[i]) j |= 1;//|=2 changed to |=1
        if (blue[i]) j |= 4;
    }

    if (dp[n][j] >= (1<<30))
        dp[n][j] = -1;

    return dp[n][j];
}

int main() {

    int n, r, g, b;
    cin >> n;
    vector<int> red, blue, green;

    for(int i = 0; i < n; i++){

        cin >> r >> g >> b;
        red.push_back(r);
        green.push_back(g);
        blue.push_back(b);
    }

    cout << min_operations(red, green, blue) << "\n";
    return 0;
}
