/*
You have an infinite number of 4 types of lego blocks of sizes given as (depth x
height x width):
    d    h    w
    1    1    1
    1    1    2
    1    1    3
    1    1    4
Using these blocks, you want to make a wall of height  and width . Features of the
wall are:
    - The wall should not have any holes in it.
    - The wall you build should be one solid structure, so there should not be a
    straight vertical break across all rows of bricks.
    - The bricks must be laid horizontally.
How many ways can the wall be built?
Example
    n = 2
    m = 3
    The height is 2 and the width is 3. Here are some configurations:
        image
    These are not all of the valid permutations. There are 9 valid permutations in all.
Function Description
    Complete the legoBlocks function in the editor below.
    legoBlocks has the following parameter(s):
        -int n: the height of the wall
        -int m: the width of the wall
Returns
    - int: the number of valid wall formations modulo (10^9 + 7)
Input Format
    The first line contains the number of test cases .
    Each of the next  lines contains two space-separated integers  and .
Constraints
    1<=t<=100
    1<=n,m<=1000
Sample Input
    STDIN   Function
    -----   --------
    4       t = 4
    2 2     n = 2, m = 2
    3 2     n = 3, m = 2
    2 3     n = 2, m = 3
    4 4     n = 4, m = 4
Sample Output
    3
    7
    9
    3375
Explanation
    For the first case, we can have:
        image
    3 mod (10^9 + 7) = 3
    For the second case, each row of the wall can contain either two blocks of width 1,
    or one block of width 2. However, the wall where all rows contain two blocks of
    width 1 is not a solid one as it can be divided vertically. Thus, the number of
    ways is 2X2X2-1=7 and 7 mod(10^9 + 7) = 7.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'legoBlocks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */
int legoBlocks(int n, int m) {
    //n = hieght of wall, m = length of wall
    /*
        dude, I faced this problem for about an hour after writing my solution
        then finally get accepted. Take care of some things :
        1) (a-b)%p = (a - b + p)%p
        2) (a+b+c+d)%p = (a%p + b%p + c%p + d%p)%p;
    */
    //((2^n)-1)^(m-1)
    //int k = pow((pow(2,n)-1),(m-1));
    //return k % static_cast<int>(pow(10,9) +7);
    //return k % 100000000007;

    /* //this code works in python, scribed it to c++
    def legoBlocks(wall_height, wall_width):
        mod = 10 ** 9 + 7
        wall_height = wall_height % mod
        wall_width = wall_width % mod
        f = []
        f.append(0)
        f.append(1)
        if wall_width > 1:
            f.append(2)
        if wall_width > 2:
            f.append(4)
        if wall_width > 3:
            f.append(8)

        if wall_width > 4:
            for i in range(5, wall_width + 1):  # stop at index wall_width - 1
                f.append((f[i - 1] + f[i - 2] + f[i - 3] + f[i - 4]) % mod)

        # total_combos = f[-1] ** wall_height

        g = []
        for i in range(len(f)):
            g.append(f[i] ** wall_height % mod)

        # print('f')
        # for _ in range(wall_height): print(f)
        # print('---')
        # print('g')
        # print(g)
        # print('---')

        h = [0] * (wall_width + 1)
        h[1] = 1

        for i in range(2, wall_width + 1):
            h[i] = g[i]
            for j in range(1, i):
                h[i] = (h[i] - h[j] * g[i-j]) % mod
                a=1

        # print('h')
        # print(h)
        # print('---')

        return h[-1] % mod
    */
    int mod = pow(10,9)+7;
    int wall_hieght = n % mod;
    int wall_width = m % mod;
    vector<unsigned int> f;
    f.push_back(0);
    f.push_back(1);
    if(wall_width > 1)
    {
        f.push_back(2);
    }
    if(wall_width > 2)
    {
        f.push_back(4);
    }
    if(wall_width > 3)
    {
        f.push_back(8);
    }
    if(wall_width > 4)
    {
        for(int i = 5; i < wall_width+1; i++)
        {
            f.push_back((f[i-1]+f[i-2]+f[i-3]+f[i-4])&mod);
        }
    }

    vector<unsigned int>g;
    for(int i = 0; i<f.size(); i++)
    {
        g.push_back(static_cast<int>(pow(f[i],wall_hieght))%mod);
    }

    vector<unsigned int> h;
    h.resize(wall_width+1);
    h[1] = 1;

    for(int i = 2; i < wall_width+1; i++)
    {
        h[i] = g[i];
        for(int j = 1; j < i; j++)
        {
            h[i] = ((h[i]-h[j] * g[i-j]) % mod );
            int a=1;
        }
    }
    return h[h.size()-1] % mod;
}


int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int result = legoBlocks(n, m);

        fout << result << "\n";
    }

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
