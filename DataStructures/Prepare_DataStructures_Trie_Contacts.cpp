/*
We're going to make our own Contacts application! The application must
perform two types of operations:
    1.add name, where name is a string denoting a contact name. This must
    store name as a new contact in the application.
    2.find partial, where partial is a string denoting a partial name to
    search the application for. It must count the number of contacts
    starting with partial and print the count on a new line.
Given n sequential add and find operations, perform each operation in order.
Example
    Operations are requested as follows:
        add ed
        add eddie
        add edward
        find ed
        add edwina
        find edw
        find a
    Three add operations include the names 'ed', 'eddie', and 'edward'.
    Next, find ed matches all 3 names. Note that it matches and counts the
    entire name 'ed'. Next, add 'edwina' and then find 'edw'.  2 names
    match: 'edward' and 'edwina'. In the final operation, there are 0 names
    that start with 'a'. Return the array [3,2,0].
Function Description
    Complete the contacts function below.
    contacts has the following parameters:
        string queries[n]: the operations to perform
Returns
    int[]: the results of each find operation
Input Format
    The first line contains a single integer, n, the number of operations
    to perform (the size of queries[]).
    Each of the following n lines contains a string, queries[i].
Constraints
    1<=n<=10^5
    1<=length of name<=21
    1<=length of partial <=21
    name and partial contain lowercase English letters only.
    The input does not have any duplicate name for the add operation.
Sample Input
    STDIN           Function
    -----           --------
    4               queries[] size n = 4
    add hack        queries = ['add hack', 'add hackerrank', 'find hac',
                            'find hak']
    add hackerrank
    find hac
    find hak
Sample Output
    2
    0
Explanation
    1.Add a contact named hack.
    2.Add a contact named hackerrank.
    3.Find the number of contact names beginning with hac. Both name start
    with hac, add 2 to the return array.
    4.Find the number of contact names beginning with hak. neither name
    starts with hak, add 0 to the return array.
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'contacts' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts 2D_STRING_ARRAY queries as parameter.
 */
/*
bool compareFunction (std::string a, std::string b) {return a<b;}
class phonebook {
    public:
    vector<string> names;
    //creator
    phonebook()
    {}
    //add name to phonebook in alphabetical order
    void addName(string s)
    {
        //add name
        names.push_back(s);
        //sort the vector
        std::sort(names.begin(),names.end(),compareFunction);
        return;
    }
    //will return all names starting with string s
    int getNames(string s)
    {
        int count = 0;
        bool match = false;
        for(int i = 0; i < names.size(); i++)
        {
            match = true;
            for(int j = 0; j < s.size(); j++)
            {
                if(names[i][j] != s[j])
                {
                    match = false;
                    break;
                }
            }
            if(match)
            {
                count += 1;
            }
        }
        return count;
    }
};
*/
class TNode {
    public:
        int wc;
        TNode* children[26];

        TNode() {
            wc = 0;
            // this was the missing code
            for(int i = 0; i < 26; i++) {
                children[i] = NULL;
            }
        }

        void add(char c, TNode* n) {
            children[c - 'a'] = n;
        }

        TNode* next(char c) {
            return children[c - 'a'];
        }

};
void insert(string key, TNode* root)
{
    for(auto c : key) {
        if(root->next(c) == NULL) {
            root->add(c, new TNode());
        }
        root = root->next(c);
        root->wc++;
    }
}

TNode* find(string key, TNode* root)
{
    for(auto c : key)
    {
        if(root->next(c) == NULL)
        {
            return NULL;
        }
        root = root->next(c);
    }
    return root;
}

vector<int> contacts(vector<vector<string>> queries)
{
    vector<int> results;
    TNode* sentinel = new TNode();
    for_each(queries.begin(), queries.end(), [&results, &sentinel](auto q)
    {
        if(q[0] == "add") {
            insert(q[1], sentinel);
        }
        if(q[0] == "find")
        {
            TNode* node = find(q[1], sentinel);
            results.push_back(node == NULL ? 0 :  node->wc);
        }
    });
    return results;
}
/*
vector<int> contacts(vector<vector<string>> queries)
{
    //to slow
    vector<int> ans;
    phonebook pb;
    for(int i = 0; i < queries.size(); i++)
    {
        if(queries[i][0] == "add")
        {
            pb.addName(queries[i][1]);
        }
        else
        {
            ans.push_back(pb.getNames(queries[i][1]));
        }
    }
    return ans;
}
*/

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string queries_rows_temp;
    getline(cin, queries_rows_temp);

    int queries_rows = stoi(ltrim(rtrim(queries_rows_temp)));

    vector<vector<string>> queries(queries_rows);

    for (int i = 0; i < queries_rows; i++) {
        queries[i].resize(2);

        string queries_row_temp_temp;
        getline(cin, queries_row_temp_temp);

        vector<string> queries_row_temp = split(rtrim(queries_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            string queries_row_item = queries_row_temp[j];

            queries[i][j] = queries_row_item;
        }
    }

    vector<int> result = contacts(queries);

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
